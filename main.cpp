#include "AVLTree.h"
#include <iostream>
#include <fstream>

int main()
{
    Node *root = NULL;
    int key;

    // Open and check input file
    std::string inputFileName;
    std::cout << "Enter the name of the input file: ";
    std::cin >> inputFileName;
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << inputFileName << std::endl;
        return 1;
    }

    // Open and check log file
    std::ofstream logFile("log.txt");
    if (!logFile) {
        std::cerr << "Error: Unable to open log file for writing" << std::endl;
        return 1;
    }

    // Read integers from file as long as possible and insert them into binary search tree
    while (inputFile >> key) {
        root = insert(root, key, logFile);
    }

    int smallestKey = INT_MAX;
    int biggestKey = INT_MIN;
    std::string isAVL;
    // Traverse binary search tree
    reversePreorderTraversal(root, logFile, smallestKey, biggestKey);
    biggestKey = getBiggestKey(root, biggestKey);
    smallestKey = getSmallestKey(root, smallestKey);
    double average = static_cast<double>(smallestKey + biggestKey) / 2;
    if (isAVLTree(root)) {
        isAVL = "yes";
    } else {
        isAVL = "no";
    }
    logFile << "isAVL: " << isAVL;
    logFile << std::endl;
    logFile << "min: " << smallestKey << ", max: " << biggestKey << ", avg: " << average;
    logFile << std::endl;


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
