#include <string>
#include <tuple>

// Bits u need in one char
const int BIT_COUNT = 5;

typedef class Patricia{
private:
    struct Node;
    Node *root = nullptr;
    void Print(Node* node, bool isLeft, int offset, int prevIndex) const;
    //Node* SearchTwo(const std::string& findKey, Node *currentNode, Node &prevNode) const;
    // Node* SearchE(const std::string& findKey, Node *currentNode,
    //                         Node &retPrevNode, Node &retPrevPrevNode) const;
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

// root = new Node("a", 228, 0);
//     root->left = new Node("d", 229, 3);
//     root->left->left = new Node("b", 230, 4);
//     root->left->left->right = root->left->left;
//     root->left->left->left = root;
//     root->left->right = new Node("e", 231, 5);
//     root->left->right->left = root->left;
//     root->left->right->right = root->left->right;

// void Patricia::Erase(const std::string& key){
//     if(!root)
//         throw std::runtime_error("\t\"" + key + "\" hadn't found!\n");

//     // Get delet node
//     Node parentDeleteNode = *root;
//     //Node *deleteNode = Search(key, &root->left, &parentDeleteNode);
//     Node *deleteNode = Search(key, root->left, parentDeleteNode, *root);

//     return;
//     if(deleteNode->key != key)
//         throw std::runtime_error("\t\"" + key + "\" hadn't found!\n");
    
//     // If delete node is root and it's one
//     if(deleteNode == root && root->left == root){
//         free(root);
//         root = nullptr;
//         return;
//     }

//     std::cout << "FAGLS: " << deleteNode->key << '\n';

//     // Get owner delete node
//     Node ownDeleteNode = *root, parentOwnDeleteNode = *root;
//     //Search(key, &deleteNode, &ownDeleteNode, &parentOwnDeleteNode);
//     Search(key, deleteNode, ownDeleteNode, parentOwnDeleteNode);

//     //std::cout << "FAGLS: " << ownDeleteNode.key << '\n';

//     // If delete node is leaf
//     if(ownDeleteNode == deleteNode){
//         if(parentDeleteNode->right == deleteNode)
//             if(deleteNode->right == deleteNode)
//                 parentDeleteNode->right = deleteNode->left;
//             else
//                 parentDeleteNode->right = deleteNode->right;
//         else
//             if(deleteNode->right == deleteNode)
//                 parentDeleteNode->left = deleteNode->left;
//             else
//                 parentDeleteNode->left = deleteNode->right;
//         free(deleteNode);
//         return;
//     }

//     // Get owner owner delete node
//     Node *ownOwnDeleteNode = root;
//     Search(ownDeleteNode->key, ownDeleteNode, ownOwnDeleteNode, root);

//     std::cout << "DEBUG: " << deleteNode->key << ' ' << deleteNode->value << ' ' <<
//         ownDeleteNode->key << ' ' << ownDeleteNode->value << ' ' <<
//         ownOwnDeleteNode->key << ' ' << ownOwnDeleteNode->value << '\n';

//     // Change item from owner delete node to delete node
//     deleteNode->key = ownDeleteNode->key;
//     deleteNode->value = ownDeleteNode->value;

//     std::cout << "DEBUG: " << deleteNode->key << ' ' << deleteNode->value << ' ' <<
//         ownDeleteNode->key << ' ' << ownDeleteNode->value << ' ' <<
//         ownOwnDeleteNode->key << ' ' << ownOwnDeleteNode->value << '\n';

//     // If owner delete node is leaf
//     if(ownOwnDeleteNode == ownDeleteNode)
//         if(parentOwnDeleteNode->right == ownDeleteNode)
//             parentOwnDeleteNode->right = deleteNode;
//         else
//             parentOwnDeleteNode->left = deleteNode;
//     else
//         // Tie parent owner delete node with child
//         if(parentOwnDeleteNode->right == ownDeleteNode)
//             if(ownDeleteNode->right == deleteNode)
//                 parentOwnDeleteNode->right = ownDeleteNode->left;
//             else
//                 parentOwnDeleteNode->right = ownDeleteNode->right;
//         else
//             if(ownDeleteNode->right == deleteNode)
//                 parentOwnDeleteNode->left = ownDeleteNode->left;
//             else
//                 parentOwnDeleteNode->left = ownDeleteNode->right;

//     free(ownDeleteNode);
// }