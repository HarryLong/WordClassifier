#include "converter.h"
#include "constants.h"

bool Converter::fromChar(char c, unsigned int & value)
{
  value = (unsigned int) c;

  if(value >= Constants::sAsciiSmallCaseMin && value <= Constants::sAsciiSmallCaseMax) // Lowercase
  {
    value -= Constants::sAsciiSmallCaseMin;
    return true;
  }

  if(value >= Constants::sAsciiUpperCaseMin && value <= Constants::sAsciiUpperCaseMax) // Uppercase
  {
    value -= Constants::sAsciiUpperCaseMin;
    return true;
  }

  if(value == Constants::sAsciiAprostrophe ) // Apostrophe
  {
    value = Constants::sAprostropheValue; // hard coded
    return true;
  }
  return false; // Invalid char
}

bool Converter::fromValue(unsigned int value, char & c)
{
  if(value == Constants::sAprostropheValue)
  {
    c = '\'';
    return true;
  }
  if(value >= 0 && value < 26)
  {
    c = (char) (value + Constants::sAsciiSmallCaseMin);
    return true;
  }
  return false;
}
