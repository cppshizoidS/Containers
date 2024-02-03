#ifndef MY_BINARY_TREE_HPP
#define MY_BINARY_TREE_HPP

#include <functional>

namespace my_binary_tree {

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class MyBinaryTree {
private:
    TreeNode<T>* root;

    void insert(TreeNode<T>*& node, const T& value) {
        if (node == nullptr) {
            node = new TreeNode<T>(value);
        } else {
            if (value.surname < node->data.surname) {
                insert(node->left, value);
            } else {
                insert(node->right, value);
            }
        }
    }

    const T* find(TreeNode<T>* node, const T& value) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (value.surname < node->data.surname) {
            return find(node->left, value);
        } else if (node->data.surname < value.surname) {
            return find(node->right, value);
        } else {
            return &node->data;
        }
    }

    void inOrderTraversal(TreeNode<T>* node, const std::function<void(const T&)>& callback) const {
        if (node != nullptr) {
            inOrderTraversal(node->left, callback);
            callback(node->data);
            inOrderTraversal(node->right, callback);
        }
    }

    void reverseInOrderTraversal(TreeNode<T>* node, const std::function<void(const T&)>& callback) const {
        if (node != nullptr) {
            reverseInOrderTraversal(node->right, callback);
            callback(node->data);
            reverseInOrderTraversal(node->left, callback);
        }
    }

    void clear(TreeNode<T>*& node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

public:
    MyBinaryTree() : root(nullptr) {}

    void insert(const T& value) {
        insert(root, value);
    }

    const T* find(const std::function<bool(const T&)>& predicate) const {
        return find(root, predicate);
    }

    void inOrderTraversal(const std::function<void(const T&)>& callback) const {
        inOrderTraversal(root, callback);
    }

    void reverseInOrderTraversal(const std::function<void(const T&)>& callback) const {
        reverseInOrderTraversal(root, callback);
    }

    ~MyBinaryTree() {
        clear(root);
    }
};

} // namespace my_binary_tree

#endif // MY_BINARY_TREE_HPP
