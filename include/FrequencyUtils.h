#ifndef FREQUENCY_UTILS_H
#define FREQUENCY_UTILS_H

#include <unordered_map>
#include <string>

// Function to calculate frequencies of characters in a file
std::unordered_map<char, int> calculateFrequencies(const std::string &filename);

#endif // FREQUENCY_UTILS_H
