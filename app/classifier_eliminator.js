const CHARS = 'abcdefghijklmnopqrstuvwxyz\''
const VOWELS = 'aeiou'
const CONSONANTS = 'bcdfghjklmnpqrstvwxyz'

const DATA_MAPPING = ['S2','S3','E2','E3','G2','G3'] // E=>End G=>Global N=>Letter Count
const DATA_SEPARATOR = 124 // ascii code of |
const MAP = DATA_MAPPING.map(() => [])

const MAX_WORD_LENGTH = 13
const MIN_VOWEL_RATIO = 0.09
const MAX_VOWEL_RATIO = 0.71

const setMap = data => {
  let counter = 0
  let separatorCounter = 0
  let numberOfLetters = 0

  data.forEach((b,i) => {

    if (b.toString() == DATA_SEPARATOR) {
      separatorCounter++
      counter = 0

    } else {
      numberOfLetters = DATA_MAPPING[separatorCounter][1]

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

const checkLength = word => {
  return word.length < MAX_WORD_LENGTH
}

const checkData = word => {
  let flag = true

  DATA_MAPPING.forEach((data, index) => {

    if(!flag)
      return

    let typeOfData = data[0]
    let numberOfLetters = data[1]

    if(typeOfData == 'S') {
      let block = word.substr(0, numberOfLetters)

      if(MAP[index].indexOf(block) != -1)
        flag = false

    } else if(typeOfData == 'E') {
      let block = word.substr(-numberOfLetters)

      if(MAP[index].indexOf(block) != -1)
        flag = false

    } else if (typeOfData  == 'G') {
      for (let i = 0; i < word.length - (numberOfLetters - 1); i++) {
        let block = ''

        for (let j = 0; j < numberOfLetters; j++)
          block += word[i + j]

        if (MAP[index].indexOf(block) != -1)
          flag = false
      }
    }
  })

  return flag
}

const checkRatio = word => {
  let ratio
  let noOfVowels = word.match(new RegExp(`[${VOWELS}]`, 'gi'))
  let noOfConsonants = word.match(new RegExp(`[${CONSONANTS}]`, 'gi'))

  noOfVowels = noOfVowels ? noOfVowels.length : 0
  noOfConsonants = noOfConsonants ? noOfConsonants.length : 0
  ratio = noOfVowels / (noOfVowels + noOfConsonants)

  return ratio > MIN_VOWEL_RATIO && ratio < MAX_VOWEL_RATIO
}

module.exports = {
  init: data => setMap(data),
  test: word => checkLength(word) && checkData(word) && checkRatio(word)
}
