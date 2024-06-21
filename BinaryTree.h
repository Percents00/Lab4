#pragma once

#include "Vector.h"

template <typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        deleteTree(root);
    }

    template <typename R>
    R reduce(R(*func)(const R&, const T&), const R& initialValue) const {
        return reduceInternal(root, func, initialValue);
    }

    BinaryTree<T> where(bool (*predicate)(const T&)) const {
        BinaryTree<T> result;
        whereInternal(root, predicate, result);
        return result;
    }



    void insert(const T& data) {
        if (!root) {
            root = new Node(data);
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (data < parent->data) {
            parent->left = new Node(data);
        } else {
            parent->right = new Node(data);
        }
    }

    bool search(const T& data) const {
        Node* current = root;

        while (current) {
            if (data == current->data) {
                return true;
            } else if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return false;
    }

    void remove(const T& data) {
        root = deleteNode(root, data);
    }

    Vector<T> preOrderTraversal() const {
        Vector<T> result;
        preOrderTraversal(root, result);
        return result;
    }

    Vector<T> inOrderTraversal() const {
        Vector<T> result;
        inOrderTraversal(root, result);
        return result;
    }

    Vector<T> postOrderTraversal() const {
        Vector<T> result;
        postOrderTraversal(root, result);
        return result;
    }

private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    template <typename R>
    R reduceInternal(Node* node, R(*func)(const R&, const T&), const R& currentValue) const {
        if (!node) {
            return currentValue;
        }
        
        R  newCurrent = func(currentValue, node->data);
        newCurrent = reduceInternal(node->left, func, newCurrent);
        newCurrent = reduceInternal(node->right, func, newCurrent);
        return newCurrent;
    }


    void whereInternal(Node* node, bool (*predicate)(const T&), BinaryTree<T>& result) const {
        if (!node) {
            return;
        }

        if (predicate(node->data)) {
            result.insert(node->data);
        }

        whereInternal(node->left, predicate, result);
        whereInternal(node->right, predicate, result);
    }


    void preOrderTraversal(Node* node, Vector<T>& result) const {
        if (node) {
            result.append(node->data);
            preOrderTraversal(node->left, result);
            preOrderTraversal(node->right, result);
        }
    }

    void inOrderTraversal(Node* node, Vector<T>& result) const {
        if (node) {
            inOrderTraversal(node->left, result);
            result.append(node->data);
            inOrderTraversal(node->right, result);
        }
    }

    void postOrderTraversal(Node* node, Vector<T>& result) const {
        if (node) {
            postOrderTraversal(node->left, result);
            postOrderTraversal(node->right, result);
            result.append(node->data);
        }
    }

    Node* findMinNode(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, const T& data) {
        if (!node) {
            return nullptr;
        }

        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else { 
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMinNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node; // Было: return Node;
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};
