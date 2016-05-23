const CHARS = 'abcdefghijklmnopqrstuvwxyz\''
const VOWELS_REGEX = new RegExp('[aeiou]', 'gi')
const CONSONANTS_REGEX = new RegExp('[bcdfghjklmnpqrstvwxyz\']', 'gi')

const MIN_WORD_LENGTH = 2
const MAX_WORD_LENGTH = 14
const MIN_VOWEL_RATIO = 0.08
const MAX_VOWEL_RATIO = 0.83
const MIN_CONSONANT_RATIO = 0.25
const MAX_CONSONANT_RATIO = 0.90

// [type of data | number of letters]
const DATA_MAPPING = ['S|2','S|3','E|2','E|3','G|2','G|3','G|4','O|0']
const DATA_SEPARATOR = 124 // ascii code of |
const DATA_FAULT_TOLERANCE = 0

let MAP = []

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

const testByData = word => {
  let faultCounter = 0

  DATA_MAPPING.forEach((data, index) => {

    data = data.split('|')
    let typeOfData = data[0]
    let numberOfLetters = parseInt(data[1])

    if (typeOfData == 'S') {
      let block = word.substr(0, numberOfLetters)

      if (MAP[index].indexOf(block) != -1)
        faultCounter++

    } else if (typeOfData == 'E') {
      let block = word.substr(-numberOfLetters)

      if (MAP[index].indexOf(block) != -1)
        faultCounter++

    } else if (typeOfData == 'G') {
      for (let i = 0; i < word.length - (numberOfLetters - 1); i++) {
        let block = ''

        for (let j = 0; j < numberOfLetters; j++)
          block += word[i + j]

        if (MAP[index].indexOf(block) != -1)
          faultCounter++
      }

    } else if (typeOfData == 'O') {
      let occurrence = {}
      for (let i = 0; i < word.length; i++) {
        occurrence[word[i]] = occurrence[word[i]] ? occurrence[word[i]] + 1 : 1
      }
      for (let letter in occurrence) {
        if (occurrence.hasOwnProperty(letter))
          if ((occurrence[letter] / word.length) * 255 > MAP[index][CHARS.indexOf(letter)]) {
            faultCounter++
          }
      }
    }
  })

  return faultCounter <= DATA_FAULT_TOLERANCE
}

const testByLength = word => {
  return word.length <= MAX_WORD_LENGTH && word.length >= MIN_WORD_LENGTH
}

const testByVowelRatio = word => {
  let noOfVowels = word.match(VOWELS_REGEX)
  noOfVowels = noOfVowels ? noOfVowels.length : 0
  let ratio = noOfVowels / word.length
  return ratio >= MIN_VOWEL_RATIO && ratio <= MAX_VOWEL_RATIO
}

const testByConsonantRatio = word => {
  let noOfConsonants = word.match(CONSONANTS_REGEX)
  noOfConsonants = noOfConsonants ? noOfConsonants.length : 0
  let ratio = noOfConsonants / word.length
  return ratio >= MIN_CONSONANT_RATIO && ratio <= MAX_CONSONANT_RATIO
}

const testWord = word =>
      word ?
      testByLength(word) &&
      testByVowelRatio(word) &&
      testByConsonantRatio(word) &&
      testByData(word) :
      false

module.exports = {
  init: initMap,
  test: testWord
}
