/** @file */
#pragma once
#include "utility.h"

/**
 * @brief Encrypts an input file using the provided key.
 *
 * This function reads a plaintext file and encrypts its contents using the key
 * specified in the key file. The encrypted output is saved to the specified output file.
 *
 * @param inputFile The path to the plaintext input file.
 * @param outputFile The path to the output file where encrypted content will be saved.
 * @param keyFile The path to the key file containing the encryption key.
 * @return int Returns 0 on successful encryption, or a non-zero error code on failure.
 */
int encrypt(const std::string& inputFile, const std::string& outputFile, const std::string& keyFile);
