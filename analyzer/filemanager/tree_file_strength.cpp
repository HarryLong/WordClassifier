#include "tree_file_strength.h"
#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include "converter.h"

#define NORMALIZATION 100000

TreeFileStrength::TreeFileStrength()
{
  reset();
}

TreeFileStrength::~TreeFileStrength()
{

}

bool TreeFileStrength::analyze(const std::string & inFilename)
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
      if(Converter::fromChar(_c[0], _v1) && Converter::fromChar(_c[1], _v2))
      {
        _totals[_v1]++;
        mData[_v1][_v2]++;
      }

      _file.seekg(_currentPos + 1, std::ios_base::beg); // Go back to the location in question
    }
    _file.close();
  }

  for(int _i(0); _i < 27; _i++)
  {
    for(int _ii(0); _ii < 27; _ii++)
    {
      mData[_i][_ii] = ((mData[_i][_ii] * 1.)/_totals[_i]) * NORMALIZATION;
    }
  }
}

bool TreeFileStrength::read(const std::string & inFilename)
{

}

void TreeFileStrength::reset()
{
  std::memset(&mData[0][0], 0, 27*27*sizeof(mData[0][0]));
}

bool TreeFileStrength::write(const std::string & inFilename) const
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

bool TreeFileStrength::writeToCSV(const std::string & inFilename) const
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
        Converter::fromValue(_i, _srcC);
        Converter::fromValue(_ii, _dstC);
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

void TreeFileStrength::generateDummyValues()
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
