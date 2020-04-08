#include "SplayTree.h"
#include <string>
#include <iostream>
using namespace std;
int main(/*int argc, const char *argv[]*/)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SplayTree<int> splay;

	splay.insert(8);
	splay.insert(6);
	splay.insert(7);
	splay.insert(5);
	splay.insert(9);
	splay.insert(25);
	splay.insert(15);
	splay.insert(13);
	splay.insert(24);
	splay.insert(10);
	splay.insert(4);
	splay.insert(20);
	splay.insert(16);
	splay.insert(14);
	splay.insert(3);
	splay.insert(19);
	splay.insert(17);
	splay.insert(2);
	splay.insert(18);
	splay.insert(1);
	splay.insert(11);
	splay.insert(23);
	splay.insert(12);
	splay.insert(22);
	splay.insert(21);

	for (int i = 0; i < splay.size(); i++)
		cout << splay.preOrderWalk().at(i) << " ";


	splay.remove(19);
	splay.remove(1);
	//splay.ToGraphvizFile("beforesplay25.txt");
	if (splay.find(25))
	{
		cout << "exist" << endl;
	}
	else
	{
		cout << "not exist" << endl;
	}
	
	cout << "max:  " << splay.getMax() << endl;
	cout << "min:  " << splay.getMin() << endl;

	//cout << splay.getRoot() << endl;
	//for (int i = 0; i < splay.size(); i++)
	//	cout << splay.preOrderWalk().at(i) << " ";

	//splay.ToGraphvizFile("aftersplay25.txt");

	return 0;
}