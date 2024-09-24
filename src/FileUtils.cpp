#include "../include/FileUtils.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

bool isFileReadable(const std::string &filename)
{
  std::ifstream infile(filename);
  return infile.good();
}

bool isFileWritable(const std::string &filename)
{
  std::ofstream outfile(filename);
  return outfile.good();
}

std::size_t getFileSize(const std::string &filename)
{
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  if (!in)
  {
    throw std::runtime_error("Error: Could not open file: " + filename);
  }
  return in.tellg();
}

void createDirectoryIfNotExists(const std::string &directory)
{
#ifdef _WIN32
  _mkdir(directory.c_str());
#else
  mkdir(directory.c_str(), 0777);
#endif
}
