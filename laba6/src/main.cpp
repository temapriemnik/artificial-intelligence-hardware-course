#include "../include/hash_table.h"
#include <iostream>

int main() {
    HashTable ht;
    
    // Тестирование базовых операций
    ht.insert("name", "Alice");
    ht.insert("age", "30");
    
    std::cout << "name: " << *ht.find("name") << std::endl;
    std::cout << "age: " << *ht.find("age") << std::endl;
    
    return 0;
}