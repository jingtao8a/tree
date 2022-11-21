#include <iostream>
#include <cmath>
#define H(n) ((n) == nullptr ? 0 : (n)->h)

class AVLNode{
	public:
		int value;
		int h;//height
		AVLNode *lchild, *rchild;
		
		AVLNode(int value)
		{
			this->value = value;
			h = 1;
			lchild = rchild = nullptr;	
		}
};

class AVLTree{
	private:
		AVLNode *root;
	public:
		AVLTree()
		{
			root = nullptr;
		}
		void insert(int value)
		{
			root = __insert(root, value);
		}
		
		void inorder()
		{
			__inorder(root);
		}
		
		AVLNode* find(int value)
		{
			return __find(root, value);
		}
		
		void delete_node(int value)
		{
			if(find(value) == nullptr) return;
			root = __delete_node(root, value);
		}
	private:
		void update_height(AVLNode *root)
		{
			if(root == nullptr) return;
			root->h = H(root->lchild) > H(root->rchild) ? (H(root->lchild) + 1) : (H(root->rchild) + 1); 
		}
		AVLNode* left_rotate(AVLNode* root)
		{
			AVLNode* p = root->rchild;
			root->rchild = p->lchild;
			p->lchild = root;
			update_height(root);
			update_height(p);
			return p;
		}
		AVLNode* right_rotate(AVLNode* root)
		{
			AVLNode* p = root->lchild;
			root->lchild = p->rchild;
			p->rchild = root;
			update_height(root);
			update_height(p);
			return p;
		}
		AVLNode* maintain(AVLNode *root)
		{
			if(root == nullptr) return nullptr;
			if(abs(H(root->lchild) - H(root->rchild)) <= 1){
				return root;
			}
			if(H(root->lchild) > H(root->rchild)){//insert into left child
				if(H(root->lchild->rchild) > H(root->lchild->lchild)){//LR
					root->lchild = left_rotate(root->lchild);
				}
				root = right_rotate(root);
			}else{
				if(H(root->rchild->lchild) > H(root->rchild->rchild)){//RL
					root->rchild = right_rotate(root->rchild);
				}
				root = left_rotate(root);
			}
			return root;
		}
		
		AVLNode* __insert(AVLNode* root, int value)
		{
			if(root == nullptr){
				root = new AVLNode(value);
				return root;
			}else if(root->value < value){
				root->rchild = __insert(root->rchild, value);
			}else if(root->value > value){
				root->lchild = __insert(root->lchild, value);
			}
			update_height(root);
			return maintain(root);
		}
		
		void __inorder(AVLNode *root)
		{
			if(root == nullptr){
				return;
			}
			__inorder(root->lchild);
			std::cout << root->value << "\t";
			__inorder(root->rchild);
		}
		
		AVLNode* __find(AVLNode* root, int value)
		{
			if(root == nullptr){
				return nullptr;
			}
			if(root->value == value){
				return root;
			}
			if(root->value > value){
				return __find(root->lchild, value);
			}else{
				return __find(root->rchild, value);
			}
		}
		
		void swap(AVLNode *root, AVLNode *p)
		{
			int tmp = root->value;
			root->value = p->value;
			p->value = tmp;
		}
		
		AVLNode *p;
		
		AVLNode* __delete_node(AVLNode *root, int value)
		{
			if(root->value == value){
				if(root->lchild == nullptr && root->rchild == nullptr){
					delete root;
					root = nullptr;
					return root;
				}else if(root->lchild != nullptr && root->rchild == nullptr){
					p = root;
					root = root->lchild;
					delete p;
					return root;
				}else if(root->lchild == nullptr && root->rchild != nullptr){
					p = root;
					root = root->rchild;
					delete p;
					return root;
				}else{
					p = root->lchild;
					while(p->rchild != nullptr){
						p = p->rchild;
					}
					swap(p, root);
					root->lchild = __delete_node(root->lchild, value);
				}
			}else if(root->value < value){
				root->rchild = __delete_node(root->rchild, value);
			}else{
				root->lchild = __delete_node(root->lchild, value);
			}
			update_height(root);
			return maintain(root);
		}
};

int main()
{
	AVLTree obj;
	int array[] = {333, 532, 1, 4, 3, 2, 98, 7};
	int i;
	for(i = 0; i < 8; i++)
		obj.insert(array[i]);
	obj.inorder();
	std::cout << "\n";
	obj.delete_node(333);
	obj.delete_node(4);
	obj.delete_node(98);
	obj.inorder();
	return 0;
}
