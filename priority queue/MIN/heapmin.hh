#ifndef _HEAPMIN_HH_
#define _HEAPMIN_HH_

#include <iostream>
#include <cassert> //para generar los mensajes de error
#include <vector>
#include <utility>
#include <string>

using namespace std;

template<typename T>
class HeapMin{

private:
	vector<T> storage;

	int getLeft(int n) const{return 2*n+1;}	 //obtiene la pos del hijo izquierdo
	bool hasLeft(int n) const {return getLeft(n) < size();}  //devuelve si existe hijo izquierdo
	int getRight(int n) const { return 2*n+2;} //obtiene la pos del hijo derecho
	bool hasRight(int n) const { return getRight(n) < size();}//valida si existe hijo derecho
	bool isRoot(int n) const { return n==0;}//valida si la pos ingresada es el root
	int parent (int n)  const { return (n-1)/2;}//devuelve la pos del papa de un nodo

	//Todas las anteriores en complejidades constantes

public:
	HeapMin(): storage() {}
	//HeapMin(const HeapMin<T> &other): storage(other.storage) {}

	bool empty() const { return storage.size()==0;}
	int size() const {return storage.size();}

	void print()  {
		for( const T &a :storage){
			cout << a << " ";
		}
		cout << endl;
	}

	T min() const { assert(!empty()); return storage[0];}
	T& min()  {
	 	assert(!empty());
	  	return storage[0];
	  }

	void insert(T elem){
		storage.push_back(elem);
		heapiFy_up(size()-1);
	}

	void removeMin(){
		if(empty()) return;
		swap(storage[0],storage[size()-1]);
		storage.pop_back();
		heapiFy_down(0);
	}

private:
	void heapiFy_up(int q){
		if(!isRoot(q)){
			int p=parent(q);
			if(storage[q] < storage[p]){
				swap(storage[p],storage[q]);
				heapiFy_up(p);
			}
		}
	}

	void heapiFy_down(int q){
		if(empty()) return;
		if(!hasRight(q) && !hasLeft(q)) return;
		if(hasRight(q) && hasLeft(q)){
			int right = getRight(q);
			int left = getLeft(q);
			if(storage[right] < storage[left]){
				if(storage[right] < storage[q]){
					swap(storage[q],storage[right]);
					heapiFy_down(right);
				}
			}else{
				if(storage[left] < storage[q]){
					swap(storage[q],storage[left]);
					heapiFy_down(left);
				}
			}
		}
		else if(hasLeft(q) && !hasRight(q)){
			//int right = getRight(q);
			int left = getLeft(q);
			if(storage[left] < storage[q]){
				swap(storage[q],storage[left]);
			}
		}
	}

};
#endif