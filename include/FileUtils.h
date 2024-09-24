#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

// Function to check if a file exists and is readable
bool isFileReadable(const std::string &filename);

// Function to check if a file is writable or can be created
bool isFileWritable(const std::string &filename);

// Function to calculate the size of a file in bytes
std::size_t getFileSize(const std::string &filename);

// Function to ensure a directory exists or create it
void createDirectoryIfNotExists(const std::string &directory);

#endif // FILEUTILS_H
