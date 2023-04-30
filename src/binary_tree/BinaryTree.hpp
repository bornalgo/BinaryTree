#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <string>
#include <sstream>
#include <vector>


template <class T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T val = NULL, TreeNode* left = nullptr, TreeNode* right = nullptr): val(val), left(left), right(right) {};
};

template <class T>
class BinaryTree {
public:
    static int getMaxWidth(TreeNode<T>* root);
    static std::tuple<int, int, int> printInfo(TreeNode<T>* root);
    static std::string toString(TreeNode<T>* root, std::string comma = "", bool arrowed = true);
    static std::string getString(T val);
    static std::string justifyString(std::string str, int c, std::string appendix = " ");
    static TreeNode<T>* fromVector(std::vector<T>& vec, T defaultT, int index = 0, int* missingIndices = nullptr, int* searchBegin = nullptr);
};

template <class T>
std::ostream& operator << (std::ostream& out, TreeNode<T>& node);

void customSplit(std::string str, char separator, std::vector < std::string > &strings);

#endif

