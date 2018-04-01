#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include "bst.hh"

using namespace std;

template <typename T>
class SET{
private:
	BST<T> storage; 

public:
	SET(): storage(){}

	SET(const SET<T> &other): storage(other.storage) {}

	void insert(T elem) { storage.insert(elem);}	//O(h)-- peor caso O(size)
	size_t getSize() const{ return storage.getSize();} //O(1)
	
	void print() const { storage.print();}

	bool pertenece(T elem)const { return storage.search(elem);}  //O(size)

	SET<T> Union( const SET<T>  &other) const{  //O(getSize()+other.Getsize())
		SET<T> r(other);
		storage.preorder([&](T n){ r.insert(n);});
		return r;
	}

	SET<T> Interseccion (const SET<T>  &other) const{//O(size*(other.storage.height) v O(other.size*(storage.height)))-> dependiendo de cual sea el mayor
		SET<T> r;
		if(getSize() < other.getSize()){
			storage.preorder([&](T n){if(other.pertenece(n)) r.insert(n);});
		}else {
			other.storage.preorder([&](T n){if(pertenece(n)) r.insert(n);});
		}
		return r;
	}

	SET<T> Diferencia(const SET<T>  &other) const{//O(size*(other.storage.height) v O(other.size*(storage.height)))-> dependiendo de cual sea el mayor
		SET<int> r;
		storage.preorder([&](T n){if(!other.pertenece(n)) r.insert(n);});
		return r;
	}


};

int main (){
	SET<int> t;
	for (int i=0; i < 15 ; i++){
		t.insert(rand()%100);
	}
	SET <int> v;
	for (int i=0; i < 15 ; i++){
		v.insert(rand()%100);
	}

	/*t.print();
	cout<< endl;
	cout<< endl;
	cout<< endl;
	v.print();*/

	cout<< t.pertenece(63)<< t.pertenece(86) << t.pertenece(27) << t.pertenece (29)  << endl;
	cout<< v.pertenece(63)<< v.pertenece(86) << v.pertenece(27) << v.pertenece (29)  << endl;
	cout << t.getSize()<< endl;
	cout << endl;
	SET<int> r(t);
	

	SET<int> k = v.Union(t);
	SET<int> h= t.Interseccion(v);
	SET<int> f= v.Diferencia(t);//v-t
	SET<int> g= t.Diferencia(v);// t-v
	//k.print();
	//h.print();
	//f.print();
	g.print();

	return 0;
}