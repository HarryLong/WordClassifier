const brain = require('brain')
const http = require('follow-redirects').http
const jsonfile = require('jsonfile')

const testFile = '../resources/test.json'

const trainSettings = {
  errorThresh: 0.005,  // error threshold to reach
  iterations: 20000,   // maximum training iterations
  log: true,           // console.log() progress periodically
  logPeriod: 10,       // number of iterations between logging
  learningRate: 0.3    // learning rate
}
let net = new brain.NeuralNetwork()

train()

function train () {
  let counter = 0
  let array = []
  jsonfile.readFile(testFile, (err, wordsExisting) => {
    wordsExisting.forEach( words => {
      counter++
      for (let word in words) {
        if (words.hasOwnProperty(word)) {
          let letterOccurrence = {}
          for (let i = 0; i < word.length; i++) {
            letterOccurrence[word[i]] = letterOccurrence[word[i]] ? letterOccurrence[word[i]] + 1 : 1
          }
          array.push({
            input: letterOccurrence,
            output: {
              isEnglish: words[word] ? 1 : 0
            }
          })
        }
      }
      process.stdout.write(counter + '\r')
    })

    array.splice(0, 8400)
    console.log('Training', array.length)
    net.train(array, trainSettings)
    test()
  })
}

function test () {
  console.log('TEST')
  http.get('http://hola.org/challenges/word_classifier/testcase', (res) => {

    let body = ''

    res.on('data', chunk => {
      body += chunk
    })

    res.on('end', () => {
      let words = JSON.parse(body)
      let nativeTrueCounter = 0
      let trueCounter = 0
      let falseCounter = 0

      for (let word in words) {
        if (words.hasOwnProperty(word)) {
          let letterOccurrence = {}
          for (let i = 0; i < word.length; i++) {
            letterOccurrence[word[i]] = letterOccurrence[word[i]] ? letterOccurrence[word[i]] + 1 : 1
          }

          if(words[word])
            nativeTrueCounter++

          if(net.run(letterOccurrence).isEnglish > .5 == words[word])
            trueCounter++
          else
            falseCounter++

        }
      }
      console.log(nativeTrueCounter, trueCounter, falseCounter)
      test()
    })
  })
}