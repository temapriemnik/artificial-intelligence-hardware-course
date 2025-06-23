#ifndef PAIR_H
#define PAIR_H

#include <string>

struct Pair {
    std::string key;
    std::string value;

    Pair(const std::string& k, const std::string& v) : key(k), value(v) {}
    
    bool operator<(const Pair& other) const {
        return key < other.key;
    }
    
    bool operator>(const Pair& other) const {
        return key > other.key;
    }
    
    bool operator==(const Pair& other) const {
        return key == other.key;
    }
};

#endif // PAIR_H