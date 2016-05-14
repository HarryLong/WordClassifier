#include "tree_file.h"
#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <cstring>

const unsigned int TreeFile::sAsciiSmallCaseMin = 97;
const unsigned int TreeFile::sAsciiSmallCaseMax = 122;

const unsigned int TreeFile::sAsciiUpperCaseMin = 65;
const unsigned int TreeFile::sAsciiUpperCaseMax = 90;

const unsigned int TreeFile::sAsciiAprostrophe = 39;

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
      if(getCharValue(_c[0], _v1) && getCharValue(_c[1], _v2))
      {
        _totals[_v1]++;
        mData[_v1][_v2]++;
      }

      _file.seekg(_currentPos + 1, std::ios_base::beg); // Go back to the location in question
    }
    _file.close();
  }

  // Normalize
  for(int _i(0); _i < 27; _i++)
  {
    for(int _ii(0); _ii < 27; _ii++)
    {
      mData[_i][_ii] = ((mData[_i][_ii] * 1.f)/_totals[_i]) * 1000;
    }
  }
}

bool TreeFile::getCharValue(char c, unsigned int & value)
{
  value = (unsigned int) c;

  if(value >= TreeFile::sAsciiSmallCaseMin && value <= TreeFile::sAsciiSmallCaseMax) // Lowercase
  {
    value -= TreeFile::sAsciiSmallCaseMin;
    return true;
  }

  if(value >= TreeFile::sAsciiUpperCaseMin && value <= TreeFile::sAsciiUpperCaseMax) // Uppercase
  {
    value -= TreeFile::sAsciiUpperCaseMin;
    return true;
  }

  if(value == TreeFile::sAsciiAprostrophe ) // Apostrophe
  {
    value = 26; // hard coded
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
    for(int _i(0); _i < 27; _i++)
    {
      for(int _ii(0); _ii < 27; _ii++)
      {
//        _file <<
//        _file.write();
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
