#include "avl_tree.hpp"
#include <algorithm>
#include <iostream>

bool AVLTree::Key_t::operator<(const Key_t& rhs) const {
    if (key < rhs.key) {
        return true;
    }
    return false;
}

bool AVLTree::Key_t::operator==(const Key_t& rhs) const {
    if (key == rhs.key) {
        return true;
    }
    return false;
}

//正数:lhs > rhs 0:lhs == rhs 负数:lhs < rhs
int AVLTree::CmpKey::operator()(const Key_t& lhs, const Key_t& rhs) {
    if (lhs < rhs) {
        return -1;
    }
    if (lhs == rhs) {
        return 0;
    }
    return 1;
}


AVLTree::Node::Node() {
    reset();
}

AVLTree::Node::Node(const Key_t& key, const Value_t& value) {
    reset();
    data.first = key;
    data.second = value;
}

void AVLTree::Node::reset() {
    parent = leftChild = rightChild = nullptr;
    height = 1;
}

AVLTree::AVLTree():m_root(nullptr) {}

AVLTree::~AVLTree() {
    destroy(m_root);
}

//查找
bool AVLTree::search(const Key_t& key, Value_t *value, Node **node) {
    if (m_root == nullptr) {
        return false;
    }
    return searchInSubTree(m_root, key, value, node);
}

bool AVLTree::searchInSubTree(Node *root, const Key_t& key, Value_t *value, Node **node) {
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
bool AVLTree::insert(const Key_t& key, const Value_t& value) {
    //已有该Node无需插入 
    if (search(key) == true) {
        return false;
    }

    if (!m_root) {
        m_root = new Node(key, value);
        return true;
    }
    insertInSubTree(m_root, key, value);
    return true;
}

void AVLTree::insertInSubTree(Node* root, const Key_t& key, const Value_t& value) {
    int cmp = m_cmpKey(root->data.first, key);
    if (cmp > 0) {
        if (root->leftChild == nullptr) {
            root->leftChild = new Node(key, value);
            root->leftChild->parent = root;
            updateHeight(root);
            maintainBalance(root);
            return;
        }
        insertInSubTree(root->leftChild, key, value);
        updateHeight(root);
        maintainBalance(root);
    } else { 
        if (root->rightChild == nullptr) {
            root->rightChild = new Node(key, value);
            root->rightChild->parent = root;
            updateHeight(root);
            maintainBalance(root);
            return;
        }
        insertInSubTree(root->rightChild, key, value);
        updateHeight(root);
        maintainBalance(root);
    }
}

void AVLTree::updateHeight(Node *root) {    
    int left = root->leftChild ? root->leftChild->height : 0;
    int right = root->rightChild ? root->rightChild->height : 0;
    root->height = std::max(left, right) + 1;
}

void AVLTree::maintainBalance(Node *root) {
    int left = root->leftChild ? root->leftChild->height : 0;
    int right = root->rightChild ? root->rightChild->height : 0;
    if (std::abs(left - right) <= 1) {
        return;
    }
    Node *nodePtr = nullptr;
    if (left > right) {//新插入的叶子节点在左子树
        nodePtr = root->leftChild;
        int left = nodePtr->leftChild ? nodePtr->leftChild->height : 0;
        int right = nodePtr->rightChild ? nodePtr->rightChild->height : 0;
        if (left < right) {//LR
            leftRotate(nodePtr);
        }
        //LL
        rightRotate(root);
    } else {//新插入的叶子节点在右子树
        nodePtr = root->rightChild;
        int left = nodePtr->leftChild ? nodePtr->leftChild->height : 0;
        int right = nodePtr->rightChild ? nodePtr->rightChild->height : 0;
        if (left > right) {//RL
            rightRotate(nodePtr);
        }
        //RR
        leftRotate(root);
    }
}

void AVLTree::rightRotate(Node *root) {
    Node *p = root->leftChild;
    Node *parent = root->parent;
    if (parent) {//如果root有父节点
        if (parent->leftChild == root) {
            parent->leftChild = p;
        } else {
            parent->rightChild = p;
        }
    }

    p->parent = parent;
    root->parent = p;

    root->leftChild = p->rightChild;
    if (root->leftChild) {
        root->leftChild->parent = root;
    }
    p->rightChild = root;
    updateHeight(root);
    updateHeight(p);
}

void AVLTree::leftRotate(Node *root) {
    Node *p = root->rightChild;
    Node *parent = root->parent;
    if (parent) {
        if (parent->leftChild == root) {
            parent->leftChild = p;
        } else {
            parent->rightChild = p;
        }
    } else {
        m_root = p;//树根变换
    }
    p->parent = parent;
    root->parent = p;

    root->rightChild = p->leftChild;
    if (root->rightChild) {
        root->rightChild->parent = root;
    }
    p->leftChild = root;

    updateHeight(root);
    updateHeight(p);
}

//删除
bool AVLTree::remove(const Key_t& key) {
    if ((search(key)) == false) {//不存在该节点
        return false;
    }
    removeInSubTree(m_root, key);
    return true;
}

void AVLTree::removeInSubTree(Node *root, const Key_t& key) {
    int cmp = m_cmpKey(root->data.first, key);
    if (cmp != 0) {
        if (cmp > 0) {
            removeInSubTree(root->leftChild, key);
        } else {
            removeInSubTree(root->rightChild, key);
        }
        updateHeight(root);
        maintainBalance(root);
    } else {
        if (root->leftChild == nullptr && root->rightChild == nullptr) {//删除的是叶子节点
            Node *parent = root->parent;
            if (!parent) {//要删除的节点是根节点
                delete m_root;
                m_root = nullptr;
                return;
            }
            if (parent->leftChild == root) {
                parent->leftChild = nullptr;
            } else {
                parent->rightChild = nullptr;
            }
            delete root;
            return;
        }

        if (root->leftChild && root->rightChild) {//有两个孩子
            Node *nextNode = root->leftChild;
            while (nextNode->rightChild) {
                nextNode = nextNode->rightChild;
            }
            auto tmp = nextNode->data;
            nextNode->data = root->data;
            root->data = tmp;
            removeInSubTree(root->leftChild, key);
            updateHeight(root);
            maintainBalance(root);
            return;
        }
        //只有一个孩子
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
            updateHeight(m_root);
            return;
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
    }
}

//修改
bool AVLTree::update(const Key_t& key, const Value_t& value) {
    Node *node = nullptr;
    if (search(key, nullptr, &node)) {
        node->data.second = value;
    }
    return false;
}

//销毁二叉搜索树
void AVLTree::destroy(Node *root) {
    if (!root) {
        return;
    }
    destroy(root->rightChild);
    destroy(root->leftChild);
    delete root;
}


//  ************* 输出图形二叉树 *************
void AVLTree::output_impl(Node* n, bool left, std::string const& indent)
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


void AVLTree::print_node(Node *root) {
    if (root->rightChild) {
		output_impl(root->rightChild, false, "");
	}
	std::cout << "(" << root->data.first.key << ")" << std::endl;
	if (root->leftChild) {
		output_impl(root->leftChild, true, "");
	}
}

//显示树的形状
void AVLTree::print() {
    if (m_root) {//空树直接返回
        print_node(m_root);
    }
    printf("-------------------------------------------\n");
}
