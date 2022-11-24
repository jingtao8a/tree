#include "../include/binary_search_tree.hpp"
#include <queue>
#include <iostream>

bool BinarySearchTree::Key_t::operator<(const Key_t& rhs) const {
    if (key < rhs.key) {
        return true;
    }
    return false;
}

bool BinarySearchTree::Key_t::operator==(const Key_t& rhs) const {
    if (key == rhs.key) {
        return true;
    }
    return false;
}

//正数:lhs > rhs 0:lhs == rhs 负数:lhs < rhs
int BinarySearchTree::CmpKey::operator()(const Key_t& lhs, const Key_t& rhs) {
    if (lhs < rhs) {
        return -1;
    }
    if (lhs == rhs) {
        return 0;
    }
    return 1;
}


BinarySearchTree::Node::Node() {
    reset();
}

BinarySearchTree::Node::Node(const Key_t& key, const Value_t& value) {
    reset();
    data.first = key;
    data.second = value;
}

void BinarySearchTree::Node::reset() {
    parent = leftChild = rightChild = nullptr;
}

BinarySearchTree::BinarySearchTree():m_root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroy(m_root);
}

//查找
bool BinarySearchTree::search(const Key_t& key, Value_t *value, Node **node) {
    if (m_root == nullptr) {
        return false;
    }
    return searchInSubTree(m_root, key, value, node);
}

bool BinarySearchTree::searchInSubTree(Node *root, const Key_t& key, Value_t *value, Node **node) {
    int cmp = m_cmpKey(root->data.first, key);
    if (cmp == 0) {
        if (value) {
            *value = root->data.second;
        }
        if (node) {
            *node = root;
        }
        return true;
    }
    if (cmp < 0 && root->rightChild) {
        return searchInSubTree(root->rightChild, key, value, node);
    } else if (cmp > 0 && root->leftChild) {
        return searchInSubTree(root->leftChild, key, value, node);
    }
    return false;
}

//插入
bool BinarySearchTree::insert(const Key_t& key, const Value_t& value) {
    //已有该Node无需插入 
    if (search(key) == true) {
        return false;
    }

    if (m_root == nullptr) {
        m_root = new Node(key, value);;
        return true;
    }
    return insertInSubTree(m_root, key, value);
}

bool BinarySearchTree::insertInSubTree(Node* root, const Key_t& key, const Value_t& value) {
    int cmp = m_cmpKey(root->data.first, key);
    if (cmp > 0) {
        if (root->leftChild == nullptr) {
            root->leftChild = new Node(key, value);
            root->leftChild->parent = root;
            return true;
        }
        return insertInSubTree(root->leftChild, key, value);
    } else { 
        if (root->rightChild == nullptr) {
            root->rightChild = new Node(key, value);
            root->rightChild->parent = root;
            return true;
        }
        return insertInSubTree(root->rightChild, key, value);
    }
}

//删除
bool BinarySearchTree::remove(const Key_t& key) {
    Node* node = nullptr;
    if (search(key, nullptr, &node) == false) {
        return false;
    }
    return removeInSubTree(node);
}

bool BinarySearchTree::removeInSubTree(Node* root) {
    if (root->leftChild == nullptr && root->rightChild == nullptr) {//删除的是叶子节点
        Node *parent = root->parent;
        if (!parent) {//要删除的节点是根节点
            delete m_root;
            m_root = nullptr;
            return true;
        }
        if (parent->leftChild == root) {
            parent->leftChild = nullptr;
        } else {
            parent->rightChild = nullptr;
        }
        delete root;
        return true;
    }

    if (root->leftChild && root->rightChild) {//有两个孩子
        Node *nextNode = root->leftChild;
        while (nextNode->rightChild) {
            nextNode = nextNode->rightChild;
        }
        auto tmp = nextNode->data;
        nextNode->data = root->data;
        root->data = tmp;
        return removeInSubTree(nextNode);
    }

    Node *parent = root->parent;

    if (!parent) {//要删除的节点是根节点
        if (m_root->leftChild) {//只有一个左孩子
            m_root = m_root->leftChild;
            m_root->parent = nullptr;
        } else {//只有一个右孩子
            m_root = m_root->rightChild;
            m_root->parent = nullptr;
        }
        delete root;
        return true;
    }

    if (root->leftChild) {//只有一个左孩子
        if (parent->leftChild == root) {
            parent->leftChild = root->leftChild;
        } else {
            parent->rightChild = root->leftChild;
        }
        root->leftChild->parent = parent;
    } else {//只有一个右孩子
        if (parent->leftChild == root) {
            parent->leftChild = root->rightChild;
        } else {
            parent->rightChild = root->rightChild;
        }
        root->rightChild->parent = parent;
    }

    delete root;
    return true;
}

//修改
bool BinarySearchTree::update(const Key_t& key, const Value_t& value) {
    Node *node = nullptr;
    if (search(key, nullptr, &node)) {
        node->data.second = value;
    }
    return false;
}

//  ************* 输出图形二叉树 *************
void BinarySearchTree::output_impl(Node* n, bool left, std::string const& indent)
{
	if (n->rightChild) {
		output_impl(n->rightChild, false, indent + (left ? "|     " : "      "));
	}
	std::cout << indent;
	std::cout << (left ? '\\' : '/');
	std::cout << "-----";
	std::cout << "(" << n->data.first.key  << ")"<< std::endl;
	if (n->leftChild) {
		output_impl(n->leftChild, true, indent + (left ? "      " : "|     "));
	}
}


void BinarySearchTree::print_node(Node *root) {
    if (root->rightChild) {
		output_impl(root->rightChild, false, "");
	}
	std::cout << "(" << root->data.first.key << ")" << std::endl;
	if (root->leftChild) {
		output_impl(root->leftChild, true, "");
	}
}

//显示树的形状
void BinarySearchTree::print() {
    if (m_root) {//空树直接返回
        print_node(m_root);
    }
    printf("-------------------------------------------\n");
}

//销毁二叉搜索树
void BinarySearchTree::destroy(Node *root) {
    if (!root) {
        return;
    }
    destroy(root->rightChild);
    destroy(root->leftChild);
    delete root;
}