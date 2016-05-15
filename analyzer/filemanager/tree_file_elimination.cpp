#include "tree_file_elimination.h"
#include "file_utils.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>     /* srand, rand */

template <unsigned int n> Combination<n>::Combination(std::initializer_list<unsigned int> inValues) :
mSize(n)
{
  int _i(0);
  for(auto _it(inValues.begin()); _it != inValues.end() && _i < mSize; _it++, _i++)
  {
      mValues[_i] = *_it;
  }
}

///

TreeFileElimination::TreeFileElimination() :
mDimension(DIMENSION)
{

}

TreeFileElimination::~TreeFileElimination()
{

}

bool TreeFileElimination::analyze(const std::string & inFilename)
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
      for(int _d(0); _d < mDimension; _d++)
      {
        _file.write((char*) FileUtils::toBin(_combinationIt->mValues[_d], 2), 2);
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

}

