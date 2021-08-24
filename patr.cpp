#include "patr.hpp"
#include <iostream>

struct Patricia::Node{
    std::string key;
    int value;
    size_t index;
    Node *right, *left;

    Node(const std::string& key, const int& value, const int& index)
        : key(key), value(value), index(index), left(nullptr), right(nullptr) {
            // Debug
        //std::cout << "[" << this << "] Created with key \"" + key + "\" and value \"" << value << "\"\n";
    }

    ~Node(){
            // Debug
        //std::cout << "[" << this << "] Deleted with key \"" + key + "\" and value \"" << value << "\"\n";
    }
};

void Patricia::Print(Node* node, bool isLeft, int offset, int prevIndex) const{
    if(node->index <= prevIndex)
        return;

    std::cout << '\t';
    for(int i = 0; i < offset; ++i)
        std::cout << ' ';
    std::cout << (isLeft ? "- " : "+ ") << node->index << ' ' << node->key
        << ' ' << node->value << '\n';

    Print(node->left, true, offset + 1, node->index);
    Print(node->right, false, offset + 1, node->index);
}

void Patricia::Print() const{
    if(!root)
        return;

    std::cout << '\t' << root->index << ' ' << root->key
        << ' ' << root->value << '\n';
    Print(root->left, true, 1, root->index);
}

int& Patricia::At(const std::string& findKey) const{
    if(!root)
        throw std::runtime_error("\t\"" + findKey + "\" hadn't found!\n");

    Node* get = Search(findKey);

    if(get->key == findKey)
        return get->value;

    throw std::runtime_error("\t\"" + findKey + "\" hadn't found!\n");
}

void Patricia::Add(const std::string& key, int value){
    if(!root){
        root = new Node(key, value, 0);
        root->left = root;
        return;
    }

    Node *foundNode = Search(key);
    if(foundNode->key == key)
        throw std::runtime_error("\t\"" + key + "\" already exist!\n");
    
    bool run = true;
    size_t charIndex = 0;
    while(run){
        char foundedKey = (foundNode->key.size() > charIndex ? foundNode->key[charIndex] : '\0');
        char inputKey   = (key.size() > charIndex ? key[charIndex] : '\0');
        for(size_t i = 0; i < BIT_COUNT; ++i){
            bool foundedKeyBit = foundedKey >> (BIT_COUNT - 1 - i) & 1;
            bool inputKeyBit = inputKey >> (BIT_COUNT - 1 - i) & 1;
            if(foundedKeyBit != inputKeyBit){
                Insert(key, value, charIndex * BIT_COUNT + i + 1);
                run = false;
                break;
            }
        }
        ++charIndex;
    }
}

void Patricia::Erase(const std::string& key){
    if(!root)
        throw std::runtime_error("\t\"" + key + "\" hadn't found!\n");

    // Get delete node, owner delete node and parent owner
    std::tuple<Node*, Node*, Node*> delOwnerParentTuple = SearchE(key);
    Node *deleteNode = std::get<0>(delOwnerParentTuple);
    Node *ownerDeleteNode = std::get<1>(delOwnerParentTuple);
    Node *parentOwnerDeleteNode = std::get<2>(delOwnerParentTuple);

    if(deleteNode->key != key)
        throw std::runtime_error("\t\"" + key + "\" hadn't found!\n");
    
    // If delete node is root and it's one
    if(deleteNode == root && root->left == root){
        delete root;
        root = nullptr;
        return;
    }

    // If delete node is leaf
    if(ownerDeleteNode == deleteNode){
        //std::cout << "[Erase] DeleteNode is leaf\n";
        if(parentOwnerDeleteNode->right == deleteNode)
            if(deleteNode->right == deleteNode)
                parentOwnerDeleteNode->right = deleteNode->left;
            else
                parentOwnerDeleteNode->right = deleteNode->right;
        else
            if(deleteNode->right == deleteNode)
                parentOwnerDeleteNode->left = deleteNode->left;
            else
                parentOwnerDeleteNode->left = deleteNode->right;
        delete deleteNode;
        return;
    }

    // Get owner owner delete node
    std::tuple<Node*, Node*, Node*> ownerOwnerTuple = SearchE(ownerDeleteNode->key);
    Node *ownerOwnerDelNode = std::get<1>(ownerOwnerTuple);

    // Change item from owner delete node to delete node
    deleteNode->key = ownerDeleteNode->key;
    deleteNode->value = ownerDeleteNode->value;

    // If owner delete node is leaf
    if(ownerOwnerDelNode == ownerDeleteNode){
        if(parentOwnerDeleteNode->right == ownerDeleteNode)
            parentOwnerDeleteNode->right = deleteNode;
        else
            parentOwnerDeleteNode->left = deleteNode;
    }
    else{
        // Tie parent owner delete node with child
        if(parentOwnerDeleteNode->right == ownerDeleteNode)
            if(ownerDeleteNode->right == deleteNode)
                parentOwnerDeleteNode->right = ownerDeleteNode->left;
            else
                parentOwnerDeleteNode->right = ownerDeleteNode->right;
        else
            if(ownerDeleteNode->right == deleteNode)
                parentOwnerDeleteNode->left = ownerDeleteNode->left;
            else
                parentOwnerDeleteNode->left = ownerDeleteNode->right;

        if(ownerOwnerDelNode->right == ownerDeleteNode)
            ownerOwnerDelNode->right = deleteNode;
        else
            ownerOwnerDelNode->left = deleteNode;
    }
    delete ownerDeleteNode;
}

void Patricia::Clear(){
    if(!root)
        return;
    if(root != root->left)
        ClearNode(root->left);
    delete root;
    root = nullptr;
}

// TODO make it faster
std::tuple<Patricia::Node*, Patricia::Node*, Patricia::Node*> Patricia::SearchE(const std::string& findKey) const{
    Node *currentNode = root->left, *prevNode = root, *prevPrevNode = root;
    while(currentNode->index > prevNode->index){
        int charIndex = (currentNode->index - 1) / BIT_COUNT;

        // FindKey is less than need char
        if(charIndex >= findKey.size()){
            prevPrevNode = prevNode;
            prevNode = currentNode;
            // Only '0'
            currentNode = currentNode->left;
            continue;
        }

        char currentChar = findKey[charIndex]; // If findkey.size less than currentNode->index
        int offset = (BIT_COUNT - 1 - ((currentNode->index - 1) % BIT_COUNT));
        bool currentBit = (currentChar >> offset) & 1;

        // Remember prevNode & prevPrevNove
        prevPrevNode = prevNode;
        prevNode = currentNode;
        // If '1' go right, '0' go left
        currentBit  ? currentNode = currentNode->right
                    : currentNode = currentNode->left;
    }

    return std::make_tuple(currentNode, prevNode, prevPrevNode);
}

Patricia::Node* Patricia::Search(const std::string& findKey) const{
    Node *currentNode = root->left, *prevNode = root;

    while(currentNode->index > prevNode->index){
        int charIndex = (currentNode->index - 1) / BIT_COUNT;

        // FindKey is less than need char
        if(charIndex >= findKey.size()){
            prevNode = currentNode;
            // Only '0'
            currentNode = currentNode->left;
            continue;
        }

        char currentChar = findKey[charIndex]; // If findkey.size less than currentNode->index
        int offset = (BIT_COUNT - 1 - ((currentNode->index - 1) % BIT_COUNT));
        bool currentBit = (currentChar >> offset) & 1;

        // Remember prevNode
        prevNode = currentNode;
        // If '1' go right, '0' go left
        currentBit  ? currentNode = currentNode->right
                    : currentNode = currentNode->left;
    }
    return currentNode;
}

void Patricia::Insert(const std::string& key, const int& value, const int& index){
    Node *currentNode = root->left, *prevNode = root;

    while(currentNode->index > prevNode->index){
        if(currentNode->index > index)
            break;

        int charIndex = (currentNode->index - 1) / BIT_COUNT;
        // FindKey is less than need char
        if(charIndex >= key.size()){
            prevNode = currentNode;
            // Only '0'
            currentNode = currentNode->left;
            continue;
        }
        char currentChar = key[charIndex]; // If findkey.size less than currentNode->index
        int offset = (BIT_COUNT - 1 - ((currentNode->index - 1) % BIT_COUNT));
        bool currentBit = (currentChar >> offset) & 1;

        // Remember prevNode
        prevNode = currentNode;
        // If '1' go right, '0' go left
        currentBit  ? currentNode = currentNode->right
                    : currentNode = currentNode->left;
    }

    char getCharFromKey = key[(index - 1) / BIT_COUNT];
    bool getBit = getCharFromKey >> (BIT_COUNT - 1 - (index - 1) % BIT_COUNT) & 1;
    Node *newNode = new Node(key, value, index);

    if(prevNode->left == currentNode)
        prevNode->left = newNode;
    else
        prevNode->right = newNode;

    getBit  ? (newNode->right = newNode, newNode->left = currentNode)
            : (newNode->left = newNode, newNode->right = currentNode);
}

void Patricia::ClearNode(Node *node){
    if(node->left->index > node->index)
        ClearNode(node->left);
    if(node->right->index > node->index)
        ClearNode(node->right);

    delete node;
}

void Patricia::Test(){
    std::tuple<Node*, Node*, Node*> test = SearchE("f");
    std::cout << std::get<0>(test)->key << ' ' << std::get<1>(test)->key << ' ' << std::get<2>(test)->key << '\n';
    std::cout << std::get<0>(test) << ' ' << std::get<1>(test) << ' ' << std::get<2>(test) << '\n';
}