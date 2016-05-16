#include "tree_file_elimination.h"

template <unsigned int n> TreeFileElimination<n>::TreeFileElimination() :
mCombinationFileWriter()
{

}

template <unsigned int n> TreeFileElimination<n>::~TreeFileElimination()
{

}

template <unsigned int n> bool TreeFileElimination<n>::read(const std::string & inFilename)
{

}

template <unsigned int n> bool TreeFileElimination<n>::write(const std::string & inFilename) const
{
  mCombinationFileWriter.write(inFilename, mInvalidCombinations);
}

template <unsigned int n> bool TreeFileElimination<n>::writeToCSV(const std::string & inFilename) const
{
  mCombinationFileWriter.writeToCSV(inFilename, mInvalidCombinations);
}

template <unsigned int n> void TreeFileElimination<n>::generateDummyValues(int inCount)
{
  reset();
  for(int _i(0); _i < inCount; _i++)
  {
    mInvalidCombinations.push_back({(unsigned int) (rand()%27),(unsigned int) (rand()%27),(unsigned int) (rand()%27)});
  }
}

template <unsigned int n> void TreeFileElimination<n>::reset()
{
  mInvalidCombinations.clear();
}

template <unsigned int n> bool TreeFileElimination<n>::contains(const Combination<n> & inCombination) const
{
  return std::find(mInvalidCombinations.begin(), mInvalidCombinations.end(), inCombination) != mInvalidCombinations.end();
}

template <unsigned int n> bool TreeFileElimination<n>::process(const TreeFileStrength<n> & inTreeFile, unsigned int inThreshold /*= 0*/)
{
  const unsigned int * _data(inTreeFile.getData());
  unsigned int _v;
  for(int _i(0); _i < pow(27, n); _i++)
  {
    if(_data[_i] <= inThreshold)
    {
      std::vector<char> _chars(Converter::getChars(n, _i));
      std::vector<unsigned int> _convertedChars;

      for(auto _it(_chars.begin()); _it != _chars.end(); _it++)
      {
        if(!Converter::fromChar(*_it, _v))
        {
          std::cerr << "Fatal error !" << std::endl;
          std::exit(1);
        }
        _convertedChars.push_back(_v);
      }
      mInvalidCombinations.push_back(_convertedChars);
    }
  }
}


template <unsigned int n>
template <unsigned int nn> bool TreeFileElimination<n>::eliminate(const TreeFileElimination<nn> & inOtherTreeFile)
{
  Combination<nn> _combination1;
//  Combination<nn> _combination2;
//  for(auto _it(mInvalidCombinations.begin()); _it != mInvalidCombinations.end(); )
//  {
////    for(int _ii(0); _ii < nn; _ii++)
////    {
////      _combination1.mValues[_ii] = _it->mValues[_ii];
////    }
////    for(int _ii(1); _ii < n; _ii++)
////    {
////      _combination2.mValues[_ii-1] = _it->mValues[_ii];
////    }
////    if(inOtherTreeFile.contains(_combination1) || inOtherTreeFile.contains(_combination2) )
////    {
////      _it = mInvalidCombinations.erase(_it);
////    }
////    else
////    {
////      _it++;
////    }
//  }
}
