#include "../include/FrequencyUtils.h"
#include <fstream>
#include <iostream>

std::unordered_map<char, int> calculateFrequencies(const std::string &filename)
{
  std::unordered_map<char, int> frequencies;
  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open())
  {
    std::cerr << "Error opening input file for frequency calculation: " << filename << std::endl;
    return frequencies;
  }

  char ch;
  while (file.get(ch))
  {
    frequencies[ch]++;
  }

  file.close();
  return frequencies;
}
