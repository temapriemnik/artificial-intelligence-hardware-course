#include "../include/hash_table.h"
#include <gtest/gtest.h>

TEST(HashTableTest, InsertAndFind) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    
    auto* value1 = ht.find("key1");
    ASSERT_NE(value1, nullptr);
    EXPECT_EQ(*value1, "value1");
    
    auto* value2 = ht.find("key2");
    ASSERT_NE(value2, nullptr);
    EXPECT_EQ(*value2, "value2");
    
    EXPECT_EQ(ht.find("nonexistent"), nullptr);
}

TEST(HashTableTest, Remove) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    
    EXPECT_TRUE(ht.remove("key1"));
    EXPECT_FALSE(ht.remove("key1")); // Already removed
    
    EXPECT_EQ(ht.find("key1"), nullptr);
    EXPECT_NE(ht.find("key2"), nullptr);
}

TEST(HashTableTest, CollisionHandling) {
    HashTable ht(1); // Force collisions with capacity 1
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    
    EXPECT_EQ(ht.getCapacity(), 1);
    EXPECT_EQ(ht.getSize(), 2);
    
    auto* value1 = ht.find("key1");
    ASSERT_NE(value1, nullptr);
    EXPECT_EQ(*value1, "value1");
    
    auto* value2 = ht.find("key2");
    ASSERT_NE(value2, nullptr);
    EXPECT_EQ(*value2, "value2");
}

TEST(HashTableTest, GetAllItems) {
    HashTable ht;
    ht.insert("b", "value2");
    ht.insert("a", "value1");
    ht.insert("c", "value3");
    
    auto items = ht.getAllItems();
    ASSERT_EQ(items.size(), 3);
    
    // Items should be unordered but contain all inserted pairs
    std::vector<std::string> keys;
    for (const auto& item : items) {
        keys.push_back(item.first);
    }
    
    EXPECT_NE(std::find(keys.begin(), keys.end(), "a"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "b"), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), "c"), keys.end());
}