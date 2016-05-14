#pragma once


#include <vector>
#include <string>
#include <fstream>

class FileUtils
{
public:
  static unsigned char* toBin(unsigned int value, int n_bytes = 4);
  static unsigned char* toBin(float value, int n_bytes = 4);

  static int readInt32(unsigned char * data, int n_bytes = 4);
  static float readFloat32(unsigned char * data, int n_bytes = 4);

  static void insertPadding(unsigned char * data, int from, int to);

  static bool open(const std::string & inFilename, std::ios_base::openmode inOpenMode, std::ofstream & outFile);

};

