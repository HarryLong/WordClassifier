#pragma once

#include <cmath>
#include <map>
#include <string>
#include <vector>

#include <initializer_list>

#define DIMENSION 3

template <unsigned int n> struct Combination{
public:
  Combination(std::initializer_list<unsigned int> inValues);
  unsigned int mValues[n];
private:
  int mSize;
};

class TreeFileElimination{
public:
  TreeFileElimination();
  ~TreeFileElimination();
  bool analyze(const std::string & inFilename);
  bool read(const std::string & inFilename);
  bool write(const std::string & inFilename) const;
  bool writeToCSV(const std::string & inFilename) const;

  void generateDummyValues(int inCount = 1000);

private:
  void reset();

  const unsigned int mDimension;

  std::vector<Combination<DIMENSION>> mInvalidCombinations;
};
