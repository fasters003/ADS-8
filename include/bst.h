// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <algorithm>

template <typename T>
class BST {
public:
    struct Node {
        T value;
        int count;
        Node *left;
        Node *right;
        explicit Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    Node* addNode(Node* node, T value) {
        if (!node) return new Node(value);
        if (value == node->value) {
            node->count++;
        } else if (value < node->value) {
            node->left = addNode(node->left, value);
        } else {
            node->right = addNode(node->right, value);
        }
        return node;
    }

    int getDepth(Node* node) const {
        if (!node) return 0;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    int searchNode(Node* node, T value) const {
        if (!node) return 0;
        if (value == node->value) return node->count;
        if (value < node->value) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void add(T value) {
        root = addNode(root, value);
    }

    int depth() const {
        if (!root) return 0;
        return getDepth(root) - 2;
    }

    int search(T value) const {
        return searchNode(root, value);
    }

    Node* getRoot() const {
        return root;
    }
};

#endif  // INCLUDE_BST_H_
