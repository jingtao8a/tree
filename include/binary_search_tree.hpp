#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <utility>
#include <memory>

class BinarySearchTree {
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
        std::pair<Key_t, Value_t> data;


        Node();
        Node(const Key_t& key, const Value_t& value);
        void reset();
    };
public:
    BinarySearchTree();
    ~BinarySearchTree();
    //查找
    bool search(const Key_t& key, Value_t *value=nullptr, Node **node=nullptr);

    //插入
    bool insert(const Key_t& key, const Value_t& value);
    
    //删除
    bool remove(const Key_t& key);

    //修改
    bool update(const Key_t& key, const Value_t& value);
    
    //显示树的形状
    void print();

    void inorder();
private:
    void _inorder(Node *root);

    bool searchInSubTree(Node* root, const Key_t& key, Value_t *value, Node **node);

    bool insertInSubTree(Node* root, const Key_t& key, const Value_t& value);

    bool removeInSubTree(Node* root);

    void destroy(Node* root);

    void print_node(Node *root);

    void output_impl(Node* n, bool left, const std::string& indent);

private:
    Node *m_root;
    CmpKey m_cmpKey;
};

#endif