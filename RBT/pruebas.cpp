
#include <iostream>
#include <vector> // used by findInterval
#include <cassert>
#include "rbt.hh"
#include <string>

using namespace std;

int main (){
	RBT<int,string> q;
	q.insert(9,"hola");
	q.insert(13,"chao");
	q.insert(12,"afa");
	q.insert(28,"ada");
	q.insert(1,"kfd");
	q.insert(10,"jja");
	q.insert(30,"jeje");
	q.insert(18,"jojo");
	q.insert(-5,"juju");
	q.insert(14,"jiji");
	q.insert(6,"juju");

	/*pair<bool,string> h= q.find(35);

	if(h.first){
		cout << h.second << endl;
	}*/	
	
	vector<string> j = q.findInterval(1,34);

	for( const string &v:j){
		cout << v << " ";
	}
	cout << endl;

	return 0;
}