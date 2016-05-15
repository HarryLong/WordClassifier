const CHARS = 'abcdefghijklmnopqrstuvwxyz\''
const TOTAL_BYTE_COUNT_PER_CHAR = CHARS.length * 2
const MAX_LENGTH_WORD = 16
const DENORMALIZER = 100000
const MAP = {}

module.exports = {
  init: data => {
    var currentLetter = CHARS[0]
    MAP[currentLetter] = []

    data.forEach((b, i) => {
      if (i % TOTAL_BYTE_COUNT_PER_CHAR == 0) {
        currentLetter = CHARS[(i / (TOTAL_BYTE_COUNT_PER_CHAR))]
        MAP[currentLetter] = []
      }

      if (i % 2 == 0)
        MAP[currentLetter].push(data.readUInt16BE(i))
    })

    // console.log(MAP)
  },
  test: (key, value) => {
    var score = 1
    for(var i=0; i < key.length - 1; i++) {
      // console.log(MAP[key[i]][CHARS.indexOf(key[i+1])] / DENORMALIZER)
      score *= MAP[key[i]][CHARS.indexOf(key[i+1])] / DENORMALIZER
    }
    //score = Math.pow(score, MAX_LENGTH_WORD - key.length)
    console.log(value, score)
  }
}
