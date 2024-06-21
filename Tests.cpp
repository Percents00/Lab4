#include "BinaryTree.h"
#include "Vector.h"

#include <iostream>
#include <cassert>
#include <sstream>

template <typename T>
bool vectorsAreEqual(const Vector<T>& vec1, const Vector<T>& vec2) {
    if (vec1.GetDimension() != vec2.GetDimension()) {
        return false;
    }
    for (int i = 0; i < vec1.GetDimension(); ++i) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }
    return true;
}


void testInsertAndSearch() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    assert(tree.search(5));
    assert(tree.search(1));
    assert(tree.search(7));
    assert(!tree.search(0));
    assert(!tree.search(10));
    std::cout << "Test 'testInsertAndSearch' passed!" << std::endl;
}

void testRemove() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    tree.remove(3);
    assert(!tree.search(3));
    assert(tree.search(4));
    std::cout << "Test 'testRemove' passed!" << std::endl;
}

void testTraversals() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    int data1[] = {5, 3, 1, 4, 7};
    int data2[] = {1, 3, 4, 5, 7};
    int data3[] = {1, 4, 3, 7, 5};

    Vector<int> expectedPreOrder(data1, 5);
    Vector<int> expectedInOrder(data2, 5);
    Vector<int> expectedPostOrder(data3, 5);

    assert(vectorsAreEqual(tree.preOrderTraversal(), expectedPreOrder));
    assert(vectorsAreEqual(tree.inOrderTraversal(), expectedInOrder));
    assert(vectorsAreEqual(tree.postOrderTraversal(), expectedPostOrder));
    std::cout << "Test 'testTraversals' passed!" << std::endl;
}

void testReduce() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    int sum = tree.reduce<int>([](const int& acc, const int& val) { return acc + val; }, 0);
    assert(sum == 20);
    std::cout << "Test 'testReduce' passed!" << std::endl;
}

void testWhere() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    BinaryTree<int> evenTree = tree.where([](const int& val) { return val % 2 == 0; });
    assert(evenTree.search(4));
    assert(!evenTree.search(5));
    std::cout << "Test 'testWhere' passed!" << std::endl;
}

void startTests() {
    testInsertAndSearch();
    testRemove();
    testTraversals();
    testReduce();
    testWhere();
}