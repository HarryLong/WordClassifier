
#include <iostream>
#include "filemanager/tree_file_strength.h"
#include "filemanager/tree_file_elimination.h"
#include "filemanager/endings_analyzer.h"
#include "filemanager/start_analyzer.h"
#include "filemanager/constants.h"
#include "filemanager/settings.h"
#include "filemanager/character_occurence_analyzer.h"

#include <sys/stat.h>

#include <thread>         // std::thread

#define OUTPUT_CHAR_OCCURENCE "char_occurence.io"
#define OUTPUT_CHAR_OCCURENCE_CSV "char_occurence.csv"

#define OUTPUT_ELIMINATE_CSV_FILE_2D "sample_elimination_2d.csv"
#define OUTPUT_ELIMINATE_CSV_FILE_3D "sample_elimination_3d.csv"
#define OUTPUT_ELIMINATE_CSV_FILE_4D "sample_elimination_4d.csv"

#define OUTPUT_STRENGTH_CSV_FILE_2D "sample_strength_2d.csv"
#define OUTPUT_STRENGTH_CSV_FILE_3D "sample_strength_3d.csv"
#define OUTPUT_STRENGTH_CSV_FILE_4D "sample_strength_4d.csv"

#define OUTPUT_ELIMINATE_IO_FILE_2D "sample_elimination_2d.io"
#define OUTPUT_STRENGTH_IO_FILE_2D "sample_strength_2d.io"
#define OUTPUT_ELIMINATE_IO_FILE_3D "sample_elimination_3d.io"
#define OUTPUT_STRENGTH_IO_FILE_3D "sample_strength_3d.io"
#define OUTPUT_ELIMINATE_IO_FILE_4D "sample_elimination_4d.io"
#define OUTPUT_STRENGTH_IO_FILE_4D "sample_strength_4d.io"

#define ENDING_ELIMINATE_IO_FILE_2D "sample_ending_elimination_2d.io"
#define ENDING_ELIMINATE_CSV_FILE_2D "sample_ending_elimination_2d.csv"
#define ENDING_ELIMINATE_IO_FILE_3D "sample_ending_elimination_3d.io"
#define ENDING_ELIMINATE_CSV_FILE_3D "sample_ending_elimination_3d.csv"

#define START_ELIMINATE_IO_FILE_2D "sample_start_elimination_2d.io"
#define START_ELIMINATE_CSV_FILE_2D "sample_start_elimination_2d.csv"

#define START_ELIMINATE_IO_FILE_3D "sample_start_elimination_3d.io"
#define START_ELIMINATE_CSV_FILE_3D "sample_start_elimination_3d.csv"

#define INPUT_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/words.txt"

#define BASE_OUTPUT_DIR "/home/harry/workspaces/qt-workspace/word-qualifier/output_multithreaded/"

#define STATS_DIR "/home/harry/workspaces/qt-workspace/word-qualifier/resources/"

//#define WRITE_CSV

//#define VOWEL_STATS
//#define GENERAL_STATS
#define CHAR_OCCURENCE_STATS
//#define GLOBAL_OCCURENCES
//#define ENDING_OCCURENCES
//#define START_OCCURENCES

#include "filemanager/logger.h"

static std::string getUniqueDirName(unsigned int inStartThresholds, unsigned int inEndThreshold, unsigned int inGlobalThreshold,
int inNormalization)
{
    std::string _dir(BASE_OUTPUT_DIR);
    _dir.append("NORM_").append(std::to_string(inNormalization)).
    append("_GLOBALT_").append(std::to_string(inGlobalThreshold)).
    append("_STARTT_").append(std::to_string(inStartThresholds)).
    append("_ENDT_").append(std::to_string(inEndThreshold));
    _dir.append("/");

    return _dir;
}

static void generateGeneralStats()
{
#ifdef GENERAL_STATS
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
}

static void generateVowelStats()
{
#ifdef VOWEL_STATS
  double _meanVowelRatio;
  double _vowelSD;
  FileUtils::getVowelStatistics(INPUT_FILE, _meanVowelRatio, _vowelSD);
  std::cout << "*************************************" << std::endl;
  std::cout << "Mean vowel ratio: " << _meanVowelRatio << std::endl;
  std::cout << "Vowel ratio SD: " << _vowelSD << std::endl;
#endif // VOWEL_STATS
}

static void generateCharOccurenceStats()
{
#ifdef CHAR_OCCURENCE_STATS
  CharacterOccurenceAnalyzer _analyzer;
  _analyzer.analyze(INPUT_FILE);
  _analyzer.write(std::string(STATS_DIR).append(OUTPUT_CHAR_OCCURENCE));
  _analyzer.writeToCSV(std::string(STATS_DIR).append(OUTPUT_CHAR_OCCURENCE_CSV));
#endif // VOWEL_STATS
}

static void run(unsigned int inStartThresholds, unsigned int inEndThreshold, unsigned int inGlobalThreshold,
int inNormalization)
{
  std::string _uniqueDir(getUniqueDirName(inStartThresholds, inEndThreshold, inGlobalThreshold, inNormalization));
  if(FileUtils::dirExists(_uniqueDir.c_str()))
    return;

  mkdir(_uniqueDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  LOG("Writing to: " << _uniqueDir)

#ifdef GLOBAL_OCCURENCES
  TreeFileStrength<2> _globalStrengthFile2D;
  _globalStrengthFile2D.analyze(INPUT_FILE, inNormalization);

  TreeFileStrength<3> _globalStrengthFile3D;
  _globalStrengthFile3D.analyze(INPUT_FILE, inNormalization);

//  TreeFileStrength<4> _strengthFile4D;
//  _strengthFile4D.analyze(INPUT_FILE);

  TreeFileElimination<2> _globalEliminator2D;
  _globalEliminator2D.process(_globalStrengthFile2D, inGlobalThreshold);

  TreeFileElimination<3> _globalEliminator3D;
  _globalEliminator3D.process(_globalStrengthFile3D, inGlobalThreshold);

//  TreeFileElimination<4> _eliminator4D;
//  _eliminator4D.process(_strengthFile4D);

//  std::cout << "Illiminating 4D" << std::endl;
//  _eliminator4D.eliminate(_eliminator3D);
  _globalEliminator3D.eliminate(_globalEliminator2D);

  _globalEliminator2D.write(_uniqueDir + OUTPUT_ELIMINATE_IO_FILE_2D);
  _globalEliminator3D.write(_uniqueDir + OUTPUT_ELIMINATE_IO_FILE_3D);

#ifdef WRITE_CSV
  _globalEliminator2D.writeToCSV(inUniqueDir + OUTPUT_ELIMINATE_CSV_FILE_2D);
  _globalEliminator3D.writeToCSV(inUniqueDir + OUTPUT_ELIMINATE_CSV_FILE_3D);
#endif
//  _eliminator4D.write(OUTPUT_ELIMINATE_IO_FILE_4D);
//  _eliminator4D.writeToCSV(OUTPUT_ELIMINATE_CSV_FILE_4D);
#endif // GLOBAL_OCCURENCES


#ifdef ENDING_OCCURENCES
  {
    EndingAnalyzer<2> _endingsAnalyzer2D;
    _endingsAnalyzer2D.analyze(INPUT_FILE, inNormalization);

    EndingAnalyzer<3> _endingsAnalyzer3D;
    _endingsAnalyzer3D.analyze(INPUT_FILE, inNormalization);

    TreeFileElimination<2> _endingEliminator2D;
    _endingEliminator2D.process(_endingsAnalyzer2D, inEndThreshold);

    TreeFileElimination<3> _endingEliminator3D;
    _endingEliminator3D.process(_endingsAnalyzer3D, inEndThreshold);

    _endingEliminator2D.eliminate(_globalEliminator2D);
    _endingEliminator3D.eliminate(_globalEliminator3D);
    _endingEliminator3D.eliminate(_endingEliminator2D);

    _endingEliminator2D.write(_uniqueDir + ENDING_ELIMINATE_IO_FILE_2D);
    _endingEliminator3D.write(_uniqueDir + ENDING_ELIMINATE_IO_FILE_3D);

#ifdef WRITE_CSV
    _endingEliminator3D.writeToCSV(inUniqueDir + ENDING_ELIMINATE_CSV_FILE_3D);
    _endingEliminator2D.writeToCSV(inUniqueDir + ENDING_ELIMINATE_CSV_FILE_2D);
#endif
  }
#endif // ENDING_OCCURENCES

#ifdef START_OCCURENCES
  {
    StartAnalyzer<2> _startAnalyzer2D;
    _startAnalyzer2D.analyze(INPUT_FILE, inNormalization);

    StartAnalyzer<3> _startAnalyzer3D;
    _startAnalyzer3D.analyze(INPUT_FILE, inNormalization);

    TreeFileElimination<2> _eliminator2D;
    _eliminator2D.process(_startAnalyzer2D, inStartThresholds);

    TreeFileElimination<3> _eliminator3D;
    _eliminator3D.process(_startAnalyzer3D, inStartThresholds);

    _eliminator2D.eliminate(_globalEliminator2D);

    _eliminator3D.eliminate(_globalEliminator3D);
    _eliminator3D.eliminate(_eliminator2D);

    _eliminator2D.write(_uniqueDir + START_ELIMINATE_IO_FILE_2D);
    _eliminator3D.write(_uniqueDir + START_ELIMINATE_IO_FILE_3D);

#ifdef WRITE_CSV
    _eliminator2D.writeToCSV(inUniqueDir + START_ELIMINATE_CSV_FILE_2D);
    _eliminator3D.writeToCSV(inUniqueDir + START_ELIMINATE_CSV_FILE_3D);
#endif
  }
#endif // START_OCCURENCES
}

int main (int argc, char *argv[])
{
  generateVowelStats();
  generateGeneralStats();
  generateCharOccurenceStats();
//  std::vector<std::thread> _threads;

//  for(int _threshold(20); _threshold < 40; _threshold++)
//  {
//    _threads.push_back(std::thread(run, _threshold, _threshold, _threshold, 10));
//  }
//  for(int _threshold(20); _threshold < 40; _threshold++)
//  {
//      _threads.push_back(std::thread(run, _threshold, _threshold, _threshold, -1));
//  }
//  for(int _startThreshold(0); _startThreshold < 20; _startThreshold++)
//  {
//    for(int _endThreshold(0); _endThreshold < 20; _endThreshold++)
//    {
//      for(int _globalThreshold(0); _globalThreshold < 20; _globalThreshold++)
//      {
//        _threads.push_back(std::thread(run, _startThreshold, _endThreshold, _globalThreshold, -1));
////        std::thread _t(run, _startThreshold, _endThreshold, _globalThreshold, -1));
////        run(_startThreshold, _endThreshold, _globalThreshold, -1);
//      }
//    }
//  }

//  for(auto _it(_threads.begin()); _it != _threads.end(); _it++)
//  {
//    _it->join();
//  }
}
