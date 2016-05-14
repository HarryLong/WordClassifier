
#include <iostream>
#include "filemanager/tree_file.h"

int main (int argc, char *argv[])
{
    TreeFile _file;
    _file.generateDummyValues();
    _file.write("/home/harry/workspaces/qt-workspace/word-qualifier/resources/sample.io");
}
