const CHARS = 'abcdefghijklmnopqrstuvwxyz\''
const VOWELS_REGEX = new RegExp('[aeiou]', 'gi')
const CONSONANTS_REGEX = new RegExp('[bcdfghjklmnpqrstvwxyz\']', 'gi')

const MAX_WORD_LENGTH = 15
const MIN_VOWEL_RATIO = 0.05
const MAX_VOWEL_RATIO = 0.71

// [type of data | number of letters | max fault tolerance]
const DATA_MAPPING = ['S|2|0','S|3|0','E|2|0','E|3|0','G|2|0','G|3|0', 'G|4|0', 'O|0|1']
const DATA_SEPARATOR = 124 // ascii code of |

let MAP

const initMap = data => {
  MAP = DATA_MAPPING.map(() => [])
  setMap(data)
}

const setMap = data => {
  let counter = 0
  let separatorCounter = 0

  data.forEach((b,i) => {

    if (b == DATA_SEPARATOR) {
      separatorCounter++
      counter = 0

    } else {

      let dataMapItem = DATA_MAPPING[separatorCounter].split('|')
      let numberOfLetters = parseInt(dataMapItem[1])

      if (numberOfLetters) {
        if (counter % numberOfLetters == 0) {
          let block = ''

          for (let j = 0; j < numberOfLetters; j++)
            block += CHARS[data[i + j]]

          MAP[separatorCounter].push(block)
        }

      } else {
        MAP[separatorCounter].push(data[i])
      }
      counter++
    }
  })
}

const testByLength = word => {
  return word.length < MAX_WORD_LENGTH
}

const testByData = word => {
  let counters = {}

  DATA_MAPPING.forEach((data, index) => {

    data = data.split('|')
    let typeOfData = data[0]
    let numberOfLetters = parseInt(data[1])

    counters[index] = counters[index] || 0

    if (typeOfData == 'S') {
      let block = word.substr(0, numberOfLetters)

      if (MAP[index].indexOf(block) != -1)
        counters[index]++

    } else if (typeOfData == 'E') {
      let block = word.substr(-numberOfLetters)

      if (MAP[index].indexOf(block) != -1)
        counters[index]++

    } else if (typeOfData == 'G') {
      for (let i = 0; i < word.length - (numberOfLetters - 1); i++) {
        let block = ''

        for (let j = 0; j < numberOfLetters; j++)
          block += word[i + j]

        if (MAP[index].indexOf(block) != -1)
          counters[index]++
      }

    } else if (typeOfData == 'O') {
      let occurrence = {}
      for (let i = 0; i < word.length; i++) {
        occurrence[word[i]] = occurrence[word[i]] ? occurrence[word[i]] + 1 : 1
      }
      for (let letter in occurrence) {
        if (occurrence.hasOwnProperty(letter))
          if ((occurrence[letter] / word.length) * 255 > MAP[index][CHARS.indexOf(letter)]) {
            counters[index]++
          }
      }
    }
  })

  let flag = true
  DATA_MAPPING.forEach((data, index) => {
    let maxError = parseInt(data.split('|')[2])
    if (counters[index] > maxError)
      flag = false
  })
  return flag
}

const testByVowelRatio = word => {
  let ratio
  let noOfVowels = word.match(VOWELS_REGEX)

  noOfVowels = noOfVowels ? noOfVowels.length : 0
  ratio = noOfVowels / word.length

  return ratio > MIN_VOWEL_RATIO && ratio < MAX_VOWEL_RATIO
}

module.exports = {
  init: data => initMap(data),
  test: word => testByLength(word) && testByData(word) && testByVowelRatio(word)
}
