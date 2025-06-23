#include "../include/avl_tree.h"
#include <algorithm>
#include <vector>

int AVLTree::height(std::shared_ptr<Node> node) {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(std::shared_ptr<Node> node) {
    return height(node->right) - height(node->left);
}

void AVLTree::updateHeight(std::shared_ptr<Node> node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

std::shared_ptr<AVLTree::Node> AVLTree::rotateRight(std::shared_ptr<Node> y) {
    auto x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}

std::shared_ptr<AVLTree::Node> AVLTree::rotateLeft(std::shared_ptr<Node> x) {
    auto y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}

std::shared_ptr<AVLTree::Node> AVLTree::balance(std::shared_ptr<Node> node) {
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

std::shared_ptr<AVLTree::Node> AVLTree::insert(std::shared_ptr<Node> node, const Pair& data) {
    if (!node) return std::make_shared<Node>(data);
    
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        node->data.value = data.value; // Update value if key exists
    
    return balance(node);
}

std::shared_ptr<AVLTree::Node> AVLTree::findMin(std::shared_ptr<Node> node) {
    return node->left ? findMin(node->left) : node;
}

std::shared_ptr<AVLTree::Node> AVLTree::removeMin(std::shared_ptr<Node> node) {
    if (!node->left) return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

std::shared_ptr<AVLTree::Node> AVLTree::remove(std::shared_ptr<Node> node, const std::string& key) {
    if (!node) return nullptr;
    
    if (key < node->data.key)
        node->left = remove(node->left, key);
    else if (key > node->data.key)
        node->right = remove(node->right, key);
    else {
        auto left = node->left;
        auto right = node->right;
        if (!right) return left;
        auto min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

std::shared_ptr<AVLTree::Node> AVLTree::find(std::shared_ptr<Node> node, const std::string& key) const {
    if (!node) return nullptr;
    
    if (key < node->data.key)
        return find(node->left, key);
    else if (key > node->data.key)
        return find(node->right, key);
    else
        return node;
}

void AVLTree::inorder(std::shared_ptr<Node> node, std::vector<Pair>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->data);
    inorder(node->right, result);
}

void AVLTree::insert(const Pair& data) {
    root = insert(root, data);
}

void AVLTree::remove(const std::string& key) {
    root = remove(root, key);
}

std::string* AVLTree::find(const std::string& key) const {
    auto node = find(root, key);
    return node ? &node->data.value : nullptr;
}

std::vector<Pair> AVLTree::getAllPairs() const {
    std::vector<Pair> result;
    inorder(root, result);
    return result;
}

bool AVLTree::isEmpty() const {
    return root == nullptr;
}