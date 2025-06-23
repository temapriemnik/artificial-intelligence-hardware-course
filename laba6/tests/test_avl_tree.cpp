#include "../include/avl_tree.h"
#include <gtest/gtest.h>

TEST(AVLTreeTest, InsertAndFind) {
    AVLTree tree;
    tree.insert(Pair("key1", "value1"));
    tree.insert(Pair("key2", "value2"));
    
    auto* value1 = tree.find("key1");
    ASSERT_NE(value1, nullptr);
    EXPECT_EQ(*value1, "value1");
    
    auto* value2 = tree.find("key2");
    ASSERT_NE(value2, nullptr);
    EXPECT_EQ(*value2, "value2");
    
    EXPECT_EQ(tree.find("nonexistent"), nullptr);
}

TEST(AVLTreeTest, Remove) {
    AVLTree tree;
    tree.insert(Pair("key1", "value1"));
    tree.insert(Pair("key2", "value2"));
    
    tree.remove("key1");
    EXPECT_EQ(tree.find("key1"), nullptr);
    
    auto* value2 = tree.find("key2");
    ASSERT_NE(value2, nullptr);
    EXPECT_EQ(*value2, "value2");
}

TEST(AVLTreeTest, GetAllPairs) {
    AVLTree tree;
    tree.insert(Pair("b", "value2"));
    tree.insert(Pair("a", "value1"));
    tree.insert(Pair("c", "value3"));
    
    auto pairs = tree.getAllPairs();
    ASSERT_EQ(pairs.size(), 3);
    EXPECT_EQ(pairs[0].key, "a");
    EXPECT_EQ(pairs[1].key, "b");
    EXPECT_EQ(pairs[2].key, "c");
}

TEST(AVLTreeTest, BalanceTest) {
    AVLTree tree;
    // Insert sorted keys to test balancing
    for (char c = 'a'; c <= 'z'; ++c) {
        std::string key(1, c);
        tree.insert(Pair(key, "value"));
    }
    
    auto pairs = tree.getAllPairs();
    EXPECT_EQ(pairs.size(), 26);
    for (size_t i = 1; i < pairs.size(); ++i) {
        EXPECT_LT(pairs[i-1].key, pairs[i].key);
    }
}