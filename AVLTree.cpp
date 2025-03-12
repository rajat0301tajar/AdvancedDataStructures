// AVL Tree implementation

#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data, height;
    Node *left, *right;

    Node(int val) {
        data = val;
        height = 1;  // New node is initially at height 1
        left = right = nullptr;
    }
};

// AVL Tree class
class AVLTree {
public:
    Node* insert(Node* root, int key);
    Node* deleteNode(Node* root, int key);
    void inorder(Node* root);

private:
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* getMinValueNode(Node* node);
};

// Get height of a node
int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0;
}

// Get Balance Factor of a node
int AVLTree::getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right Rotate (LL Case)
Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left Rotate (RR Case)
Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Balance the tree after insertion or deletion
Node* AVLTree::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    // Left Heavy (LL or LR)
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) // LR Case
            node->left = rotateLeft(node->left);
        return rotateRight(node); // LL Case
    }

    // Right Heavy (RR or RL)
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) // RL Case
            node->right = rotateRight(node->right);
        return rotateLeft(node); // RR Case
    }

    return node; // No balancing needed
}

// Insert a node
Node* AVLTree::insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        return root; // No duplicates allowed

    // Update height and balance
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return balance(root);
}

// Get node with the minimum value (for deletion)
Node* AVLTree::getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

// Delete a node
Node* AVLTree::deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // One or No Child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) { // No child
                temp = root;
                root = nullptr;
            } else // One child
                *root = *temp;
            delete temp;
        } else {
            // Two children: Get inorder successor
            Node* temp = getMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (!root) return root; // Tree had only one node

    // Update height and balance
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return balance(root);
}

// Inorder Traversal
void AVLTree::inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Main function
int main() {
    AVLTree tree;
    Node* root = nullptr;

    root = tree.insert(root, 10);
    root = tree.insert(root, 20);
    root = tree.insert(root, 30);
    root = tree.insert(root, 25);
    root = tree.insert(root, 40);
    root = tree.insert(root, 50);

    cout << "Inorder traversal after insertion:\n";
    tree.inorder(root);
    cout << endl;

    root = tree.deleteNode(root, 30);
    cout << "Inorder traversal after deletion of 30:\n";
    tree.inorder(root);
    cout << endl;

    return 0;
}
