
#include <iostream>
#include "filemanager/tree_file_strength.h"
#include "filemanager/tree_file_elimination.h"
#include "filemanager/endings_analyzer.h"
#include "filemanager/start_analyzer.h"
#include "filemanager/constants.h"

#define OUTPUT_ELIMINATE_CSV_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination_2d.csv"
#define OUTPUT_ELIMINATE_CSV_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination_3d.csv"
#define OUTPUT_ELIMINATE_CSV_FILE_4D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination_4d.csv"

#define OUTPUT_STRENGTH_CSV_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength_2d.csv"
#define OUTPUT_STRENGTH_CSV_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength_3d.csv"
#define OUTPUT_STRENGTH_CSV_FILE_4D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength_4d.csv"

#define OUTPUT_ELIMINATE_IO_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination_2d.io"
#define OUTPUT_STRENGTH_IO_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength_2d.io"
#define OUTPUT_ELIMINATE_IO_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination_3d.io"
#define OUTPUT_STRENGTH_IO_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength_3d.io"
#define OUTPUT_ELIMINATE_IO_FILE_4D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_elimination_4d.io"
#define OUTPUT_STRENGTH_IO_FILE_4D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_strength_4d.io"

#define ENDING_ELIMINATE_IO_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_ending_elimination_2d.io"
#define ENDING_ELIMINATE_CSV_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_ending_elimination_2d.csv"
#define ENDING_ELIMINATE_IO_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_ending_elimination_3d.io"
#define ENDING_ELIMINATE_CSV_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_ending_elimination_3d.csv"

#define START_ELIMINATE_IO_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_start_elimination_2d.io"
#define START_ELIMINATE_CSV_FILE_2D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_start_elimination_2d.csv"

#define START_ELIMINATE_IO_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_start_elimination_3d.io"
#define START_ELIMINATE_CSV_FILE_3D "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample_start_elimination_3d.csv"

#define INPUT_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/words.txt"

#define VOWEL_STATS false
#define GENERAL_STATS false
#define GLOBAL_OCCURENCES false
#define ENDING_OCCURENCES false
#define START_OCCURENCES true

int main (int argc, char *argv[])
{

#if VOWEL_STATS
  double _meanVowelRatio;
  double _vowelSD;
  FileUtils::getVowelStatistics(INPUT_FILE, _meanVowelRatio, _vowelSD);
  std::cout << "*************************************" << std::endl;
  std::cout << "Mean vowel ratio: " << _meanVowelRatio << std::endl;
  std::cout << "Vowel ratio SD: " << _vowelSD << std::endl;
#endif // VOWEL_STATS

#if GENERAL_STATS
  int _maxLength;
  std::string _longestWord;
  double _mean;
  double _sd;

  FileUtils::getStatistics(INPUT_FILE, _maxLength, _longestWord, _mean, _sd);

  std::cout << "*************************************" << std::endl;
  std::cout << "Max Length: " << _maxLength << std::endl;
  std::cout << "Longest word: " << _longestWord << std::endl;
  std::cout << "Mean length: " << _mean << std::endl;
  std::cout << "SD: " << _sd << std::endl;
#endif // GENERAL_STATS

#if GLOBAL_OCCURENCES
  {
    TreeFileStrength<2> _strengthFile2D;
  _strengthFile2D.analyze(INPUT_FILE);

  TreeFileStrength<3> _strengthFile3D;
  _strengthFile3D.analyze(INPUT_FILE);

//  TreeFileStrength<4> _strengthFile4D;
//  _strengthFile4D.analyze(INPUT_FILE);

  TreeFileElimination<2> _eliminator2D;
  _eliminator2D.process(_strengthFile2D);

  TreeFileElimination<3> _eliminator3D;
  _eliminator3D.process(_strengthFile3D);

//  TreeFileElimination<4> _eliminator4D;
//  _eliminator4D.process(_strengthFile4D);

//  std::cout << "Illiminating 4D" << std::endl;
//  _eliminator4D.eliminate(_eliminator3D);
  std::cout << "Illiminating 3D" << std::endl;
  _eliminator3D.eliminate(_eliminator2D);

  _eliminator2D.write(OUTPUT_ELIMINATE_IO_FILE_2D);
  _eliminator2D.writeToCSV(OUTPUT_ELIMINATE_CSV_FILE_2D);

  _eliminator3D.write(OUTPUT_ELIMINATE_IO_FILE_3D);
  _eliminator3D.writeToCSV(OUTPUT_ELIMINATE_CSV_FILE_3D);

//  _eliminator4D.write(OUTPUT_ELIMINATE_IO_FILE_4D);
//  _eliminator4D.writeToCSV(OUTPUT_ELIMINATE_CSV_FILE_4D);
  }
#endif // GLOBAL_OCCURENCES


#if ENDING_OCCURENCES
  {
    EndingAnalyzer<2> _endingsAnalyzer2D;
    _endingsAnalyzer2D.analyze(INPUT_FILE);

    EndingAnalyzer<3> _endingsAnalyzer3D;
    _endingsAnalyzer3D.analyze(INPUT_FILE);

    TreeFileElimination<2> _eliminator2D;
    _eliminator2D.process(_endingsAnalyzer2D);

    TreeFileElimination<3> _eliminator3D;
    _eliminator3D.process(_endingsAnalyzer3D);

    _eliminator3D.eliminate(_eliminator2D);


    _eliminator2D.write(ENDING_ELIMINATE_IO_FILE_2D);
    _eliminator2D.writeToCSV(ENDING_ELIMINATE_CSV_FILE_2D);

    _eliminator3D.write(ENDING_ELIMINATE_IO_FILE_3D);
    _eliminator3D.writeToCSV(ENDING_ELIMINATE_CSV_FILE_3D);
  }
#endif // ENDING_OCCURENCES

#if START_OCCURENCES
  {
    StartAnalyzer<2> _startAnalyzer2D;
    _startAnalyzer2D.analyze(INPUT_FILE);

    StartAnalyzer<3> _startAnalyzer3D;
    _startAnalyzer3D.analyze(INPUT_FILE);

    TreeFileElimination<2> _eliminator2D;
    _eliminator2D.process(_startAnalyzer2D);

    TreeFileElimination<3> _eliminator3D;
    _eliminator3D.process(_startAnalyzer3D);

    _eliminator3D.eliminate(_eliminator2D);


    _eliminator2D.write(START_ELIMINATE_IO_FILE_2D);
    _eliminator2D.writeToCSV(START_ELIMINATE_CSV_FILE_2D);

    _eliminator3D.write(START_ELIMINATE_IO_FILE_3D);
    _eliminator3D.writeToCSV(START_ELIMINATE_CSV_FILE_3D);
  }
#endif // START_OCCURENCES
}
