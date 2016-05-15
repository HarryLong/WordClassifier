#pragma once

#include <cmath>
#include <map>
#include <string>
#include <vector>

#include <initializer_list>

#include "constants.h"
#include "tree_file_strength.h"

template <unsigned int n> struct Combination{
public:
  Combination(const std::initializer_list<unsigned int> & inValues);
  Combination(const std::vector<unsigned int> & inValues);
  unsigned int mValues[n];
private:
  int mSize;
};

class TreeFileElimination{
public:
  TreeFileElimination();
  ~TreeFileElimination();
  template <unsigned int n> bool process(const TreeFileStrength<n> & inTreeFile, unsigned int threshold = 0);
  bool read(const std::string & inFilename);
  bool write(const std::string & inFilename) const;
  bool writeToCSV(const std::string & inFilename) const;

  void generateDummyValues(int inCount = 1000);

private:
  void reset();

  std::vector<Combination<Constants::sDimension>> mInvalidCombinations;
};

template <unsigned int n> Combination<n>::Combination(const std::initializer_list<unsigned int> & inValues) :
mSize(n)
{
  int _i(0);
  for(auto _it(inValues.begin()); _it != inValues.end() && _i < mSize; _it++, _i++)
  {
      mValues[_i] = *_it;
  }
}

template <unsigned int n> Combination<n>::Combination(const std::vector<unsigned int> & inValues) :
mSize(n)
{
  int _i(0);
  for(auto _it(inValues.begin()); _it != inValues.end() && _i < mSize; _it++, _i++)
  {
      mValues[_i] = *_it;
  }
}

template <unsigned int n> bool TreeFileElimination::process(const TreeFileStrength<n> & inTreeFile, unsigned int inThreshold /*= 0*/)
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
