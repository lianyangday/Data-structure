
#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//*
//������������һ������Ķ�����
//ÿһ���ڵ����Ҷ�ӽڵ㶼�ȸ��׽ڵ�����ӽڵ㶼�ȸ��ڵ�С

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
	//�߶Ȳ�������ĸ߶�-�������ĸ߶�
	int _bf = 0;
};


template<class T>
class BST
{
public:
	typedef BST_Node<T>  Node;
	//*����
	Node* lrotate(Node*ronode)
	{
		Node* subr = ronode->_right;
		Node* subrl = subr->_left;
		ronode->_right = subrl;
		subr->_left = ronode;

		//*���������ڵ��˫�׽ڵ�
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

	//*�ҵ���
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
		//*1.�ҵ���
		ronode = rrotate(ronode->_right);
		//*2.����ת
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
		//*1.����
		ronode = lrotate(ronode->_left);
		//*2.�ҵ���ת
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




	//*���빦��
	bool Insert(const T& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		Node* newnode = new Node(key);
		//���ڵ�Ϊ��
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
				//�����ظ�������,����ʧ��
				//cout << "�ظ�" << endl;
				return false;
			}
		}
		//����
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
		//����Ԫ��֮�����ƽ�����ӵļ��
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
					//��������
					lrotate(parent);
					
					
				}
				else if (parent->_bf == -2 && parent->_left->_bf == -1)
				{
					rrotate(parent);
					
				}
				else if (parent->_bf == 2 && parent->_right->_bf == -1)
				{
					//*������������
					rlrotate(parent);
					
				}
				else if (parent->_bf == -2 && parent->_left->_bf == 1)
				{
					//*������������
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
	//�ж��Ƿ�ƽ��
	bool isbalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int heightright = height(root->_right);
		int heightleft = height(root->_left);
		int diff = heightright - heightleft;

		if (abs(diff) > 2)
		{
			cout << "ƽ�����Ӵ���" << endl;
			return false;
		}

		if (root->_bf != diff)
		{
			cout << "ƽ�����Ӵ���" << endl;
			return false;
		}

		return isbalance(root->_right) && isbalance(root->_left);
	}

	//*���ҹ���
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
				//�����ظ�������,����ʧ��
				return cur;
			}
		}
		return nullptr;
	}
	////ɾ�����ܣ����޸ģ�
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

	//	//*û���ҵ�������
	//	if (cur == nullptr)
	//	{
	//		return false;
	//	}

	//	//*�ҵ�������

	//	//*1.�������ڵĽڵ�û���ӽڵ㣬����ֻ��һ���ӽڵ�
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

	//	//*2.�������ڵĽڵ㣬�������ӽڵ�
	//	else
	//	{
	//		//�ҵ���Ҫ������Ҷ�ӽ��
	//		Node* tar = cur->_right;
	//		Node* tarparent = cur;
	//		while (tar->_left != nullptr)
	//		{
	//			tarparent = tar;
	//			tar = tar->_left;
	//		}

	//		//���ݽ��н���
	//		cur->_key = tar->_key;

	//		//��Ҷ�ӽڵ����ɾ��
	//		if (tar == cur->_right)
	//			tarparent->_right = tar->_right;
	//		else
	//			tarparent->_left = tar->_right;
	//		delete tar;
	//	}
	//}
	// �������
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



