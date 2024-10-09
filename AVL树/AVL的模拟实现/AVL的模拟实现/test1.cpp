#include"AVLtree.h"
#include<iostream>
#include<vector>
using namespace std;

void test()
{
	//int tes[] = { 3,7,9,11,14,15,16,18,26 };
	int tes[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int tes[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14};
	//const int N = 100000;
	//vector<int> v;
	//v.reserve(N);
	//srand(time(0));

	//for (size_t i = 0; i < N; i++)
	//{
	//	//v.push_back(i);
	//	v.push_back(rand());
	//}

	size_t begin1 = clock();

	BST<int> tree;
	int i = 0;
	for (auto& e : tes)
	{
		tree.Insert(e);
		tree.Isbalance();
		//tree.InOrder();
		cout << "i:" << i << endl;
		i++;
	}
	//tree.Isbalance();
	size_t end1 = clock();

	cout << "insert:" << end1 - begin1 << endl;
	cout << "Heigth:" << tree.Height() << endl;
	tree.InOrder();

}

	int main()
	{
		test();
		return 0;
	}