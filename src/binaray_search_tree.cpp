#include <iostream>

class BSTNode{
	public:
		int value;
		BSTNode *lchild, *rchild;
		
		BSTNode(int value)
		{
			this->value = value;
			lchild = rchild = nullptr;	
		}	
};

class BSTree{
	private:
		BSTNode* root;
	public:
		BSTree()
		{ root = nullptr; }
		
		void insert(int value)
		{
			root = __insert(root, value);
		}
		
		void inorder()
		{
			__inorder(root);
		}
		
		BSTNode* find(int value)
		{
			return __find(root, value);
		}
		
		void delete_node(int value)
		{
			if(find(value) == nullptr) return;
			root = __delete_node(root, value);
		}
	private:
		BSTNode* __insert(BSTNode* root, int value)
		{
			if(root == nullptr){
				BSTNode* tmp = new BSTNode(value);
				root = tmp;
			}else{
				if(root->value > value){
					root->lchild = __insert(root->lchild, value);
				}else if(root->value < value){
					root->rchild = __insert(root->rchild, value);
				}
			}
			return root;
		}
		
		void __inorder(BSTNode *root)
		{
			if(root == nullptr){
				return;
			}
			__inorder(root->lchild);
			std::cout << root->value << "\t";
			__inorder(root->rchild);
		}
		
		BSTNode* __find(BSTNode* root, int value)
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
		BSTNode *p;
		
		void swap(BSTNode *root, BSTNode *p)
		{
			int tmp = root->value;
			root->value = p->value;
			p->value = tmp;
		}
		
		BSTNode* __delete_node(BSTNode *root, int value)
		{
			if(root->value == value){
				if(root->lchild == nullptr && root->rchild == nullptr){
					delete root;
					root = nullptr;
				}else if(root->lchild != nullptr && root->rchild == nullptr){
					p = root;
					root = root->lchild;
					delete p;
				}else if(root->lchild == nullptr && root->rchild != nullptr){
					p = root;
					root = root->rchild;
					delete p;
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
			return root;
		}
};

int main()
{
	BSTree obj;
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