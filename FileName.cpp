#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};
class AVLTree {
private:
    Node* root;
    int getHeight(Node* node) {
        return (node != nullptr) ? node->height : 0;
    }
    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else {
            return node; 
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);
        // Left Heavy
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }
        // Right Heavy
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }
        // Left Right Heavy
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right Left Heavy
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
public:
    AVLTree() : root(nullptr) {}
    void insert(int value) {
        root = insert(root, value);
    }
    void inOrderTraversal() {
        inOrderTraversal(root);
    }
};
int main() {
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.inOrderTraversal();
    cout << endl;

}