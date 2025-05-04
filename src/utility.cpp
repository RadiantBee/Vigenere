/** @file */
#include "utility.h"
#include <cctype>
#include <fstream>
#include <string>

/**
 * @brief Finds the next valid index in the key string.
 *
 * This function increments the index until it points to a valid lowercase alphabetical character.
 * Returns -1 if no valid characters are found.
 *
 * @param key The key string to iterate through.
 * @param currentIndex The current index in the key string.
 * @return long long int The next valid index, or -1 if none exist.
 */
long long int nextValidKeyIndex(const std::string &key, long long int currentIndex)
{
    do
    {
        ++currentIndex;
        if (currentIndex >= (long long int)key.length())
            return -1;
    } while (key[currentIndex] < 'a' || key[currentIndex] > 'z');
    return currentIndex;
}

/**
 * @brief Reads the key data from a file into a string.
 *
 * This function reads the contents of the specified file and stores the data in the provided key string.
 *
 * @param filename The name of the file containing the key.
 * @param key The string where the key data will be stored.
 * @return bool True if the key data is successfully read, false otherwise.
 */
bool getKeyDataFromFile(const std::string &filename, std::string& key)
{
    std::string readBuff;
    key = "";

    std::ifstream inFile(filename);

    if (!inFile)
    {
        std::cerr << "Error! Couldn't read from [" << filename << "] file!\n";
        return false;
    }

    while (inFile >> readBuff)
    {
        key += readBuff;
    }
    inFile.close();
    return true;
}

/**
 * @brief Reads text data from a file into a string.
 *
 * This function reads the contents of a file line by line and appends it to the provided string.
 *
 * @param filename The name of the file containing the text data.
 * @param textData The string where the text data will be stored.
 * @return bool True if the text data is successfully read, false otherwise.
 */
bool getTextDataFromFile(const std::string& filename, std::string& textData)
{
    std::string readBuff;
    textData = "";

    std::ifstream inFile(filename);

    if (!inFile)
    {
        std::cerr << "Error! Couldn't read from [" << filename << "] file!\n";
        return false;
    }

    while (std::getline(inFile, readBuff))
    {
        textData += readBuff + "\n";
    }
    inFile.close();
    return true;
}

/**
 * @brief Converts a string to lowercase.
 *
 * This function modifies the provided string by converting all uppercase letters to their lowercase equivalents.
 *
 * @param str The string to convert to lowercase.
 */
void stringToLowercase(std::string& str)
{
    for (char &c : str)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c += 32;
        }
    }
}

/**
 * @brief Saves data to a file.
 *
 * Writes the provided data to a file with the specified filename.
 *
 * @param filename The name of the file to save the data.
 * @param data The string data to be written to the file.
 * @return bool True if the data is successfully saved, false otherwise.
 */
bool saveToFile(const std::string& filename, const std::string& data)
{
    std::ofstream outFile(filename);
    if (outFile)
    {
        outFile << data;
        outFile.close();
        return true;
    }
    std::cerr << "Error! Couldn't write to [" << filename << "] file!\n";
    return false;
}

/**
 * @brief Extracts raw alphabetical text from a file.
 *
 * This function reads a file, filters out non-alphabetical characters, and converts uppercase characters to lowercase.
 *
 * @param filename The name of the file to process.
 * @param rawText The string where the raw text will be stored.
 */
void fillRawText(const std::string& filename, std::string& rawText)
{
    std::ifstream inFile(filename);
    std::string buff;
    while (inFile >> buff)
    {
        for (char c : buff)
        {
            if (isupper(c))
            {
                c = tolower(c);
            }
            if (islower(c))
            {
                rawText += c;
            }
        }
    }
    inFile.close();
}

/**
 * @brief Fills a frequency table based on the text.
 *
 * This function updates the provided frequency table based on the occurrence of each letter in the raw text.
 *
 * @param rawText The input text to analyze.
 * @param frequencyTable An array to store the frequency of each letter.
 */
void fillFrequencyTableFromText(const std::string& rawText, long long unsigned int* frequencyTable)
{
    for (char c : rawText)
    {
        frequencyTable[c - ASCII_TEXT_MARGIN]++;
    }
}

/**
 * @brief Decrypts text data using a Vigenère cipher key.
 *
 * This function decrypts the input data using the provided key and modifies the data in place.
 *
 * @param inputData The encrypted text to decrypt.
 * @param key The Vigenère cipher key.
 */
void decrypt(std::string& inputData, const std::string& key)
{
    long long int keyIndex = 0;
    for (char &c : inputData)
    {
        if (c >= 'a' && c <= 'z')
        {
            if (c - key[keyIndex] + ASCII_TEXT_MARGIN < 'a')
                c -= key[keyIndex] - ASCII_TEXT_MARGIN - 26;
            else
                c -= key[keyIndex] - ASCII_TEXT_MARGIN;
            keyIndex = nextValidKeyIndex(key, keyIndex);

            if (keyIndex == -1)
                keyIndex = 0;
        }
    }
}

/**
 * @brief Determines the Caesar cipher key for a given text group.
 *
 * Analyzes the input data and determines the most likely Caesar cipher key by comparing letter frequencies.
 *
 * @param inputData The text to analyze.
 * @param frequencyTable A frequency table to be used during analysis.
 * @return char The most likely Caesar cipher key.
 */
char getCaesarKey(std::string& inputData, long long unsigned int* frequencyTable)
{
    memset(frequencyTable, 0, 26 * sizeof(frequencyTable[0]));
    fillFrequencyTableFromText(inputData, frequencyTable);

    int mostFrequentPos = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (frequencyTable[i] > frequencyTable[mostFrequentPos])
        {
            mostFrequentPos = i;
        }
    }
    return (char)((mostFrequentPos + 'a' - 'e' + 26) % 26) + 'a';
}

/**
 * @brief Calculates the index of coincidence for a frequency table.
 *
 * This metric is used to analyze the likelihood of a particular key length in cryptographic analysis.
 *
 * @param frequencyTable A table of letter frequencies.
 * @return double The calculated index of coincidence.
 */
double getIndexOfCoincidence(long long unsigned int* frequencyTable)
{
    long long unsigned int total = 0;
    long long unsigned int sum = 0;
    for (int i = 0; i < 26; ++i)
    {
        sum += frequencyTable[i] * (frequencyTable[i] - 1);
        total += frequencyTable[i];
    }
    return (double)(26 * sum) / (total * (total - 1));
}

/**
 * @brief Determines the likely key length for a Vigenère cipher.
 *
 * Analyzes the input text and determines the most likely key length based on statistical analysis.
 *
 * @param rawText The text to analyze.
 * @return long long unsigned int The most likely key length, or 0 if none is found.
 */
long long unsigned int getKeyLength(const std::string& rawText)
{
    long long unsigned int period = 0;
    double sum = 0;
    std::string groupText;
    long long unsigned int localFrequencyTable[26];
    while (period < rawText.length())
    {
        ++period;
        sum = 0;
        for (long long unsigned int group = 0; group < period; ++group)
        {
            groupText = "";
            memset(localFrequencyTable, 0, 26 * sizeof(localFrequencyTable[0]));
            for (long long unsigned int i = group; i < rawText.length(); i += period)
            {
                groupText += rawText[i];
            }
            fillFrequencyTableFromText(groupText, localFrequencyTable);
            sum += getIndexOfCoincidence(localFrequencyTable);
        }
        if (sum / period > 1.68)
        {
            return period;
        }
    }
    return 0;
}

/**
 * @brief Prints help information about the program's usage.
 *
 * Displays the supported flags, their purposes, and example usage.
 */
void printHelp()
{
    std::cout << "VEDB: Vigenere encryptor, decryptor and breaker.\n";
    std::cout << "Performs operations on files in local directory.\n";
    std::cout << "List of flags:\n";
    std::cout << "-en           Encryption mode\n";
    std::cout << "-de           Decryption mode\n";
    std::cout << "-br           Breaker mode\n";
    std::cout << "-i [filename] Input text file\n";
    std::cout << "-o [filename] Output text file\n";
    std::cout << "-k [filename] Key text file\n";
    std::cout << "Examples: \n";
    std::cout << "To encrypt file:\n";
    std::cout << "./main -en -i fileForEncryption -k keyFile -o encryptedFile\n";
    std::cout << "./main -de -i encryptedFile -k keyFile -o decryptedFile\n";
    std::cout << "./main -br -i fileForBreaking -o encryptedFile\n";
    std::cout << "Note that flags can be placed without a particular order.\n";
}

/**
 * @brief Parses command-line arguments to configure the program.
 *
 * Parses and validates command-line arguments for setting operation mode, input file,
 * output file, and key file paths.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param mode A reference to store the chosen mode.
 * @param inputFile A reference to store the input file path.
 * @param outputFile A reference to store the output file path.
 * @param keyFile A reference to store the key file path.
 * @return bool True if arguments are successfully parsed, false otherwise.
 */
bool parceArguments(int argc, char** argv, std::string& mode, std::string& inputFile, std::string& outputFile, std::string& keyFile)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string str = argv[i];
        if (str == "-en" || str == "-de" || str == "-br")
        {
            mode = str;
        }
        else if (str == "-i")
        {
            if (i + 1 < argc)
                inputFile = argv[++i];
        }
        else if (str == "-o")
        {
            if (i + 1 < argc)
                outputFile = argv[++i];
        }
        else if (str == "-k")
        {
            if (i + 1 < argc)
                keyFile = argv[++i];
        }
    }

    if (mode.empty() || inputFile.empty() || outputFile.empty())
        return false;

    if (mode != "-br" && keyFile.empty())
        return false;

    return true;
}
