//** 
//*@file 
//* @details First semester project of InfAAu>SI1FoCP19 student at Silesian University of Technology
//* @author Maksym Pankin
//* @date 2024-2025
//*
//*/
#include "src/encryptor.h"
#include "src/decryptor.h"
#include "src/breaker.h"
#include "src/utility.h"

/**
 * @brief Entry point of the application.
 *
 * This program supports three modes of operation:
 * - Encryption: Encrypts the input file using a specified key.
 * - Decryption: Decrypts the input file using a specified key.
 * - Breaking: Attempts to break the encryption on the input file without a key.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 *        - Mode: Specify "-en" for encryption, "-de" for decryption, or "-br" for breaking.
 *        - InputFile: Path to the input file to process.
 *        - OutputFile: Path to save the processed output.
 *        - KeyFile: Path to the key file (required for encryption and decryption).
 *
 * @return Exit status of the program.
 *         - 0: Success.
 *         - 1: Invalid mode specified.
 *         - -1: Error in parsing arguments or execution.
 */
int main(int argc, char* argv[])
{
    std::string mode = "";
    std::string inputFile = "";
    std::string outputFile = "";
    std::string keyFile = "";

    //Parcing arguments and checking for errors
    if(!parceArguments(argc, argv, mode, inputFile, outputFile, keyFile))
    {
        printHelp();
        return -1;
    }

    //Invoking chosen mode
    if(mode == "-br")
    {
        return breakFile(inputFile, outputFile);
    }
    else if(mode == "-de")
    {
        return decrypt(inputFile, outputFile, keyFile);
    }
    else if(mode == "-en")
    {
        return encrypt(inputFile, outputFile, keyFile);
    }
    return 1;
}
