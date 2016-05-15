#pragma once

class Converter{
public:
  static bool fromChar(char c, unsigned int & value);
  static bool fromValue(unsigned int value, char & c);

private:
  Converter();// pure static
};
