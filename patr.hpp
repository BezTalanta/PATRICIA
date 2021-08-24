#pragma once
#include <string>
#include <tuple>

// Bits u need in one char
const int BIT_COUNT = 5;

typedef class Patricia{
private:
    struct Node;
    Node *root = nullptr;
    void Print(Node* node, bool isLeft, int offset, int prevIndex) const;
    std::tuple<Node*, Node*, Node*> SearchE(const std::string& findKey) const;
    Node* Search(const std::string& findKey) const;
    void Insert(const std::string& key, const int& value, const int& index);
    void ClearNode(Node *node);
public:
    // Printing trie
    void Print() const;
    int& At(const std::string& findKey) const;
    void Add(const std::string& key, int value);
    void Erase(const std::string& key);
    void Clear();
    void Test();
} patr;