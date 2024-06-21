#pragma once

#include <iostream>
#include "BinaryTree.h"

template <typename T>
class ConsoleUI {
public:
    void run();

private:
    BinaryTree<T> inputTree(const std::string& prompt = "Enter tree elements (separated by spaces): ") const;

    void displayTree(const BinaryTree<T>& tree, const std::string& message = "Tree:") const;

    void displayTraversalOptions(const BinaryTree<T>& tree) const;

    int getChoice(int minChoice, int maxChoice) const;

    T getValue(const std::string& message) const;

    void clearCin() const;
};

template class ConsoleUI<int>;
template class ConsoleUI<double>;