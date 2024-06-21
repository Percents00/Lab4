#pragma once

#include "Vector.h"

template <typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& data) : data(data), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
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

    template <typename Func>
    void map(Func func) {
        mapRecursive(root, func);
    }

    BinaryTree<T> subtree(Node* subRoot) const {
        if (!subRoot) {
            return BinaryTree<T>();
        }

        BinaryTree<T> newTree;
        newTree.root = copySubtree(subRoot);

        return newTree;
    }


    void insert(const T& data) {
        root = insertRecursive(root, data);
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
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* copySubtree(Node* node) const {
        if (!node) {
            return nullptr;
        }
        Node* newNode = new Node(node->data);
        newNode->left = copySubtree(node->left);
        newNode->right = copySubtree(node->right);
        newNode->height = node->height;
        return newNode;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        x->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }


    Node* insertRecursive(Node* node, const T& data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
            return node;
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
            return node;
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);
        if (balance > 1 && data > node->right->data) {
            return rotateLeft(node);
        }
        if (balance < -1 && data < node->left->data) {
            return rotateRight(node);
        }
        if (balance > 1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balance < -1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        return node; 
    }


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


    template <typename Func>
    void mapRecursive(Node* node, Func func) {
        if (node != nullptr) {
            node->data = func(node->data);
            mapRecursive(node->left, func);
            mapRecursive(node->right, func);
        }
    }


    Node* deleteNode(Node* node, const T& data) {
        if (node == nullptr) {
        return nullptr;
        }

        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else { 

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMinNode(node->right); 
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        if (node == nullptr) { 
            return node; 
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};
