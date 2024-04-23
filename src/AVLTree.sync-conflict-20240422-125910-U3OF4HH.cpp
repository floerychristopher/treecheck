#include "AVLTree.h"

// A utility function to get the
// height of the tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, int key, ofstream& logFile)
{
    if (node == NULL) {
        return newNode(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, logFile);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, logFile);
    }
    else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    logFile << "bal(" << node->key << ") = " << balance;
    if (balance > 1 || balance < -1) {
        logFile << " (AVL violation!)";
    }

    logFile << endl;
    // HIER STEHENGEBLIEBEN. FÜR NÄCHSTES MAL: ROTATIONS GENAU LERNEN
    // UND CODE DARUNTER VERGLEICHEN VERSTEHEN
    // Right rotation
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    // Left rotation
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    // Left-right rotation
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right-left rotation
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool isAVLTree(Node* root)
{
    if (root == NULL)
        return true;
    int balance = getBalance(root);
    return (abs(balance) <= 1) && isAVLTree(root->left) && isAVLTree(root->right);
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
// A utility function to print preorder
// traversal of the tree.
// The function also prints height
// of every node
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
    }
}
