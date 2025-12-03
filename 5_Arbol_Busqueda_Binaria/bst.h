#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

template <class T>
class BST;

template <class T>
class TreeNode {
private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

public:
    TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}
    TreeNode(T data, TreeNode<T> *left, TreeNode<T> *right) : data(data), left(left), right(right) {}

    void add(T data) {
        if (data < this->data) {
            if (left == nullptr) {
                left = new TreeNode<T>(data);
            } else {
                left->add(data);
            }
        } else if (data > this->data) {
            if (right == nullptr) {
                right = new TreeNode<T>(data);
            } else {
                right->add(data);
            }
        }
    }

    string visit() {
        stringstream ss;
        
        ss << "[";
        preorder(ss);
        ss << "]";
        
        ss << "\n[";
        inorder(ss);
        ss << "]";
        
        ss << "\n[";
        postorder(ss);
        ss << "]";
        
        ss << "\n[";
        levelByLevel(ss);
        ss << "]";
        
        return ss.str();
    }

    void preorder(stringstream &ss) {
        ss << data;
        if (left != nullptr) {
            ss << " ";
            left->preorder(ss);
        }
        if (right != nullptr) {
            ss << " ";
            right->preorder(ss);
        }
    }

    void inorder(stringstream &ss) {
        if (left != nullptr) {
            left->inorder(ss);
            ss << " ";
        }
        ss << data;
        if (right != nullptr) {
            ss << " ";
            right->inorder(ss);
        }
    }

    void postorder(stringstream &ss) {
        if (left != nullptr) {
            left->postorder(ss);
            ss << " ";
        }
        if (right != nullptr) {
            right->postorder(ss);
            ss << " ";
        }
        ss << data;
    }

    void levelByLevel(stringstream &ss) {
        queue<TreeNode<T>*> q;
        q.push(this);
        
        bool first = true;
        while (!q.empty()) {
            TreeNode<T> *current = q.front();
            q.pop();
            
            if (!first) {
                ss << " ";
            }
            ss << current->data;
            first = false;
            
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    int height() {
        int leftHeight = 0, rightHeight = 0;
        
        if (left != nullptr) {
            leftHeight = left->height();
        }
        if (right != nullptr) {
            rightHeight = right->height();
        }
        
        return 1 + max(leftHeight, rightHeight);
    }

    string ancestors(T value) {
        vector<T> ancestorsList;
        bool found = findAncestors(value, ancestorsList);
        
        stringstream ss;
        ss << "[";
        if (found) {
            for (size_t i = 0; i < ancestorsList.size(); i++) {
                if (i > 0) {
                    ss << " ";
                }
                ss << ancestorsList[i];
            }
        }
        ss << "]";
        return ss.str();
    }

    bool findAncestors(T value, vector<T> &ancestorsList) {
        if (data == value) {
            return true;
        }
        
        ancestorsList.push_back(data);
        
        bool found = false;
        if (value < data && left != nullptr) {
            found = left->findAncestors(value, ancestorsList);
        } else if (value > data && right != nullptr) {
            found = right->findAncestors(value, ancestorsList);
        }
        
        if (!found) {
            ancestorsList.pop_back();
        }
        
        return found;
    }

    int whatlevelamI(T value) {
        return findLevel(value, 1);
    }

    int findLevel(T value, int currentLevel) {
        if (data == value) {
            return currentLevel;
        }
        
        if (value < data && left != nullptr) {
            return left->findLevel(value, currentLevel + 1);
        } else if (value > data && right != nullptr) {
            return right->findLevel(value, currentLevel + 1);
        }
        
        return -1; 
    }

    friend class BST<T>;
};

template <class T>
class BST {
private:
    TreeNode<T> *root;

public:
    BST() : root(nullptr) {}

    void add(T data) {
        if (root == nullptr) {
            root = new TreeNode<T>(data);
        } else {
            root->add(data);
        }
    }

    string visit() {
        if (root == nullptr) {
            return "[]\n[]\n[]\n[]";
        }
        return root->visit();
    }

    int height() {
        if (root == nullptr) {
            return 0;
        }
        return root->height();
    }

    string ancestors(T value) {
        if (root == nullptr) {
            return "[]";
        }
        return root->ancestors(value);
    }

    int whatlevelamI(T value) {
        if (root == nullptr) {
            return -1;
        }
        return root->whatlevelamI(value);
    }
};

#endif