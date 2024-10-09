
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//*
//搜索二叉树是一种特殊的二叉树
//每一个节点的右叶子节点都比父亲节点大，左子节点都比父节点小

template<class T>
class BST_Node
{
public:
	BST_Node(const T& key)
		:_key(key),
		_right(nullptr),
		_left(nullptr),
		_parent(nullptr),
		_bf(0)
	{}
	T _key;
	BST_Node* _right = nullptr;
	BST_Node* _left = nullptr;
	BST_Node* _parent = nullptr;
	//高度差：右子树的高度-左子树的高度
	int _bf = 0;
};


template<class T>
class BST
{
public:
	typedef BST_Node<T>  Node;
	//*左单旋
	Node* lrotate(Node*ronode)
	{
		Node* subr = ronode->_right;
		Node* subrl = subr->_left;
		ronode->_right = subrl;
		subr->_left = ronode;

		//*调整三个节点的双亲节点
		Node* ronodep = ronode->_parent;

		if (ronodep != nullptr)
		{
			if (ronode == ronodep->_left)
				ronodep->_left = subr;
			else
				ronodep->_right = subr;
		}
		else
		{
			_root = subr;
		}
		subr->_parent = ronodep;
		if(subrl!=nullptr)
		subrl->_parent = ronode;
		ronode->_parent = subr;
		subr->_bf = 0;
		ronode->_bf = 0;

		return subr;
	}

	//*右单旋
	Node* rrotate(Node* ronode)
	{
		Node* subl = ronode->_left;
		Node* sublr = subl->_right;
		ronode->_left = sublr;
		subl->_right = ronode;

		Node* ronodep = ronode->_parent;
		if (ronodep != nullptr)
		{
			if (ronode == ronodep->_left)
				ronodep->_left = subl;
			else
				ronodep->_right = subl;
		}
		else
		{
			_root = subl;
		}
		
		subl->_parent = ronodep;
		if (sublr != nullptr)
		sublr->_parent = ronode;
		ronode->_parent = subl;
		subl->_bf = 0;
		ronode->_bf = 0;

		return subl;
	}

	Node* rlrotate(Node* ronode)
	{
		int judbf = ronode->_right->_left->_bf;
		//*1.右单旋
		ronode = rrotate(ronode->_right);
		//*2.左单旋转
		ronode = lrotate(ronode->_parent);

		ronode->_bf = 0;
		if (judbf == 1)
		{
			ronode->_right->_bf = 0;
			ronode->_left->_bf = -1;
		}
		else if (judbf == -1)
		{
			ronode->_left->_bf = 0;
			ronode->_right->_bf = 1;
		}
		else
		{
			ronode->_left->_bf = 0;
			ronode->_right->_bf = 0;
		}

		return ronode;
	}

	Node* lrrotate(Node* ronode)
	{
		int judbf = ronode->_left->_right->_bf;
		//*1.左单旋
		ronode = lrotate(ronode->_left);
		//*2.右单旋转
		ronode = rrotate(ronode->_parent);

		ronode->_bf = 0;
		if (judbf == 1)
		{
			ronode->_right->_bf = 0;
			ronode->_left->_bf = -1;
		}
		else if (judbf == -1)
		{
			ronode->_left->_bf = 0;
			ronode->_right->_bf = 1;
		}
		else
		{
			ronode->_left->_bf = 0;
			ronode->_right->_bf = 0;
		}

		return ronode;
	}




	//*插入功能
	bool Insert(const T& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		Node* newnode = new Node(key);
		//根节点为空
		if (_root == nullptr)
		{
			_root = newnode;
			return true;
		}
		while (cur != nullptr)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//出现重复的数据,插入失败
				//cout << "重复" << endl;
				return false;
			}
		}
		//插入
		if (parent->_key > key)
		{
			parent->_left = newnode;
			newnode->_parent = parent;
		}
		else
		{
			parent->_right = newnode;
			newnode->_parent = parent;
		}

		cur = newnode;
		//插入元素之后进行平衡因子的检查
		while (parent)
		{

			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				break;
			}
			else if(parent->_bf == 1 || parent->_bf == -1)
			{	
					cur = parent;
					parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && parent->_right->_bf == 1)
				{
					//调用左旋
					lrotate(parent);
					
					
				}
				else if (parent->_bf == -2 && parent->_left->_bf == -1)
				{
					rrotate(parent);
					
				}
				else if (parent->_bf == 2 && parent->_right->_bf == -1)
				{
					//*先右旋再左旋
					rlrotate(parent);
					
				}
				else if (parent->_bf == -2 && parent->_left->_bf == 1)
				{
					//*先左旋再右旋
					lrrotate(parent);

				}
			}
			else
			{
				assert(1);
			}
		}

		return true;
	}

	int height(Node* root)
	{
		if(root == nullptr)
			return 0;

		int heigthright = height(root->_right);
		int heigthleft = height(root->_left);

		return heigthright > heigthleft ? heigthright + 1 : heigthleft + 1;
	}

	int Height()
	{
		return height(_root);
	}
	bool Isbalance()
	{
		return isbalance(_root);
	}
	//判断是否平衡
	bool isbalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int heightright = height(root->_right);
		int heightleft = height(root->_left);
		int diff = heightright - heightleft;

		if (abs(diff) > 2)
		{
			cout << "平衡因子错误" << endl;
			return false;
		}

		if (root->_bf != diff)
		{
			cout << "平衡因子错误" << endl;
			return false;
		}

		return isbalance(root->_right) && isbalance(root->_left);
	}

	//*查找功能
	Node* Find(const T& key)
	{
		Node* cur = _root;
		if (_root == nullptr)
			return nullptr;
		while (cur != nullptr)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				//出现重复的数据,插入失败
				return cur;
			}
		}
		return nullptr;
	}
	////删除功能（待修改）
	//bool Erase(const T& key)
	//{
	//	Node* cur = _root;
	//	Node* parent = cur;
	//	while (cur != nullptr)
	//	{
	//		if (cur->_key > key)
	//		{
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else if (cur->_key < key)
	//		{
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}

	//	//*没有找到该数据
	//	if (cur == nullptr)
	//	{
	//		return false;
	//	}

	//	//*找到该数据

	//	//*1.数据所在的节点没有子节点，或者只有一个子节点
	//	if (cur->_left == nullptr || cur->_right == nullptr)
	//	{
	//		if (parent->_key > key)
	//		{
	//			if (cur->_left == nullptr)
	//				parent->_left = cur->_right;
	//			else
	//				parent->_left = cur->_left;
	//		}
	//		else if (parent->_key < key)
	//		{
	//			if (cur->_left == nullptr)
	//				parent->_right = cur->_right;
	//			else
	//				parent->_right = cur->_left;
	//		}
	//		else
	//		{
	//			if (cur->_left == nullptr)
	//				_root = cur->_right;
	//			else
	//				_root = cur->_left;
	//		}
	//		delete cur;
	//	}

	//	//*2.数据所在的节点，友两个子节点
	//	else
	//	{
	//		//找到需要交换的叶子结点
	//		Node* tar = cur->_right;
	//		Node* tarparent = cur;
	//		while (tar->_left != nullptr)
	//		{
	//			tarparent = tar;
	//			tar = tar->_left;
	//		}

	//		//数据进行交换
	//		cur->_key = tar->_key;

	//		//对叶子节点进行删除
	//		if (tar == cur->_right)
	//			tarparent->_right = tar->_right;
	//		else
	//			tarparent->_left = tar->_right;
	//		delete tar;
	//	}
	//}
	// 中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}


private:
	Node* _root = nullptr;
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << "("<<root->_key <<","<< root->_bf << ")" << " ";
		_InOrder(root->_right);
	}
};



