#include "../include/FileComparisonUtils.h"
#include <fstream>
#include <iostream>

bool compareFiles(const std::string &file1, const std::string &file2)
{
  std::ifstream f1(file1, std::ios::binary | std::ios::ate);
  std::ifstream f2(file2, std::ios::binary | std::ios::ate);

  if (!f1.is_open() || !f2.is_open())
  {
    std::cerr << "Error opening files for comparison." << std::endl;
    return false;
  }

  // Check if file sizes are different
  if (f1.tellg() != f2.tellg())
  {
    return false;
  }

  // Seek back to the beginning
  f1.seekg(0);
  f2.seekg(0);

  // Compare byte by byte
  char ch1, ch2;
  while (f1.get(ch1) && f2.get(ch2))
  {
    if (ch1 != ch2)
    {
      return false;
    }
  }

  return true;
}
