#include "../include/ArgumentParser.h"
#include "../include/FileUtils.h"
#include "../include/Handler.h"
#include <iostream>

int main(int argc, char *argv[])
{
  std::string mode;
  std::string inputFile;
  std::string outputFile;

  // Parse command-line arguments
  if (!parseArguments(argc, argv, mode, inputFile, outputFile))
  {
    return 1; // Exit if argument parsing fails or --help is displayed
  }

  // Ensure the output directory exists
  try
  {
    createDirectoryIfNotExists("output");
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error creating output directory: " << e.what() << std::endl;
    return 1;
  }

  // Perform the selected operation
  if (mode == "encode")
  {
    handleEncoding(inputFile, outputFile);
  }
  else if (mode == "decode")
  {
    handleDecoding(inputFile, outputFile);
  }

  return 0;
}
