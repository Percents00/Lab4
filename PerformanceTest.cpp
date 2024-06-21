#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include "BinaryTree.h"
#include <random>

class RandomGenerator {
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
public:
    RandomGenerator(int min, int max): rd(), mt(rd()), dist(min, max) {}

    int get() { return dist(mt); }
};


template <typename T>
double testBinaryTreeInsertion(int size) {
    RandomGenerator rng(1, 1000000);
    BinaryTree<T> tree;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        tree.insert(rng.get());
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

template <typename T>
double testBinaryTreeSearch(int size, int searchCount = 1000) {
    RandomGenerator rng(1, 1000000);
    BinaryTree<T> tree;

    for (int i = 0; i < size; ++i) {
        tree.insert(rng.get());
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < searchCount; ++i) {
        tree.search(rng.get());
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count() / searchCount;
}

int main() {
    std::ofstream outfile("results.txt");
    std::vector<int> sizes = {10000, 50000, 100000, 500000, 1000000, 5000000, 10000000 };

    outfile << "Size,InsertionTime,SearchTime\n";
    for (int size : sizes) {
        double insertionTime = testBinaryTreeInsertion<int>(size);
        double searchTime = testBinaryTreeSearch<int>(size);
        outfile << size << "," << insertionTime << "," << searchTime << "\n";
        std::cout << "Size: " << size << ", Insertion: " << insertionTime << "s, Search: " << searchTime << "s" << std::endl;
    }
    outfile.close();
    return 0;
}