#include <iostream>
#include <vector>
#define K(root) (root == NULL ? 0 : root->val)
using namespace std;

enum{
	RED, BLACK, DB_BLACK
};

struct Node{
	int val;
	Node *left, *right;
	int color;
	Node(int v) : val(v), left(NULL), right(NULL), color(RED) {} 	
};


typedef int (*HANDLE)(Node* root);

int fun1(Node* root);
int fun2(Node* root);

HANDLE C = fun1;

int fun1(Node* root) {
	if (root == NULL) return BLACK;
	return root->color;
}

int fun2(Node* root) {
	if (root == NULL) return DB_BLACK;
	return root->color;
}

class RB{
	Node* root;
	public:
		RB() : root(NULL) {}
		void insert(int val) {
			__insert(root, val);
			root->color = BLACK;
		}
		
		void deletenode(int val) {
			__delete(root, val);
			root->color = BLACK;
		}
		
		void preorder() {
			__preorder(root);
			root->color = BLACK;
		}
	private:
		void __preorder(Node* root) {
			if (root == NULL) return;
			cout << root->val << "," << (C(root) == RED ? "red": "black") << "(" << K(root->left) << "," << K(root->right) << ")" << endl;
			__preorder(root->left);
			__preorder(root->right);
		}
		void left_rotate(Node* &root) {
			Node* tmp = root->right;
			root->right = tmp->left;
			tmp->left = root;
			root = tmp;
		}
		
		void right_rotate(Node* &root) {
			Node* tmp = root->left;
			root->left = tmp->right;
			tmp->right = root;
			root = tmp;
		}
		void insertmaintain(Node* &root) {
			if (C(root->left) == RED && C(root->left->left) == RED) {
				if (C(root->right) == RED) {//4
					root->right->color = BLACK;
					root->left->color = BLACK;
					root->color = RED;
				} else {//3
					right_rotate(root);
					root->right->color = RED;
					root->color = BLACK;
				}
			} else if (C(root->right) == RED && C(root->right->right) == RED) {
				if (C(root->left) == RED) {
					root->left->color = BLACK;
					root->right->color = BLACK;
					root->color = RED;
				} else {
					left_rotate(root);
					root->left->color = RED;
					root->color = BLACK;
				}
			} else if (C(root->right) == RED && C(root->right->left) == RED) {
				right_rotate(root->right);//5 or 6
				insertmaintain(root);
			} else if (C(root->left) == RED && C(root->left->right) == RED) {
				left_rotate(root->left);
				insertmaintain(root);
			}
		}
		
		void __insert(Node* &root, int val) {
			if (root == NULL) {
				root = new Node(val);
			} else if (root->val > val) {
				__insert(root->left, val);
				insertmaintain(root);
				
			} else {
				__insert(root->right, val);
				insertmaintain(root);
			}
		}
		
		void swap(Node* p, Node* root) {
			int tmp = p->val;
			p->val = root->val;
			root->val = tmp;
		}
		
		void __delete(Node* &root, int val) {
			if (root) {
				if (root->val == val) {
					Node* p;
					if (root->left == NULL && root->right == NULL) {
						if (root->color == BLACK) {
							C = fun2;
						}
						delete root;
						root = NULL;
					} else if (root->left != NULL && root->right != NULL) {
						p = root->left;
						while(p->right) {
							p = p->right;
						}
						swap(p, root);
						__delete(root->left, val);
						deletemaintain(root);
					} else if (root->left == NULL) {
						p = root;
						root = root->right;
						root->color = BLACK;
						delete p;
					} else {
						p = root;
						root = root->left;
						root->color = BLACK;
						delete p;
					}
				} else if (root->val < val) {
					__delete(root->right, val);
					deletemaintain(root);
					
				} else {
					__delete(root->left, val);
					deletemaintain(root);
				}
			}
		}
		void deletemaintain(Node* &root) {
			if (C(root->left) == DB_BLACK) {
				if (root->left) root->left->color = BLACK;
				if (C(root) == RED) {
					if (root->right->right == NULL && root->right->left == NULL) {
						root->color = BLACK;
						root->right->color = RED;
						C = fun1;
					} else if (C(root->right->left) == RED) {
						right_rotate(root->right);
						left_rotate(root);
						root->left->color = BLACK;
						C = fun1;
					} else {
						left_rotate(root);
						root->color = RED;
						root->left->color = root->right->color = BLACK;
						C = fun1;
					}
				} else {
					if (root->right->right == NULL && root->right->left == NULL) {
						root->color = DB_BLACK;
						root->right->color = RED;
						C = fun1;
					} else if (C(root->right->left) == RED) {
						right_rotate(root->right);
						left_rotate(root);
						root->color = BLACK;
						C = fun1;
					} else {
						left_rotate(root);
						root->right->color = BLACK;
						C = fun1;
					}
				}
				
			} else if(C(root->right) == DB_BLACK) {
				if (root->right) root->right->color = BLACK;
				if (C(root) == RED) {
					if (root->left->left == NULL && root->left->right == NULL) {
						root->color = BLACK;
						root->left->color = RED;
						C = fun1;	
					} else if (C(root->left->right) == RED) {
						left_rotate(root->left);
						right_rotate(root);
						root->right->color = BLACK;
						C = fun1;
					} else {
						right_rotate(root);
						root->color = RED;
						root->left->color = root->right->color = BLACK;
						C = fun1;
					}
				} else {
					if (root->left->left == NULL && root->left->right == NULL) {
						root->color = DB_BLACK;
						root->left->color = RED;
						C = fun1;
					} else if (C(root->left->right) == RED) {
						left_rotate(root->left);
						right_rotate(root);
						root->color = BLACK;
						C = fun1;
					} else {
						right_rotate(root);
						root->left->color = BLACK;
						C = fun1;
					}
				}
			}
		}
};

int main()
{
	RB tree;
	vector<int> num{10, 32, 2, 5, 34, 92};
	for (int i = 0; i < num.size(); ++i) tree.insert(num[i]);
	tree.deletenode(10);
	tree.preorder();
 	return 0;
}
