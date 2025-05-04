/** @file */
#include "encryptor.h"
#include "utility.h"

/**
 * @brief Encrypts the input file data using a specified key and saves the result to an output file.
 *
 * This function reads the plain text data and the encryption key from the specified files, performs the 
 * encryption by shifting each character based on the key, and then writes the encrypted data to the output file.
 *
 * @param inputFile The path to the file containing the plain text data.
 * @param outputFile The path to the file where the encrypted data will be saved.
 * @param keyFile The path to the file containing the encryption key.
 * @return Returns 0 if the encryption was successful, or -1 if an error occurred during the process (e.g., 
 *         invalid key or file reading issues).
 */
int encrypt(const std::string& inputFile, const std::string& outputFile, const std::string& keyFile)
{
    std::string inputData;
    std::string key;

    // Reading input data from files
    if(!getTextDataFromFile(inputFile, inputData) || !getKeyDataFromFile(keyFile, key))
        return -1;

    // Converting both input data and key to lowercase
    stringToLowercase(inputData);
    stringToLowercase(key);

    // Checking if the key is valid
    if(nextValidKeyIndex(key, -1) == -1)
    {
        std::cerr << "Error! Invalid key!\n";
        return -1;
    }

    // Encoding every character based on the key
    long long int keyIndex = 0;
    for(char &c : inputData)
    {
        if(c > 96 && c < 123) // Ensure the character is lowercase
        {
            // Shift the character by the key value, accounting for wraparound in the alphabet
            if(c + key[keyIndex] - ASCII_TEXT_MARGIN > 122)
                c += key[keyIndex] - ASCII_TEXT_MARGIN - 26;
            else
                c += key[keyIndex] - ASCII_TEXT_MARGIN;

            // Update the key index for the next character
            keyIndex = nextValidKeyIndex(key, keyIndex);

            // If no valid key index is found, reset the key index
            if(keyIndex == -1)
                keyIndex = 0;
        }
    }

    // Writing the encrypted data to the output file
    return saveToFile(outputFile, inputData) - 1;
}

