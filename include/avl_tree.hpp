#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <utility>
#include <string>

class AVLTree {
public:
    struct Key_t {
        int key;
        bool operator<(const Key_t& rhs) const;
        bool operator==(const Key_t& rhs) const;
    };
    
    struct CmpKey {
        //正数:lhs > rhs 0:lhs == rhs 负数:lhs < rhs
        int operator() (const Key_t& lhs, const Key_t& rhs);
    };

    struct Value_t {
        int value;
    };

    struct Node {
        Node* parent;
        Node* leftChild;
        Node* rightChild;
        int height;
        std::pair<Key_t, Value_t> data;


        Node();
        Node(const Key_t& key, const Value_t& value);
        void reset();
    };

public:
    AVLTree();
    ~AVLTree();
    //查找
    bool search(const Key_t& key, Value_t *value=nullptr, Node **node=nullptr);

    //插入
    bool insert(const Key_t& key, const Value_t& value);

    //显示树的形状
    void print();

private:
    //查找
    bool searchInSubTree(Node* root, const Key_t& key, Value_t *value, Node **node);
    
    //插入
    void insertInSubTree(Node* root, const Key_t& key, const Value_t& value);

    void maintainBalance(Node *root);

    void updateHeight(Node *root);

    void rightRotate(Node *root);

    void leftRotate(Node *root);

    void destroy(Node *root);

    void print_node(Node *root);

    void output_impl(Node* n, bool left, const std::string& indent);

private:
    Node *m_root;
    CmpKey m_cmpKey;
};

#endif