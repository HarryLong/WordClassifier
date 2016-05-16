#pragma once


#include <cmath>
#include <map>
#include <string>
#include <vector>
#include "constants.h"

template <unsigned int n = Constants::sDimension> class TreeFileStrength{
public:
  TreeFileStrength();
  ~TreeFileStrength();
  virtual bool analyze(const std::string & inFilename);
  bool read(const std::string & inFilename);
  bool write(const std::string & inFilename) const;
  bool writeToCSV(const std::string & inFilename) const;

  void generateDummyValues();

  const unsigned int * getData() const;
protected:
  void reset();
  bool getIndex(char inChars[n], unsigned int & outIndex) const;
  std::vector<char> getChars(int inIndex) const;

  unsigned int mData[(unsigned int)pow(27,n)];
};

#include "tree_file_strength.tpp"
