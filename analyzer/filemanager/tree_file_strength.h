#pragma once

#define DIMENSION 3

#include <cmath>
#include <map>
#include <string>
#include <vector>

class TreeFileStrength{
public:
  TreeFileStrength();
  ~TreeFileStrength();
  bool analyze(const std::string & inFilename);
  bool read(const std::string & inFilename);
  bool write(const std::string & inFilename) const;
  bool writeToCSV(const std::string & inFilename) const;

  void generateDummyValues();

private:
  void reset();


  unsigned int mData[27][27];
};
