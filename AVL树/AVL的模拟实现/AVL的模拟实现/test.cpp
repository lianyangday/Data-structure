﻿#include"AVLtree.h"
#include<iostream>
using namespace std;

void test()
{
	//int tes[] = { 3,7,9,11,14,15,16,18,26 };
	int tes[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	BST<int> tree;
	for (auto& e : tes)
	{
		tree.Insert(e);
	}
	tree.InOrder();

}


int main()
{
	test();


	return 0;
}