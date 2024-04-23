#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <bits/stdc++.h>
using namespace std;

// tree node
class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
    int balance;
};

// Functions
int height(Node *N);
int max(int a, int b);
Node* newNode(int key);
int getBalance(Node *N);
Node* insert(Node* node, int key, ofstream& logFile);
bool isAVLTree(Node* root);
void inorderStats(Node* root, ofstream& logFile, int& minBalance, int& maxBalance, int& totalBalance, int& nodeCount);
void reversePreorderTraversal(Node* root, ofstream& logFile, int smallestKey, int biggestKey);
int getBiggestKey(Node* root, int& biggestKey);
int getSmallestKey(Node* root, int& smallestKey);

#endif /* AVL_TREE_H */
