/** @file */
#include "breaker.h"
#include "utility.h"

/**
 * @brief Attempts to break the encryption of a file and write the decrypted output.
 * 
 * This function analyzes the encrypted file, determines the likely key length,
 * derives the encryption key, and decrypts the file. The result is saved to the output file.
 * 
 * @param targetFile The path to the encrypted file to be analyzed and decrypted.
 * @param outputFile The path to the file where decrypted content will be saved.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int breakFile(const std::string& targetFile, const std::string& outputFile)
{
    std::string cipher;
    std::string rawText;
    long long unsigned int keyLength;

    // Load encrypted text from file
    if (!getTextDataFromFile(targetFile, cipher))
        return -1;

    // Convert text to lowercase for analysis
    stringToLowercase(cipher);

    // Extract raw text from the file
    fillRawText(targetFile, rawText);

    // Determine the key length
    keyLength = getKeyLength(rawText);
    if (!keyLength)
    {
        std::cerr << "Error! Couldn't get the key length!\n";
        return saveToFile(outputFile, cipher);
    }

    // Determine the decryption key
    std::string key = "";
    std::string groupText;
    long long unsigned int localFrequencyTable[26];
    for (long long unsigned int group = 0; group < keyLength; ++group)
    {
        groupText = "";
        for (long long unsigned int i = group; i < rawText.length(); i += keyLength)
        {
            groupText += rawText[i];
        }
        key += getCaesarKey(groupText, localFrequencyTable);
    }

    // Output the derived key
    std::cout << "The key is: " << key << "\n";

    // Decrypt the cipher using the derived key
    decrypt(cipher, key);

    // Write the decrypted content to the output file
    return saveToFile(outputFile, cipher);
}

