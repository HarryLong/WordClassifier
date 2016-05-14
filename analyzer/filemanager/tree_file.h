#pragma once

#include <map>
#include <string>

class TreeFile{
public:
  TreeFile();
  ~TreeFile();
  bool read(const std::string & inFilename);
  bool write(const std::string & inFilename) const;

private:
  void reset();
  unsigned int mData[27][27];
};
