#pragma once

#include <map>
#include <string>

class TreeFile{
public:
  TreeFile();
  ~TreeFile();
  bool analyze(const std::string & inFilename);
  bool read(const std::string & inFilename);
  bool write(const std::string & inFilename) const;

  void generateDummyValues();

private:
  void reset();

  unsigned int mData[27][27];
};
