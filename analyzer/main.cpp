
#include <iostream>
#include "filemanager/tree_file.h"

#define OUTPUT_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.io"
#define INPUT_FILE "/home/harry/workspaces/qt-workspace/word-qualifier/resources/words.txt"

int main (int argc, char *argv[])
{
    TreeFile _file;

//    _file.analyze(INPUT_FILE);
    _file.generateDummyValues();
    _file.write("/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.io");
}
