/** @file */
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

/**
 * @brief ASCII margin value for text processing.
 */
const int ASCII_TEXT_MARGIN = 97;

/**
 * @brief Percent frequency of every letter in English text.
 */
const double FREQUENCY_TABLE[] = {
  0.08167, 0.01492, 0.02782, 0.04253, 0.02702, 0.02228, 0.02015, 0.06094,
  0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
  0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
  0.01975, 0.00074
};

/**
 * @brief Computes the Index of Coincidence for a frequency table.
 * @param frequencyTable The frequency table to analyze.
 * @return The Index of Coincidence.
 */
double getIndexOfCoincidence(long long unsigned int*frequencyTable);

/**
 * @brief Decrypts input data using the given key.
 * @param inputData The data to be decrypted.
 * @param key The decryption key.
 */
void decrypt(std::string& inputData, const std::string& key);

/**
 * @brief Determines the Caesar cipher key from input data.
 * @param inputData The data to analyze.
 * @param frequencyTable The frequency table to use for analysis.
 * @return The determined Caesar cipher key.
 */
char getCaesarKey(std::string& inputData, long long unsigned int* frequencyTable);

/**
 * @brief Reads raw text from a file into a string.
 * @param filename The name of the file to read.
 * @param rawText The string to store the raw text.
 */
void fillRawText(const std::string& filename, std::string& rawText);

/**
 * @brief Populates a frequency table from the given text.
 * @param rawText The text to analyze.
 * @param frequencyTable The frequency table to populate.
 */
void fillFrequencyTableFromText (const std::string& rawText , long long unsigned int* frequencyTable);

/**
 * @brief Determines the key length of the given text.
 * @param rawText The text to analyze.
 * @return The determined key length.
 */
long long unsigned int getKeyLength(const std::string& rawText);

/**
 * @brief Finds the next valid key index.
 * @param key The key string to analyze.
 * @param currentIndex The current index to start from.
 * @return The next valid key index, or -1 if none are found.
 */
long long int nextValidKeyIndex(const std::string &key, long long int currentIndex);

/**
 * @brief Saves data to a file with a chosen separator.
 * @param filename The name of the file to save to.
 * @param data The data to save.
 * @return True if the save operation succeeds, false otherwise.
 */
bool saveToFile(const std::string& filename, const std::string& data);

/**
 * @brief Converts every character of a string to its lowercase version.
 * @param str The string to convert.
 */
void stringToLowercase(std::string& str);

/**
 * @brief Reads text data from a file.
 * @param filename The name of the file to read.
 * @param textData The string to store the text data.
 * @return True if the operation succeeds, false otherwise.
 */
bool getTextDataFromFile(const std::string& filename, std::string& textData);

/**
 * @brief Reads key data from a file.
 * @param filename The name of the file to read.
 * @param key The string to store the key data.
 * @return True if the operation succeeds, false otherwise.
 */
bool getKeyDataFromFile(const std::string& filename, std::string& key);

/**
 * @brief Prints help information to the console.
 */
void printHelp();

/**
 * @brief Parses command-line arguments and extracts required values.
 * @param argc The number of arguments.
 * @param argv The array of argument strings.
 * @param mode The mode of operation (e.g., "-en", "-de", "-br").
 * @param inputFile The input file path.
 * @param outputFile The output file path.
 * @param keyFile The key file path.
 * @return True if arguments are parsed successfully, false otherwise.
 */
bool parceArguments(int argc, char** argv, std::string& mode, std::string& inputFile, std::string& outputFile, std::string& keyFile);

