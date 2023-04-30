#include <queue>
#include <map>
#include "BinaryTree.hpp"

template <class T>
int BinaryTree<T>::getMaxWidth(TreeNode<T>* root){
    std::queue<std::pair<TreeNode<T>, int>> Q;
    Q.push({*root, 0});
    int leftIndex, rightIndex, width = 0;
    while (!Q.empty()) {
        int sz = Q.size();
        leftIndex = Q.front().second;
        for (int i = 0; i < sz; ++i) {
            TreeNode<T> node = Q.front().first;
            int index = rightIndex = Q.front().second;
            Q.pop();
            if (node.left) {
                Q.push({*(node.left), 2 * index + 1});
            }
            if (node.right) {
                Q.push({*(node.right), 2 * index + 2});
            }
        }
        width = std::max(width, rightIndex - leftIndex + 1);
    }
    return width;
};

template <class T>
std::tuple<int, int, int> BinaryTree<T>::printInfo(TreeNode<T>* root) {
    std::queue<TreeNode<T>> Q;
    Q.push(*root);
    int n = 0 , m = 0, w = 0;
    ++m;
    while (!Q.empty()) {
        int sz = Q.size();
        for (int i = 0; i < sz; ++i) {
            TreeNode<T> node = Q.front();
            int len = BinaryTree<T>::getString(node.val).size();
            w = std::max(w, len);
            Q.pop();
            if (node.left) {
                Q.push(*(node.left));
            }
            if (node.right) {
                Q.push(*(node.right));
            }
        }
        m *= 2;
        ++n;
    }
    --m;
    return {n, m, w};
};

template <class T>
std::string BinaryTree<T>::toString(TreeNode<T>* root, std::string comma /*= ""*/, bool arrowed /*= true*/){
    auto info = BinaryTree::printInfo(root);
    int n = std::get<0>(info);
    int m = std::get<1>(info);
    int w = std::get<2>(info);
    std::queue<std::pair<TreeNode<T>, int>> Q;
    int r = 0;
    int c = (int)((m - 1) / 2);
    int q = (int)((m + 1) / 4);
    std::string str = "";
    std::string horizontalArrow = BinaryTree::justifyString("_", w);
    std::string verticalArrow = BinaryTree::justifyString("|", w);
    std::string emptyStr = BinaryTree::justifyString(" ", w);
    std::string emptyStrComma = emptyStr + comma;
    std::string horizontalArrowComma = horizontalArrow + comma;
    std::string verticalArrowComma = verticalArrow + comma;
    Q.push({*root, c});
    while (!Q.empty()) {
        std::string str2 = "";
        int sz = Q.size();
        if (r > 0) {
            str += "\n";
        }
        else {
            str += "";
        }
        if (arrowed) {
            str2 += "\n";
        }
        int k = 0;
        bool hadRightNode = false;
        for (int i = 0; i < sz; ++i) {
            TreeNode<T> node = Q.front().first;
            c = Q.front().second;
            Q.pop();

            if (node.left) {
                Q.push({*(node.left), c - q});
                for (int j = k; j < c; ++j) {
                    if (!arrowed || j < c - q + 1) {
                        if (arrowed && hadRightNode && j < k - 1 + q){
                            str += horizontalArrowComma;
                        }
                        else {
                            str += emptyStrComma;
                        }
                    }
                    else {
                        str += horizontalArrowComma;
                    }
                    if (arrowed) {
                        if (j == c - q || (hadRightNode && j == k - 1 + q)){
                            str2 += verticalArrowComma;
                        }
                        else {
                            str2 += emptyStrComma;
                        }
                    }
                }
            }
            else {
                for (int j = k; j < c; ++j) {
                    if (arrowed && hadRightNode && j < k - 1 + q){
                        str += horizontalArrowComma;
                    }
                    else {
                        str += emptyStrComma;
                    }
                    if (arrowed) {
                        if (hadRightNode && j == k - 1 + q){
                            str2 += verticalArrowComma;
                        }
                        else {
                            str2 += emptyStrComma;
                        }
                    }
                }
            }
            if (node.right) {
                Q.push({*(node.right), c + q});
                hadRightNode = true;
            }
            else {
                hadRightNode = false;
            }
            str += BinaryTree::justifyString(BinaryTree<T>::getString(node.val), w);
            if (arrowed) {
                str2 += emptyStr;
            }
            k = c + 1;
            if (c < m - 1) {
                str += comma;
                if (arrowed) {
                    str2 += comma;
                }
            }
        }
        for (int j = k; j < m - 1; ++j) {
            if (arrowed && hadRightNode && j < k - 1 + q){
                str += horizontalArrowComma;
            }
            else {
                str += emptyStrComma;
            }
            if (arrowed) {
                if (hadRightNode && j == k - 1 + q){
                    str2 += verticalArrowComma;
                }
                else {
                    str2 += emptyStrComma;
                }
            }
        }
        if (c < m - 1) {
            str += emptyStr; 
            if (arrowed) {
                str2 += emptyStr;
            }
        }
        ++r;
        q /= 2;
        if (r < n) {
            str += str2;
        }
    }
    return str;
}

template <class T>
std::string BinaryTree<T>::getString(T val) {
    std::stringstream ss;
    ss << val;
    return ss.str();
}
 
template <class T>
std::string BinaryTree<T>::justifyString(std::string str, int c, std::string appendix /*= " "*/) {
    int n = str.size();
    if (n > c) {
        return str.substr(0, c);
    }
    else if (n < c) {
        while (c - n > 2) {
            str = appendix + str + appendix;
            n += 2;
        }
        if (n < c){
            str = str + appendix;
        }
    }
    return str;
}

template <class T>
TreeNode<T>* BinaryTree<T>::fromVector(std::vector<T>& vec, T defaultT, int index /*= 0*/, int* missingIndices /*= nullptr*/, int* searchBegin /*= nullptr*/) {
    TreeNode<T>* node = nullptr;
    int n = vec.size();
    if (n == 0 || index >= n || (vec[index] == defaultT)) {
        return node;
    }
    node = new TreeNode<T>(vec[index]);
    int missingIndices0 = 0;
    int searchBegin0 = 0;
    if (!missingIndices) {
        missingIndices = &missingIndices0;
    }
    if (!searchBegin) {
        searchBegin = &searchBegin0;
    }
    for (int i = *searchBegin; i < index; ++i) {
        if (vec[i] == defaultT) {
            ++*missingIndices;
        }
    }
    int leftIndex = (index - *missingIndices) * 2 + 1;
    if (leftIndex < n) {
        *searchBegin = index;
        int missingIndices1 = *missingIndices;
        node->left = fromVector(vec, defaultT, leftIndex, missingIndices, searchBegin);
        int rightIndex = leftIndex + 1;
        if (rightIndex < n) {
            *searchBegin = index;
            *missingIndices = missingIndices1;
            node->right = fromVector(vec, defaultT, rightIndex, missingIndices, searchBegin);
        }
    }
    return node;
}

template <class T>
std::ostream& operator << (std::ostream& out, TreeNode<T>& node) {
    out << BinaryTree<T>::toString(&node);
    return out;
}

// Create custom split() function.  
void customSplit(std::string str, char separator, std::vector < std::string > &strings) {
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
        
        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
}