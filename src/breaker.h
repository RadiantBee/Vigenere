/** @file */
#pragma once
#include "utility.h"

/**
 * @brief Attempts to break the encryption of a file.
 *
 * This function analyzes the target file and attempts to break its encryption,
 * saving the results to the specified output file. The exact breaking method
 * depends on the implementation in the source file.
 *
 * @param targetFile The path to the file to analyze and attempt to break.
 * @param outputFile The path where the results will be saved.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int breakFile(const std::string& targetFile, const std::string& outputFile);
