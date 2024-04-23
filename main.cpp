#include "AVLTree.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    // Check if number of arguments is 2
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " Treechecker" << std::endl;
        return 1;
    }

    // Declare root pointer and key
    Node* root = nullptr;
    int key;

    // Open and check input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    // Open and check log file
    std::ofstream logFile("log.txt");
    if (!logFile) {
        std::cerr << "Error: Unable to open log file for writing" << std::endl;
        return 1;
    }

    // Read keys from file as long as possible and insert them into binary search tree (build tree)
    while (inputFile >> key) {
        // Update the pointer (root) after every insertion
        root = insertInBinSearchTree(root, key, logFile);
    }

    // Traverse binary search tree
    reversePreorderTraversal(root, logFile);

    // Print stats of binary search tree
    printStats(root, logFile);

    inputFile.close();
    logFile.close();

    // Open the log file for reading and print its contents
    std::ifstream readLogFile("log.txt");
    if (readLogFile) {
        std::cout << "Log file contents:" << std::endl;
        std::string line;
        while (std::getline(readLogFile, line)) {
            std::cout << line << std::endl;
        }
        readLogFile.close();
    } else {
        std::cerr << "Error: Unable to open log file for reading" << std::endl;
        return 1;
    }

    std::cout << "Binary search tree construction and analysis completed." << std::endl;

    return 0;
}
