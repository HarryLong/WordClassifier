const fs = require('fs')
const http = require('follow-redirects').http
const file = '../resources/wordsV2.txt'

collect()

// test classifier
let counter = 0
function collect () {
  let wordsFile = fs.createWriteStream(file, {'flags': 'a'})
  http.get('http://hola.org/challenges/word_classifier/testcase', (res) => {

    let body = ''

    res.on('data', chunk => {
      body += chunk
    })

    res.on('end', () => {
      let words = JSON.parse(body)
      for (let word in words) {
        if (words.hasOwnProperty(word)) {
          if(words[word]) {
            counter++
            wordsFile.write(word + '\n')
          }
        }
      }
      console.log('added', counter)
      wordsFile.end()
      collect()
    })
  })
}