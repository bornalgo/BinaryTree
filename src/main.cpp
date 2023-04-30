#include <iostream>
#include <vector>
#include <string>
#include <BinaryTree.hpp>
#include <BinaryTree.cpp>
#include <algorithm>

#ifndef _MAX_PATH
#define _MAX_PATH   260
#endif
static char szInput[_MAX_PATH];

int main() {
    while (true) {
        std::cout << "> ";
        std::cin.getline(szInput, _MAX_PATH);
        std::vector < std::string > strings;
        customSplit(szInput, ' ', strings);
        if (strings.size() > 0) {
            std::string str = strings[0];
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
            if (str == "quit") {
                break;
            }
            TreeNode<std::string>* root = BinaryTree<std::string>::fromVector(strings, "NULL");
            std::cout << "Schematic of the binary tree:\n" << *root << std::endl;
            std::cout << "Maximum width of the binary tree: " << BinaryTree<std::string>::getMaxWidth(root) << std::endl;
        }
        else {
            break;
        }
    }
    // std::vector<int> vec{1,2,3,NULL,4};
    // TreeNode<int>* root = BinaryTree<int>::fromVector(vec, 0);
    // std::cout << "Schematic of the binary tree:\n" << *root << std::endl;
    // std::cout << "Maximum width of the binary tree: " << BinaryTree<int>::getMaxWidth(root) << std::endl;
    return 0;
}