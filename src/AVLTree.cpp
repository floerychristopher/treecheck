#include "AVLTree.h"

// Get height of tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

// Create new node
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->balance = 0;
    return(node);
}

// Get Balance factor of node
int getBalance(Node* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Recursive function to insert a key in subtree rooted
// with node (returns new root of the subtree)
Node* insertInBinSearchTree(Node* node, int key, ofstream& logFile)
{
    // if node isn't part of the tree yet
    if (node == NULL) {
        return newNode(key);
    }

    if (key > node->key) {
        node->left = insertInBinSearchTree(node->left, key, logFile);
    } else if (key < node->key) {
        node->right = insertInBinSearchTree(node->right, key, logFile);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    node->balance = getBalance(node);

    return node;
}

bool isAVLTree(Node* root)
{
    if (root == NULL)
        return true;
    int balance = getBalance(root);
    return (balance <= 1 && balance >= -1) && isAVLTree(root->left) && isAVLTree(root->right);
}

void reversePreorderTraversal(Node* node, ofstream& logFile) {
    if (node == nullptr) {
            return;
    }
    reversePreorderTraversal(node->left, logFile);
    reversePreorderTraversal(node->right, logFile);
    logFile << "bal(" << node->key << ") = " << node->balance;
    if (node->balance > 1 || node->balance < -1) {
        logFile << " (AVL violation!)";
    }
    logFile << endl;
}

void printStats(Node* root, ofstream& logFile)
{
    double average = (double)getSum(root) / countNodes(root);

    std::string isAVL;
    isAVLTree(root) ? isAVL = "yes" : isAVL = "no";

    logFile << "isAVL: " << isAVL;
    logFile << std::endl;

    logFile << "min: " << getSmallestKey(root) << ", max: " << getBiggestKey(root) << ", avg: " << average;
    logFile << std::endl;
}

int getBiggestKey(Node* node)
{
    if (node == nullptr) {
        return INT_MIN;
    }

    int biggestKey = node->key;

    int rightBiggest = getBiggestKey(node->right);
    int leftBiggest = getBiggestKey(node->left);

    if (rightBiggest > biggestKey) {
        biggestKey = rightBiggest;
    }

    if (leftBiggest > biggestKey) {
        biggestKey = leftBiggest;
    }

    return biggestKey;
}

int getSmallestKey(Node* node) {
    if (node == nullptr) {
        return INT_MAX;
    }

    int smallestKey = node->key;

    int rightSmallest = getSmallestKey(node->right);
    int leftSmallest = getSmallestKey(node->left);

    if (rightSmallest < smallestKey) {
        smallestKey = rightSmallest;
    }

    if (leftSmallest < smallestKey) {
        smallestKey = leftSmallest;
    }

    return smallestKey;
}

int getSum(Node* node)
{
    if (node == nullptr) {
        return 0;
    }

    int sum = 0;

    sum += getSum(node->right);
    sum += getSum(node->left);

    return sum += node->key;
}

int countNodes(Node* node)
{
    if (node == nullptr) {
        return 0;
    }

    int leftCount = countNodes(node->left);
    int rightCount = countNodes(node->right);

    return leftCount + rightCount + 1;
}
