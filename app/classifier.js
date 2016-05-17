const CHARS = 'abcdefghijklmnopqrstuvwxyz\''
const VOWELS = 'aeiou'
const CONSONANTS = 'bcdfghjklmnpqrstvwxyz'

// [type of data | number of letters | max fault tolerance]
const DATA_MAPPING = ['S|2|0','S|3|1','E|2|0','E|3|1','G|2|0','G|3|1']
const DATA_SEPARATOR = 124 // ascii code of |

const MAX_WORD_LENGTH = 15 // SD
const MIN_VOWEL_RATIO = 0.10
const MAX_VOWEL_RATIO = 0.80

let MAP

const initMap = data => {
  MAP = DATA_MAPPING.map(() => [])
  setMap(data)
}

const setMap = data => {
  let counter = 0
  let separatorCounter = 0
  let numberOfLetters = 0

  data.forEach((b,i) => {

    if (b == DATA_SEPARATOR) {
      separatorCounter++
      counter = 0

    } else {
      numberOfLetters = parseInt(DATA_MAPPING[separatorCounter].split('|')[1])

      if (counter % numberOfLetters == 0) {
        let block = ''

        for (let j = 0; j < numberOfLetters; j++)
          block += CHARS[data[i + j]]

        MAP[separatorCounter].push(block)
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
        counters[index] += 1

    } else if (typeOfData == 'E') {
      let block = word.substr(-numberOfLetters)

      if (MAP[index].indexOf(block) != -1)
        counters[index] += 1

    } else if (typeOfData == 'G') {
      for (let i = 0; i < word.length - (numberOfLetters - 1); i++) {
        let block = ''

        for (let j = 0; j < numberOfLetters; j++)
          block += word[i + j]

        if (MAP[index].indexOf(block) != -1)
          counters[index] += 1
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
  let noOfVowels = word.match(new RegExp(`[${VOWELS}]`, 'gi'))
  let noOfConsonants = word.match(new RegExp(`[${CONSONANTS}]`, 'gi'))

  noOfVowels = noOfVowels ? noOfVowels.length : 0
  noOfConsonants = noOfConsonants ? noOfConsonants.length : 0
  ratio = noOfVowels / (noOfVowels + noOfConsonants)

  return ratio > MIN_VOWEL_RATIO && ratio < MAX_VOWEL_RATIO
}

module.exports = {
  init: data => initMap(data),
  test: word => testByLength(word) && testByData(word) && testByVowelRatio(word)
}
