#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <bits/stdc++.h>
using namespace std;

// Tree node
class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
    int balance;
};

int height(Node *N);
int max(int a, int b);
Node* newNode(int key);
int getBalance(Node *N);
Node* insertInBinSearchTree(Node* node, int key, ofstream& logFile);
bool isAVLTree(Node* root);
void reversePreorderTraversal(Node* root, ofstream& logFile);
void printStats(Node* root, ofstream& logFile);
int getBiggestKey(Node* root);
int getSmallestKey(Node* root);
int getSum(Node* node);
int countNodes(Node* node);

#endif /* AVL_TREE_H */
