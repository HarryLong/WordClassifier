const CHARS = 'abcdefghijklmnopqrstuvwxyz\''
var MAP = []
var DIMENSION = 2

/*
* thins to add
* 1. starting letters probability
* 2. ending letters probability
* 3. Wovel ratio
* */

module.exports = {

  init: data => {
    data.forEach((b,i) => {

      if (b.toString() == '|'.charCodeAt(0))
        DIMENSION++

      if (i % DIMENSION == 0) {
        let block = ''
        for (let j = 0; j < DIMENSION; j++)
          block += CHARS[data[i + j]]

        MAP.push(block)
      }
    })
  },

  test: word => {
    let isEnglish = true

    if(word.length >= 15)
      return false

    for (var d = 2; d < DIMENSION; d++) {
      if (isEnglish) {
        for (let i = 0; i < word.length - (d - 1); i++) {
          if (isEnglish) {
            let block = ''

            for (let j = 0; j < d; j++)
              block += word[i + j]

            if (MAP.indexOf(block) != -1)
              isEnglish = false
          }
        }
      }
    }
    return isEnglish
  }
}
