#include <iostream>
#include <cstring>
#include <vector>

class Node{
	public:
		char value;
		Node* lchild;
		Node* rchild;
		
		Node(char value)
		{
			this->value = value;
			this->lchild = this->rchild = NULL;	
		}
};

class BTree{
	private:
		Node* root;
	public:
		BTree()
		{
			root = NULL;	
		}
		
		void create_btree(const char* str)
		{
			Node* tmp, *p;
			int size = std::strlen(str);
			int i, k;
			root = new Node(str[0]);
			p = root;
			std::vector<Node*> stack;
			for(i = 1; i < size; i++){
				switch(str[i]){
					case '(':
						stack.push_back(p);
						k = 1;
						break;
					case ',':
						k = 2;
						break;
					case ')':
						stack.pop_back();
						break;
					default:
						tmp = stack.back();
						p = new Node(str[i]);
						switch(k)
						{
							case 1:
								tmp->lchild = p;
								break;
							case 2:
								tmp->rchild = p;
								break;
						}
				}
			}
		}
		
		void preorder()
		{
			__preorder(root);
		}
		
		int find_high()
		{
			return __find_high(root);
		}
	private:
		void __preorder(Node* tmp)
		{
			if(tmp == NULL) return;
			std::cout << tmp->value << std::endl;
			__preorder(tmp->lchild);
			__preorder(tmp->rchild);
		}
		int __find_high(Node* tmp)
		{
			if(tmp == NULL){
				return 0;
			}
			int left, right;
			left = __find_high(tmp->lchild);
			right = __find_high(tmp->rchild);
			if(left > right)	return left + 1;
			else	return right + 1;
		}
};

int main()
{
	BTree obj;
	obj.create_btree("a(b(f,g),c(d,e(,u(,i(,a(,v))))))");
	obj.preorder();
	std::cout << obj.find_high();
	return 0;
}