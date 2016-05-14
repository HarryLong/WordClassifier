#include "tree_file.h"
#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>

#define NORMALIZATION 100000

const unsigned int TreeFile::sAsciiSmallCaseMin = 97;
const unsigned int TreeFile::sAsciiSmallCaseMax = 122;

const unsigned int TreeFile::sAsciiUpperCaseMin = 65;
const unsigned int TreeFile::sAsciiUpperCaseMax = 90;

const unsigned int TreeFile::sAsciiAprostrophe = 39;

const unsigned int TreeFile::sAprostropheValue = 26;

TreeFile::TreeFile()
{
  reset();
}

TreeFile::~TreeFile()
{

}

bool TreeFile::analyze(const std::string & inFilename)
{
  reset();

  unsigned int _totals[27];
  std::memset(&_totals[0], 0, 27*sizeof(unsigned int));
  std::ifstream _file;
  if(FileUtils::open(inFilename, std::ios_base::in | std::ios_base::ate, _file))
  {
    std::streampos _size = _file.tellg(); // Get size
    std::cout << "Size : " << _size << std::endl;
    _file.seekg(0, std::ios_base::beg); // Go back to beginning
    std::streampos _currentPos;
    char _c[2];
    unsigned int _v1;
    unsigned int _v2;
    while((_currentPos = _file.tellg()) < _size-1)
    {
      if(_currentPos % 10000 == 0)
      {
        std::cout << (((1.f*_currentPos)/_size) * 100) << "%" << std::endl;
      }
      _file.read(&_c[0],  2);
      if(getValueFromChar(_c[0], _v1) && getValueFromChar(_c[1], _v2))
      {
        _totals[_v1]++;
        mData[_v1][_v2]++;
      }

      _file.seekg(_currentPos + 1, std::ios_base::beg); // Go back to the location in question
    }
    _file.close();
  }
//  for(int _i(0); _i < 27; _i++)
//  {
//    std::cout << "Total[" << _i << "] --> " << _totals[_i] << std::endl;
//  }
  // Normalize
  for(int _i(0); _i < 27; _i++)
  {
    for(int _ii(0); _ii < 27; _ii++)
    {
      mData[_i][_ii] = ((mData[_i][_ii] * 1.)/_totals[_i]) * NORMALIZATION;
    }
  }
}

std::string TreeFile::getLongestWord(const std::string & inFilename, int & inLength)
{
  std::string _longestWord("");
  inLength = 0;
  std::ifstream _file;
  if(FileUtils::open(inFilename, std::ios_base::in | std::ios_base::ate, _file))
  {
    std::streampos _size = _file.tellg(); // Get size
    _file.seekg(0, std::ios_base::beg); // Go back to beginning
    int _currentLength = 0;
    std::string _currentWord;
    char _c;
    while(_file.tellg() < _size)
    {
      _file.read(&_c, 1);
      if(_c != '\n')
      {
        _currentWord += _c;
        _currentLength++;
      }
      else
      {
        if(_currentLength > inLength)
        {
          inLength = _currentLength;
          _longestWord = _currentWord;
        }
        _currentWord.clear();
        _currentLength = 0;
      }
    }
    _file.close();
  }
  return _longestWord;
}

bool TreeFile::getCharFromValue(unsigned int value, char & c) const
{
  if(value == sAprostropheValue)
  {
    c = '\'';
    return true;
  }
  if(value >= 0 && value < 26)
  {
    c = (char) (value + sAsciiSmallCaseMin);
    return true;
  }
  return false;
}

bool TreeFile::getValueFromChar(char c, unsigned int & value)  const
{
  value = (unsigned int) c;

  if(value >= sAsciiSmallCaseMin && value <= sAsciiSmallCaseMax) // Lowercase
  {
    value -= sAsciiSmallCaseMin;
    return true;
  }

  if(value >= sAsciiUpperCaseMin && value <= sAsciiUpperCaseMax) // Uppercase
  {
    value -= sAsciiUpperCaseMin;
    return true;
  }

  if(value == sAsciiAprostrophe ) // Apostrophe
  {
    value = sAprostropheValue; // hard coded
    return true;
  }
  return false; // Invalid char
}

bool TreeFile::read(const std::string & inFilename)
{

}

void TreeFile::reset()
{
  for(int _i(0); _i < 27; _i++)
  {
    std::memset(mData[_i], 0, 27*sizeof(unsigned int));
  }
}

bool TreeFile::write(const std::string & inFilename) const
{
  std::ofstream _file;
  if(FileUtils::open(inFilename, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc, _file))
  {
    for(int _i(0); _i < 27; _i++)
    {
      for(int _ii(0); _ii < 27; _ii++)
      {
        _file.write((char*) FileUtils::toBin(mData[_i][_ii], 2), 2);
      }
    }
    std::cout << "Data written to: " << inFilename << std::endl;
    _file.close();
  }
  else
  {
    std::cerr << "Failed to open file: " << inFilename << std::endl;
  }
}

bool TreeFile::writeToCSV(const std::string & inFilename) const
{
  std::ofstream _file;
  if(FileUtils::open(inFilename, std::ios_base::out | std::ios_base::trunc, _file))
  {
    char _srcC;
    char _dstC;
    for(int _i(0); _i < 27; _i++)
    {
      for(int _ii(0); _ii < 27; _ii++)
      {
        getCharFromValue(_i, _srcC);
        getCharFromValue(_ii, _dstC);
        _file << _srcC << ", " << _dstC << ", " << std::to_string(mData[_i][_ii]) << "\n";
      }
    }
    std::cout << "CSV data written to: " << inFilename << std::endl;
    _file.close();
  }
  else
  {
    std::cerr << "Failed to open file: " << inFilename << std::endl;
  }
}

void TreeFile::generateDummyValues()
{
  int _v(0);
  for(int _i(0); _i < 27; _i++)
  {
    for(int _ii(0); _ii < 27; _ii++)
    {
      mData[_i][_ii] = _v++%1000;
    }
  }
}
