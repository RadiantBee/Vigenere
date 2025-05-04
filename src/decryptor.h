/** @file */
#pragma once
#include "utility.h"

/**
 * @brief Decrypts an input file using the provided key.
 *
 * This function reads an encrypted file and decrypts its contents using the key
 * specified in the key file. The decrypted output is saved to the specified output file.
 *
 * @param inputFile The path to the encrypted input file.
 * @param outputFile The path to the output file where decrypted content will be saved.
 * @param keyFile The path to the key file containing the decryption key.
 * @return int Returns 0 on successful decryption, or a non-zero error code on failure.
 */
int decrypt(const std::string& inputFile, const std::string& outputFile, const std::string& keyFile);
