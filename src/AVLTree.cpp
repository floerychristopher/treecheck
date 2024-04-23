#include "AVLTree.h"

// get height of tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

// create new node
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    node->balance = 0;
    return(node);
}

// Get Balance factor of node N
int getBalance(Node* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Recursive function to insert a key in subtree rooted
// with node and returns the new root of the subtree.
Node* insert(Node* node, int key, ofstream& logFile)
{
    // if node isn't part of the tree yet
    if (node == NULL) {
        return newNode(key);
    }

    if (key > node->key) {
        node->left = insert(node->left, key, logFile);
    } else if (key < node->key) {
        node->right = insert(node->right, key, logFile);
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

// Function to perform inorder traversal and compute statistics
void inorderStats(Node* root, ofstream& logFile, int& minBalance, int& maxBalance, int& totalBalance, int& nodeCount) {
    if (root != NULL) {
        inorderStats(root->left, logFile, minBalance, maxBalance, totalBalance, nodeCount);
        int balance = getBalance(root);
        logFile << "bal(" << root->key << ") = " << balance << endl;
        minBalance = min(minBalance, balance);
        maxBalance = max(maxBalance, balance);
        totalBalance += balance;
        nodeCount++;
        inorderStats(root->right, logFile, minBalance, maxBalance, totalBalance, nodeCount);
    }
}

void reversePreorderTraversal(Node* node, ofstream& logFile, int smallestKey, int biggestKey) {
    if (node == nullptr) {
            return;
    }
    reversePreorderTraversal(node->left, logFile, smallestKey, biggestKey);
    reversePreorderTraversal(node->right, logFile, smallestKey, biggestKey);
    logFile << "bal(" << node->key << ") = " << node->balance;
    if (node->balance > 1 || node->balance < -1) {
        logFile << " (AVL violation!)";
    }
    logFile << endl;

    if (node->key < smallestKey) {
        smallestKey = node->key;
    }

    if (node->key > biggestKey) {
        biggestKey = node->key;
    }
}

int getBiggestKey(Node* node, int& biggestKey) {
    if (node == nullptr) {
        return INT_MIN;
    }

    getBiggestKey(node->right, biggestKey);
    getBiggestKey(node->left, biggestKey);

    if (node->key > biggestKey) {
        biggestKey = node->key;
    }

    return biggestKey;
}

int getSmallestKey(Node* node, int& smallestKey) {
    if (node == nullptr) {
        return INT_MIN;
    }

    getSmallestKey(node->right, smallestKey);
    getSmallestKey(node->left, smallestKey);

    if (node->key < smallestKey) {
        smallestKey = node->key;
    }

    return smallestKey;
}

void getSum(Node* node, int& sum) {
    if (node == nullptr) {
        return;
    }

    getSum(node->right, sum);
    getSum(node->left, sum);

    sum += node->key;
}

int countNodes(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    int leftCount = countNodes(node->left);
    int rightCount = countNodes(node->right);

    return leftCount + rightCount + 1;
}
