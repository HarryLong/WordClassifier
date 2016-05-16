#include "combination_filewriter.h"
#include "converter.h"

template <unsigned int n> CombinationFileWriter<n>::CombinationFileWriter()
{

}

template <unsigned int n> CombinationFileWriter<n>::~CombinationFileWriter()
{

}

template <unsigned int n> bool CombinationFileWriter<n>::write(const std::string & inFilename, std::vector<Combination<n>> inCombinations) const
{
  std::ofstream _file;
  if(FileUtils::open(inFilename, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc, _file))
  {
    for(auto _combinationIt(inCombinations.cbegin()); _combinationIt != inCombinations.cend(); _combinationIt++)
    {
      for(int _d(0); _d < n; _d++)
      {
        _file.write((char*) FileUtils::toBin(_combinationIt->mValues[_d], 1), 1);
      }
    }
    std::cout << "Data written to: " << inFilename << std::endl;
    _file.close();
    return true;
  }
  std::cerr << "Failed to open file: " << inFilename << std::endl;
  return false;
}

template <unsigned int n> bool CombinationFileWriter<n>::writeToCSV(const std::string & inFilename, std::vector<Combination<n>> inCombinations) const
{
  std::ofstream _file;
  if(FileUtils::open(inFilename, std::ios_base::out | std::ios_base::trunc, _file))
  {
    char _c;
    for(auto _combinationIt(inCombinations.cbegin()); _combinationIt != inCombinations.cend(); _combinationIt++)
    {
      for(int _d(0); _d < n; _d++)
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

    return true;
  }
  std::cerr << "Failed to open file: " << inFilename << std::endl;
  return false;
}
