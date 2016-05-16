const zlib = require('zlib')
const fs = require('fs')
const jsonfile = require('jsonfile')
const http = require('follow-redirects').http
const classifier = require('./classifier_eliminator')
const combinedStream = require('combined-stream');

const srcs = [
  '../resources/sample_start_elimination_2d.io',
  '../resources/sample_start_elimination_3d.io',
  '../resources/sample_ending_elimination_2d.io',
  '../resources/sample_ending_elimination_3d.io',
  '../resources/sample_elimination_2d.io',
  '../resources/sample_elimination_3d.io'
]

const dest = '../resources/sample_elimination_all.io'
const zip = '../resources/sample_elimination_all.io.gz'

var counter = 0
var sum = 0

var cs = combinedStream.create();
srcs.forEach(src => {
  cs.append(fs.createReadStream(src))
  cs.append(new Buffer('|'))
})
cs.pipe(
  fs.createWriteStream(dest)
    .on('close', gzip)
)

// retrieveTestData()

// create gzip
function gzip () {
  fs.createReadStream(dest)
    .pipe(zlib.createGzip())
    .pipe(
      fs.createWriteStream(zip)
        .on('close', init)
    )
}

// read gzip
function init() {
  classifier.init(
    zlib.gunzipSync(fs.readFileSync(zip))
  )
  testLocal()
}
// test classifier
function testLive() {

  http.get('http://hola.org/challenges/word_classifier/testcase', (res) => {
    counter++

    let body = ''

    res.on('data', chunk => {
      body += chunk
    })

    res.on('end', () => {
      let words = JSON.parse(body)
      let correctCounter = 0
      for (var word in words) {
        if (words.hasOwnProperty(word)) {
          let isEnglish = classifier.test(word)
          isEnglish == words[word] && correctCounter++
          // console.log(word, words[word], isEnglish)
        }
      }

      sum = sum + ((100 * correctCounter) / Object.keys(words).length)

      process.stdout.write(`Counter: ${counter} | Average: ${(sum/counter).toFixed(2)}%\r`);
      // console.log('Result', (100 * correctCounter) / Object.keys(words).length, '%')
      testLive()
    })
  })
}

function testLocal() {
  let file = '../resources/test.json'
  jsonfile.readFile(file, (err, wordsExisting) => {
    wordsExisting.forEach( words => {
      counter++
      let correctCounter = 0
      for (var word in words) {
        if (words.hasOwnProperty(word)) {
          let isEnglish = classifier.test(word)
          isEnglish == words[word] && correctCounter++
        }
      }
      sum = sum + ((100 * correctCounter) / Object.keys(words).length)
      process.stdout.write(`Counter: ${counter} | Average: ${(sum/counter).toFixed(2)}%\r`);
    })
    console.log('')
  })
}

// test classifier
function retrieveTestData() {

  http.get('http://hola.org/challenges/word_classifier/testcase', (res) => {
    counter++

    let body = ''

    res.on('data', chunk => {
      body += chunk
    })

    res.on('end', () => {
      let words = JSON.parse(body)
      let file = '../resources/test.json'

      jsonfile.readFile(file, (err, wordsExisting) => {
        console.log('Size:', wordsExisting.length)
        wordsExisting.push(words)
        jsonfile.writeFile(file, wordsExisting, function (err) {
            retrieveTestData()
        })
      })
    })
  })
}