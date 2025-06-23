#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "avl_tree.h"
#include <vector>
#include <string>
#include <functional>

class HashTable {
private:
    std::vector<AVLTree> table;
    size_t size;
    size_t capacity;

    size_t hash(const std::string& key) const {
        return std::hash<std::string>{}(key) % capacity;
    }

public:
    HashTable(size_t initial_capacity = 16) : capacity(initial_capacity), size(0) {
        table.resize(capacity);
    }

    void insert(const std::string& key, const std::string& value);
    bool remove(const std::string& key);
    std::string* find(const std::string& key) const;
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    std::vector<std::pair<std::string, std::string>> getAllItems() const;
};

#endif // HASH_TABLE_H