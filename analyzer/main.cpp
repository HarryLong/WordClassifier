
#include <iostream>
#include "filemanager/tree_file_strength.h"
#include "filemanager/tree_file_elimination.h"
#include "filemanager/constants.h"

#define OUTPUT_ELIMINATE_CSV_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination.csv"
#define OUTPUT_STRENGTH_CSV_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength.csv"

#define OUTPUT_ELIMINATE_IO_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination.io"
#define OUTPUT_STRENGTH_IO_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength.io"
#define INPUT_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/words.txt"

int main (int argc, char *argv[])
{
//  TreeFileElimination _file;
  TreeFileStrength<> _strengthFile;
  _strengthFile.analyze(INPUT_FILE);
  _strengthFile.write(OUTPUT_STRENGTH_IO_FILE);
  _strengthFile.writeToCSV(OUTPUT_STRENGTH_CSV_FILE);

  TreeFileElimination _eliminator;
  _eliminator.process(_strengthFile);
  _eliminator.write(OUTPUT_ELIMINATE_IO_FILE);
  _eliminator.writeToCSV(OUTPUT_ELIMINATE_CSV_FILE);


//  _file.analyze(INPUT_FILE);
//  _file.write(OUTPUT_IO_FILE);
//  _file.writeToCSV(OUTPUT_CSV_FILE);

//  int _length;
//  std::string _longestWord(_file.getLongestWord(INPUT_FILE, _length));
//  std::cout << "Longest word: " << _longestWord << " [ " << _length << " ]" << std::endl;

//  _file.generateDummyValues();
//  _file.write("/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.io");
}
