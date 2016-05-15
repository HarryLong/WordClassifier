
#include <iostream>
#include "filemanager/tree_file_strength.h"
#include "filemanager/tree_file_elimination.h"

#define OUTPUT_CSV_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.csv"
#define OUTPUT_IO_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.io"
#define INPUT_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/words.txt"

int main (int argc, char *argv[])
{
  TreeFileElimination _file;

  _file.generateDummyValues();
  _file.write(OUTPUT_IO_FILE);
//  _file.analyze(INPUT_FILE);
//  _file.write(OUTPUT_IO_FILE);
//  _file.writeToCSV(OUTPUT_CSV_FILE);

//  int _length;
//  std::string _longestWord(_file.getLongestWord(INPUT_FILE, _length));
//  std::cout << "Longest word: " << _longestWord << " [ " << _length << " ]" << std::endl;

//  _file.generateDummyValues();
//  _file.write("/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.io");
}
