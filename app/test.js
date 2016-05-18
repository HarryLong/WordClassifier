const zlib = require('zlib')
const fs = require('fs')
const path = require('path')
const jsonfile = require('jsonfile')
const http = require('follow-redirects').http
const classifier = require('./classifier')
const combinedStream = require('combined-stream')
const walk = require('walkdir')

const srcs = [
  'sample_start_elimination_2d.io',
  'sample_start_elimination_3d.io',
  'sample_ending_elimination_2d.io',
  'sample_ending_elimination_3d.io',
  'sample_elimination_2d.io',
  'sample_elimination_3d.io'
]
const dest = '../resources/sample_elimination_all.io'
const zip = '../resources/sample_elimination_all.io.gz'
const testFile = '../resources/test.json'
const reportFile = '../report.json'

let sourcePathsQueue = []
let report
let currentPath

getReport()
initFolders()
// retrieveTestData()

function getReport () {
  if (!fs.existsSync(reportFile))
    jsonfile.writeFileSync(reportFile, {})

  report = jsonfile.readFileSync(reportFile)
}

function setReport (average) {
  report[path.dirname(currentPath)] = average
  jsonfile.writeFileSync(reportFile, report, {spaces: 2})
}

function initFolders () {
  let directories = []

  walk('../')
    .on('path', p => {
      if(p.indexOf('.io') != -1)
        if (directories.indexOf(path.dirname(p)) == -1)
          directories.push(path.dirname(p))

    })
    .on('end', () => {
      initFiles(directories)
    })
}

function initFiles (directories) {

  directories.forEach((dir, i) => {
    let counter = 0
    let tempArr = []

    walk(dir)
      .on('path', p => {

        if(p.indexOf('.io') != -1)
          srcs.forEach(src => {
            if (p && p.indexOf(src) != -1) {
              counter++
              tempArr.push(p)

              if(counter == srcs.length)
                sourcePathsQueue = sourcePathsQueue.concat(tempArr)
            }
          })
      })
      .on('end', () => {
        if(directories.length - 1 == i)
          processQueue()
      })

  })
}

function processQueue () {
  let tempArr = []
  if(sourcePathsQueue.length > (srcs.length - 1)) {
    let unSorted = sourcePathsQueue.splice(0, srcs.length)
    srcs.forEach((src, i) => {
      unSorted.forEach( unSortedSrc => {
        if (unSortedSrc.indexOf(src) != -1)
          tempArr[i] = unSortedSrc
      })
    })
    merge(tempArr)
  } else {
    console.log('DONE')
  }
}

function merge (sourcePaths) {
  currentPath = sourcePaths[0]
  if(!currentPath || report[path.dirname(currentPath)])
    return processQueue()

  // push extra individuals
  sourcePaths.push('../resources/char_occurence.io')

  // log source path
  console.log('Testing Source Path:', path.dirname(currentPath))

  let cs = combinedStream.create()
  sourcePaths.forEach(src => {
    cs.append(fs.createReadStream(src))
    cs.append(new Buffer('|'))
  })
  cs.pipe(
    fs.createWriteStream(dest)
      .on('close', gzip)
  )
}


// create gzip
function gzip () {
  fs.createReadStream(dest)
    .pipe(zlib.createGzip())
    .pipe(
      fs.createWriteStream(zip)
        .on('close', run)
    )
}

// read gzip
function run () {
  classifier.init(
    zlib.gunzipSync(fs.readFileSync(zip))
  )
  testLocal()
}
// test classifier
function testLive () {
  let counter = 0
  let sum = 0

  http.get('http://hola.org/challenges/word_classifier/testcase', (res) => {
    counter++

    let body = ''

    res.on('data', chunk => {
      body += chunk
    })

    res.on('end', () => {
      let words = JSON.parse(body)
      let correctCounter = 0
      for (let word in words) {
        if (words.hasOwnProperty(word)) {
          let isEnglish = classifier.test(word)
          isEnglish == words[word] && correctCounter++
          // console.log(word, words[word], isEnglish)
        }
      }

      sum = sum + ((100 * correctCounter) / Object.keys(words).length)

      process.stdout.write(`Counter: ${counter} | Average: ${(sum/counter).toFixed(2)}%\r`)
      // console.log('Result', (100 * correctCounter) / Object.keys(words).length, '%')
      processQueue()
    })
  })
}

function testLocal () {
  let counter = 0
  let sum = 0

  let counters = {
    truetrue: 0,
    truefalse: 0,
    falsefalse: 0,
    falsetrue: 0
  }

  jsonfile.readFile(testFile, (err, wordsExisting) => {
    wordsExisting.forEach( words => {
      counter++
      let correctCounter = 0
      for (let word in words) {
        if (words.hasOwnProperty(word)) {
          let isEnglish = classifier.test(word)
          isEnglish == words[word] && correctCounter++

          if(words[word] == true && isEnglish == true)
            counters.truetrue++
          else if(words[word] == true && isEnglish == false)
            counters.truefalse++
          else if(words[word] == false && isEnglish == false)
            counters.falsefalse++
          else if(words[word] == false && isEnglish == true)
            counters.falsetrue++
        }
      }
      sum = sum + ((100 * correctCounter) / Object.keys(words).length)
      process.stdout.write(`Counter: ${counter} | Average: ${(sum/counter).toFixed(2)}%\r`)
    })

    setReport((sum/counter).toFixed(2))
    console.log('\n', counters)
    processQueue()
  })
}

// test classifier
function retrieveTestData () {

  http.get('http://hola.org/challenges/word_classifier/testcase', (res) => {

    let body = ''

    res.on('data', chunk => {
      body += chunk
    })

    res.on('end', () => {
      let words = JSON.parse(body)

      jsonfile.readFile(testFile, (err, wordsExisting) => {
        console.log('Size:', wordsExisting.length)
        wordsExisting.push(words)
        jsonfile.writeFile(testFile, wordsExisting, function (err) {
            retrieveTestData()
        })
      })
    })
  })
}