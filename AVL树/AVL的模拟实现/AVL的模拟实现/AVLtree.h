#pragma once
#include<iostream>
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
	typedef BST_Node<T> Node;
	//*左单旋
	BST_Node* lrotate(BST_Node*ronode)
	{
		BST_Node* subr = ronode->_right;
		BST_Node* subrl = subr->_left;
		ronode->_right = subrl;
		subr->_right = ronode;

		//*调整三个节点的双亲节点
		BST_Node* ronodep=ronode->_parent;
		if (ronode == ronodep->_left)
			ronodep->_left = subr;
		else
			ronofr->_right = subr;

		subr->_parent = ronodep;
		subrl->_parent = ronode;
		ronode->_parent = subr;
		return subr;
	}

	//*右单旋
	BST_Node* rrotate(BST_Node* ronode)
	{
		BST_Node* subl = ronode->_left;
		BST_Node* sublr = subl->_right;
		ronode->_left = sublr;
		subl->_left = ronode;

		BST_Node* ronodep = ronode->_parent;
		if (ronode == ronodep->_left)
			ronodep->_left = subl;
		else
			ronofr->_right = subl;

		subl->_parent = ronodep;
		sublr->_parent = ronode;
		ronode->_parent = subl;
		return subl;
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

		//插入元素之后进行平衡因子的检查
		cur = newnode;
		while (cur!=nullptr)
		{
			if (cur == parent->_right)
				parent->_bf++;
			else
				parent->_bf--;

			if (parent->_bf == 0)
			{
				break;
			}
			if else(parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if(parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && parent->_right->_bf == 1)
				{
					//调用左旋
					parent=lrotate(parent);
					parent->_bf = 0;
					parent->_left->_bf = 0;
				}
				else if (parent->_bf == -2 && parent->_left->_bf == -1)
				{
					parent = lrotate(parent);
					parent->_bf = 0;
					parent->_right->_bf = 0;
				}
				else if (parent->_bf == 2 && parent->_right->_bf == -1)
				{
					int judbf = parent->_right->_left->_bf;
					//*1.右单旋
					parent=rrotate(parent->_right);
					//*2.左单旋转
					parent = lrotate(parent->_parent);

					parent->_bf = 0;
					if (judbf == 1)
					{
						parent->_right = 0;
						parent->_left = -1;
					}
					else
					{
						parent->_left = 0;
						parent->_right = 1;
					}
				}
				else if (parent->_bf == -2 && parent->_right->_bf == 1)
				{
					int judbf = parent->_left->_right->_bf;
					//*1.左单旋
					parent = lrotate(parent->_right);
					//*2.右单旋转
					parent = rrotate(parent->_parent);

					parent->_bf = 0;
					if (judbf == 1)
					{
						parent->_right = 0;
						parent->_left = -1;
					}
					else
					{
						parent->_left = 0;
						parent->_right = 1;
					}
				}
			}
			else
			{
				assert(1);
			}
		}
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
	//删除功能
	bool Erase(const T& key)
	{
		Node* cur = _root;
		Node* parent = cur;
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
				break;
			}
		}

		//*没有找到该数据
		if (cur == nullptr)
		{
			return false;
		}

		//*找到该数据

		//*1.数据所在的节点没有子节点，或者只有一个子节点
		if (cur->_left == nullptr || cur->_right == nullptr)
		{
			if (parent->_key > key)
			{
				if (cur->_left == nullptr)
					parent->_left = cur->_right;
				else
					parent->_left = cur->_left;
			}
			else if (parent->_key < key)
			{
				if (cur->_left == nullptr)
					parent->_right = cur->_right;
				else
					parent->_right = cur->_left;
			}
			else
			{
				if (cur->_left == nullptr)
					_root = cur->_right;
				else
					_root = cur->_left;
			}
			delete cur;
		}

		//*2.数据所在的节点，友两个子节点
		else
		{
			//找到需要交换的叶子结点
			Node* tar = cur->_right;
			Node* tarparent = cur;
			while (tar->_left != nullptr)
			{
				tarparent = tar;
				tar = tar->_left;
			}

			//数据进行交换
			cur->_key = tar->_key;

			//对叶子节点进行删除
			if (tar == cur->_right)
				tarparent->_right = tar->_right;
			else
				tarparent->_left = tar->_right;
			delete tar;
		}
	}
	// 中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};