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
  bool writeToCSV(const std::string & inFilename) const;

  void generateDummyValues();

  std::string getLongestWord(const std::string & inFilename, int & inLength);
private:
  void reset();
  bool getValueFromChar(char c, unsigned int & value) const;
  bool getCharFromValue(unsigned int value, char & c) const;

  unsigned int mData[27][27];

  static const unsigned int sAsciiSmallCaseMin;
  static const unsigned int sAsciiSmallCaseMax;

  static const unsigned int sAsciiUpperCaseMin;
  static const unsigned int sAsciiUpperCaseMax;

  static const unsigned int sAsciiAprostrophe;

  static const unsigned int sAprostropheValue;
};
