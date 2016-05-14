#include "tree_file.h"
#include "file_utils.h"
#include <fstream>
#include <iostream>
#include <cstring>

TreeFile::TreeFile()
{
  reset();
}

TreeFile::~TreeFile()
{

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
  if(FileUtils::open(inFilename, _file))
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
