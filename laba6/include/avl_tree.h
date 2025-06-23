#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "pair.h"
#include <memory>
#include <vector>  // Добавлено

class AVLTree {
public:  // Изменено с private на public для Node
    struct Node {
        Pair data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int height;

        Node(const Pair& d) : data(d), left(nullptr), right(nullptr), height(1) {}
    };

private:
    std::shared_ptr<Node> root;

    int height(std::shared_ptr<Node> node);
    int balanceFactor(std::shared_ptr<Node> node);
    void updateHeight(std::shared_ptr<Node> node);
    std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> y);
    std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> x);
    std::shared_ptr<Node> balance(std::shared_ptr<Node> node);
    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, const Pair& data);
    std::shared_ptr<Node> findMin(std::shared_ptr<Node> node);
    std::shared_ptr<Node> removeMin(std::shared_ptr<Node> node);
    std::shared_ptr<Node> remove(std::shared_ptr<Node> node, const std::string& key);
    std::shared_ptr<Node> find(std::shared_ptr<Node> node, const std::string& key) const;
    void inorder(std::shared_ptr<Node> node, std::vector<Pair>& result) const;

public:
    AVLTree() : root(nullptr) {}

    void insert(const Pair& data);
    void remove(const std::string& key);
    std::string* find(const std::string& key) const;
    std::vector<Pair> getAllPairs() const;
    bool isEmpty() const;
};

#endif // AVL_TREE_H