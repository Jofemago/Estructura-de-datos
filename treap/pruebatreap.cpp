#include "treap.hh"
#include <iostream>
#include <functional>

using namespace std;

int main(){
	Treap<int> b;

	b.insert(8);
	b.insert(10);
	b.insert(25);
	/*b.insert(5);
	b.insert(17);
	b.insert(1);*/
	b.print();

	/*cout << endl << endl << endl;

	b.remove(25);
	b.remove(5);
	b.remove(8);
	b.print();*/

	/*b.inorder([](int key){cout << key <<" ";});
	cout << endl;*/
}