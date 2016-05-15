#include "tree_file_elimination.h"
#include "file_utils.h"
#include "converter.h"

#include <stdlib.h>     /* srand, rand */
#include <iostream>     /* srand, rand */

///

TreeFileElimination::TreeFileElimination()
{

}

TreeFileElimination::~TreeFileElimination()
{

}

bool TreeFileElimination::read(const std::string & inFilename)
{

}

bool TreeFileElimination::write(const std::string & inFilename) const
{
  std::ofstream _file;
  if(FileUtils::open(inFilename, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc, _file))
  {
    for(auto _combinationIt(mInvalidCombinations.cbegin()); _combinationIt != mInvalidCombinations.cend(); _combinationIt++)
    {
      for(int _d(0); _d < Constants::sDimension; _d++)
      {
        _file.write((char*) FileUtils::toBin(_combinationIt->mValues[_d], 1), 1);
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

bool TreeFileElimination::writeToCSV(const std::string & inFilename) const
{
  std::ofstream _file;
  if(FileUtils::open(inFilename, std::ios_base::out | std::ios_base::trunc, _file))
  {
    char _c;
    for(auto _combinationIt(mInvalidCombinations.cbegin()); _combinationIt != mInvalidCombinations.cend(); _combinationIt++)
    {
      for(int _d(0); _d < Constants::sDimension; _d++)
      {
        if(_d != 0)
          _file << ", ";
        if(Converter::fromValue(_combinationIt->mValues[_d], _c))
        {
          _file << _c;
        }
        else
        {
          _file << "INVALID CHAR";
        }
      }
      _file << '\n';
    }

    std::cout << "CSV data written to: " << inFilename << std::endl;
    _file.close();
  }
  else
  {
    std::cerr << "Failed to open file: " << inFilename << std::endl;
  }
}

void TreeFileElimination::generateDummyValues(int inCount)
{
  reset();
  for(int _i(0); _i < inCount; _i++)
  {
    mInvalidCombinations.push_back({(unsigned int) (rand()%27),(unsigned int) (rand()%27),(unsigned int) (rand()%27)});
  }
}

void TreeFileElimination::reset()
{
  mInvalidCombinations.clear();
}

