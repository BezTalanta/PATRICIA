#pragma once
#include <string>
#include <tuple>

// Bits u need in one char
const int BIT_COUNT = 5;

typedef class Patricia{
private:
    struct Node;
    Node *root = nullptr;
    // Print node
    void Print(Node* node, bool isLeft, int offset, const size_t& prevIndex) const;
    // Search but return 3 nodes
    std::tuple<Node*, Node*, Node*> SearchE(const std::string& findKey) const;
    // Search return only 1 node
    Node* Search(const std::string& findKey) const;
    void Insert(const std::string& key, const int& value, const size_t& index);
    void ClearNode(Node *node);
public:
    // Printing trie
    void Print() const;
    // Get value from map
    int& At(const std::string& findKey) const;
    void Add(const std::string& key, int value);
    void Erase(const std::string& key);
    void Clear();
    ~Patricia(){
	Clear();
    }
} patr;
