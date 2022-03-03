#include <cstdio>
#define K(n) ((n) == nullptr ? 0 : (n)->value)

enum Color{
	RED = 1, BLACK = 2, DOUBLE_BLACK = 3
};

class RBNode{
	public:
		int value;
		Color color;
		RBNode *lchild, *rchild;
		RBNode(int value, Color color)
		{
			this->value = value;
			this->color = color;
			this->lchild = nullptr;
			this->rchild = nullptr;
		}
};

typedef int (*HANDLE)(RBNode *n);

int fun1(RBNode *n);
int fun2(RBNode *n);

HANDLE C = fun1;



int fun1(RBNode *n)
{
	return (n == nullptr ? BLACK : n->color);
}

int fun2(RBNode *n)
{
	return (n == nullptr ? DOUBLE_BLACK : n->color);
}
//single link

class RBTree{
	private:
		RBNode *root;
	public:
		RBTree()
		{ 
			root = nullptr;
		}
		void insert(int value)
		{
			root = __insert(root, value);
			root->color = BLACK;
		}
		
		void inorder()
		{
			__inorder(root);
		}
		
		RBNode* find(int value)
		{
			return __find(root, value);
		}
	
		void delete_node(int value)
		{
			if(find(value) == nullptr) return;
			root = __delete_node(root, value);
			if(root) root->color = BLACK;
		}
	
	private:
		RBNode* __insert(RBNode* root, int value)
		{
			if(root == nullptr){
				root = new RBNode(value, RED);
				return root;
			}else if(root->value < value){
				root->rchild = __insert(root->rchild, value);
			}else if(root->value > value){
				root->lchild = __insert(root->lchild, value);
			}
			return insert_maintain(root);
		}
		
		RBNode* left_rotate(RBNode *root)
		{
			RBNode* tmp = root->rchild;
			root->rchild = tmp->lchild;
			tmp->lchild = root;
			return tmp;
		}
		
		RBNode* right_rotate(RBNode *root)
		{
			RBNode* tmp = root->lchild;
			root->lchild = tmp->rchild;
			tmp->rchild = root;
			return tmp;
		}
		
		RBNode* insert_maintain(RBNode *root)
		{
			if(C(root->lchild) == RED && C(root->rchild) == BLACK && (C(root->lchild->rchild) == RED || C(root->lchild->rchild) == RED)){
				if(C(root->lchild->rchild) == RED){
					root->lchild = left_rotate(root->lchild);
				}
				root = right_rotate(root);
				root->color = BLACK;
				root->rchild->color = RED;
			}else if(C(root->rchild) == RED && C(root->lchild) == BLACK && (C(root->rchild->lchild) == RED || C(root->rchild->rchild) == RED)){
				
				if(C(root->rchild->lchild) == RED){
					root->rchild = right_rotate(root->rchild);
				}
				root = left_rotate(root);
				root->color = BLACK;
				root->lchild->color = RED;
			}else if(C(root->rchild) == RED && C(root->lchild) == RED\
				&&(C(root->rchild->lchild) == RED || C(root->rchild->rchild) == RED ||\
				 C(root->lchild->rchild) == RED || C(root->lchild->rchild) == RED)){
				
				root->color = RED;
				root->lchild->color = BLACK;
				root->rchild->color = BLACK;
			}
			return root;
		}
		
		void __inorder(RBNode* root)
		{
			if(root == nullptr) return;
			std::printf("%d %s | %d %d \n", K(root), root->color == RED ? "red" : "black", K(root->lchild), K(root->rchild));
			__inorder(root->lchild);
			__inorder(root->rchild);
		}
		
		RBNode* __find(RBNode* root, int value)
		{
			if(root == nullptr) return nullptr;
			if(root->value == value) return root;
			if(root->value < value) return __find(root->rchild, value);
			else return __find(root->lchild, value);
		}
		
		void swap(RBNode* tmp, RBNode* root)
		{
			int p = tmp->value;
			tmp->value = root->value;
			root->value = p;
		}
		
		RBNode* __delete_node(RBNode* root, int value)
		{
			if(root->value == value){
				if(root->lchild == nullptr && root->rchild == nullptr){
					if(root->color == BLACK){
						C = fun2;
					}
					delete root;
					return nullptr;
				}else if(root->lchild != nullptr && root->rchild != nullptr){
					RBNode* tmp = root->lchild;
					while(tmp->rchild != nullptr){
						tmp = tmp->rchild;
					}
					swap(tmp, root);
					root->lchild = __delete_node(root->lchild, value);
				}else{
					RBNode* tmp = root;
					if(root->lchild == nullptr)
						root = root->rchild;
					else
						root = root->lchild;
					root->color = BLACK;
					delete tmp;
					return root;
				}
			}else if(root->value < value){
				root->rchild = __delete_node(root->rchild, value);
			}else{
				root->lchild = __delete_node(root->lchild, value);
			}
			return delete_maintain(root);
		}
		
		RBNode* delete_maintain(RBNode* root)
		{
			if(C(root->lchild) == DOUBLE_BLACK && C(root) == RED && C(root->rchild) == BLACK){
				if(C(root->rchild->lchild) == RED || C(root->rchild->lchild) == RED){
					if(C(root->rchild->lchild) == RED){
						root->rchild = right_rotate(root->rchild);
						root->rchild->color = BLACK;
						root->rchild->rchild->color = RED;
					}
					root = left_rotate(root);
				}else{
					root->color = BLACK;
					root->rchild->color = RED;
				}
				C = fun1;
				return root;
			}
			if(C(root->rchild) == DOUBLE_BLACK && C(root) == RED && C(root->lchild) == BLACK){
				if(C(root->lchild->lchild) == RED || C(root->lchild->rchild) == RED){
					if(C(root->lchild->rchild) == RED){
						root->lchild = left_rotate(root->lchild);
						root->lchild->color = BLACK;
						root->lchild->lchild->color = RED;
					}
					root = right_rotate(root);
				}else{
					root->color = BLACK;
					root->lchild->color = RED;
				}
				C = fun1;
				return root;
			}

			if(C(root->lchild) == DOUBLE_BLACK && C(root) == BLACK){
				if(C(root->rchild) == RED){
					root = left_rotate(root);
					root->color = BLACK;
					root->lchild->color = BLACK;
					root->lchild->rchild->color = RED;
				}else{
					root->rchild->color = RED;
					root->color = DOUBLE_BLACK;
				}
				C = fun1;
				return root;
			}
			if(C(root->rchild) == DOUBLE_BLACK && C(root) == BLACK){
				if(C(root->lchild) == RED){
					root = right_rotate(root);
					root->color = BLACK;
					root->rchild->color = BLACK;
					root->rchild->lchild->color = RED;
				}else{
					root->lchild->color = RED;
					root->color = DOUBLE_BLACK;
				}
				C = fun1;
				return root;
			}
			return root;
		}
};


int main()
{
	RBTree obj;
	int array[] = {333, 532, 1, 4, 3, 2, 98, 7, 99, 45, 54, 6};
	int i;
	for(i = 0; i < 12; i++)
		obj.insert(array[i]);
	obj.delete_node(45);
	obj.inorder();
	return 0;
}