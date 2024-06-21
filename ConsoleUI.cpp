#include "ConsoleUI.h"

#include <iostream>
#include <limits>
#include <sstream>

template<typename T>
void ConsoleUI<T>::run() {
    BinaryTree<T> tree;

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Insert into the tree\n";
        std::cout << "2. Search in the tree\n";
        std::cout << "3. Remove from the tree\n";
        std::cout << "4. Display the tree (in-order)\n";
        std::cout << "5. Tree Traversal\n";
        std::cout << "6. Reduce\n";
        std::cout << "7. Where\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        choice = getChoice(0, 7);

        switch (choice) {
            case 1: {
                int insertChoice;
                do {
                    tree = inputTree();
                    std::cout << "Elements inserted.\n";

                    std::cout << "1. Insert more elements\n";
                    std::cout << "0. Back to main menu\n";
                    std::cout << "Enter your choice: ";
                    insertChoice = getChoice(0, 1); 
                } while (insertChoice != 0);
                break;
            }
            case 2: {
                T searchValue = getValue("Enter search value: ");
                if (tree.search(searchValue)) {
                    std::cout << "Value " << searchValue << " found in the tree.\n";
                } else {
                    std::cout << "Value " << searchValue << " not found in the tree.\n";
                }
                break;
            }
            case 3: {
                T removeValue = getValue("Enter value to remove: ");
                tree.remove(removeValue);
                std::cout << "Value " << removeValue << " removed (if found).\n";
                break;
            }
            case 4: {
                displayTree(tree);
                break;
            }
            case 5: {
                displayTraversalOptions(tree);
                break;
            }
            case 6: {
                T initialValue = getValue("Enter initial value for reduce: ");
                T result = tree.template reduce<T>(
                        [](const T &acc, const T &val) {
                            return acc + val;
                        },
                        initialValue);
                std::cout << "Result of reduce: " << result << std::endl;
                break;
            }
            case 7: {
                if constexpr (std::is_integral<T>::value) {
                    BinaryTree<T> filteredTree = tree.where([](const T &val) {
                        return val % 2 == 0; 
                });
                std::cout << "Filtered tree: ";
                displayTree(filteredTree);
            } else {
                std::cout << "Filtering is only available for integer trees." << std::endl;
            }
            break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

template<typename T>
BinaryTree<T> ConsoleUI<T>::inputTree(const std::string &prompt) const {
    BinaryTree<T> tree;
    std::string input;
    T value;

    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::istringstream iss(input);
    while (iss >> value) {
        tree.insert(value);
    }
    return tree;
}

template<typename T>
void ConsoleUI<T>::displayTree(const BinaryTree<T> &tree, const std::string &message) const {
    std::cout << message << std::endl;
    Vector<T> values = tree.inOrderTraversal();
    if (values.GetDimension() == 0) {
        std::cout << "Tree is empty.\n";
    } else {
        for (int i = 0; i < values.GetDimension(); ++i) {
            std::cout << values[i] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void ConsoleUI<T>::displayTraversalOptions(const BinaryTree<T> &tree) const {
    int choice;
    do {
        std::cout << "\nTraversal options:\n";
        std::cout << "1. Pre-order traversal\n";
        std::cout << "2. In-order traversal\n";
        std::cout << "3. Post-order traversal\n";
        std::cout << "0. Back\n";
        std::cout << "Enter your choice: ";

        choice = getChoice(0, 3);

        switch (choice) {
            case 1:
                displayTree(tree, "Pre-order: ");
                break;
            case 2:
                displayTree(tree, "In-order: ");
                break;
            case 3:
                displayTree(tree, "Post-order: ");
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

template<typename T>
int ConsoleUI<T>::getChoice(int minChoice, int maxChoice) const {
    int choice;
    while (!(std::cin >> choice) || choice < minChoice || choice > maxChoice) {
        std::cout << "Invalid choice. Please enter a number between "
                  << minChoice << " and " << maxChoice << ": ";
        clearCin();
    }
    return choice;
}

template<typename T>
T ConsoleUI<T>::getValue(const std::string &message) const {
    T value;
    std::cout << message;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter a value: ";
        clearCin();
    }
    return value;
}

template<typename T>
void ConsoleUI<T>::clearCin() const {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}