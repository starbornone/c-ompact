#include "../include/ArgumentParser.h"
#include <iostream>

void printUsage()
{
  std::cout << "Usage: cppompact [options]\n"
            << "Options:\n"
            << "  --encode -e <input> <output>  Encode the input file to the output file.\n"
            << "  --decode -d <input> <output>  Decode the input file to the output file.\n"
            << "  --help   -h                   Show this help message.\n";
}

bool parseArguments(int argc, char *argv[], std::string &mode, std::string &inputFile, std::string &outputFile)
{
  if (argc < 2)
  {
    std::cerr << "Error: Missing arguments.\n";
    printUsage();
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg == "--encode" || arg == "-e")
    {
      if (i + 2 >= argc)
      {
        std::cerr << "Error: Missing input or output file for encoding.\n";
        printUsage();
        return false;
      }
      mode = "encode";
      inputFile = argv[++i];
      outputFile = argv[++i];
    }
    else if (arg == "--decode" || arg == "-d")
    {
      if (i + 2 >= argc)
      {
        std::cerr << "Error: Missing input or output file for decoding.\n";
        printUsage();
        return false;
      }
      mode = "decode";
      inputFile = argv[++i];
      outputFile = argv[++i];
    }
    else if (arg == "--help" || arg == "-h")
    {
      printUsage();
      return false;
    }
    else
    {
      std::cerr << "Error: Unknown option: " << arg << "\n";
      printUsage();
      return false;
    }
  }

  if (mode.empty())
  {
    std::cerr << "Error: No operation mode specified.\n";
    printUsage();
    return false;
  }

  return true;
}
