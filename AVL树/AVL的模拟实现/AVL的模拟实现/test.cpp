#include"AVLtree.h"
#include<iostream>
using namespace std;

void test()
{
	int tes[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	BST<int> tree;
	for (auto& e : tes)
	{
		tree.Insert(e);
	}
	tree.InOrder();
	cout << endl;
	tree.InOrderbf();
}


int main()
{
	test();


	return 0;
}