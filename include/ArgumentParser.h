#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <string>

// Function to display usage information
void printUsage();

// Function to parse command-line arguments
bool parseArguments(int argc, char *argv[], std::string &mode, std::string &inputFile, std::string &outputFile);

#endif // ARGUMENTPARSER_H
