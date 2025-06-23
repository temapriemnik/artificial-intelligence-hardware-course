#include "../include/hash_table.h"
void HashTable::insert(const std::string& key, const std::string& value) {
    size_t index = hash(key);
    Pair pair(key, value);
    
    // Check if key already exists
    if (table[index].find(key)) {
        table[index].remove(key);
        table[index].insert(pair);
    } else {
        table[index].insert(pair);
        size++;
    }
}

bool HashTable::remove(const std::string& key) {
    size_t index = hash(key);
    if (table[index].find(key)) {
        table[index].remove(key);
        size--;
        return true;
    }
    return false;
}

std::string* HashTable::find(const std::string& key) const {
    size_t index = hash(key);
    return table[index].find(key);
}

std::vector<std::pair<std::string, std::string>> HashTable::getAllItems() const {
    std::vector<std::pair<std::string, std::string>> result;
    for (const auto& tree : table) {
        auto pairs = tree.getAllPairs();
        for (const auto& pair : pairs) {
            result.emplace_back(pair.key, pair.value);
        }
    }
    return result;
}