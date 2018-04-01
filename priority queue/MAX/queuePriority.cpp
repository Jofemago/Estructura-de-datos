#include <iostream>
#include <cassert> //para generar los mensajes de error
//#include <vector>
#include <utility>
#include <string>
#include "heapmax.hh"

template<typename T>
class PriorityQueue{
private:
	HeapMax<pair<int,T>> storage;
public:
	PriorityQueue(): storage() {}

	void push(T elem, int prio){ storage.insert({prio,elem}); }

	void pop(){ storage.removeMax(); }

	T front() const { return storage.max().second;}
	T& front()  { return storage.max().second;}

	int size(){return storage.size();}

};

template<typename K>
bool operator <(const pair<int,K> &lhs , const pair<int,K> &rhs){
	return lhs.first < rhs.first;
}

int main (){
	PriorityQueue<string> p;

	p.push("camilo",25);
	p.push("es",3);
	p.push("una",4);
	p.push("buena",9);
	p.push("persona",18);
	p.push("9",1);
	p.push("10",1);

	cout << p.front() << " " << p.size()<< endl;
	p.pop();
	cout << p.front() << " " << p.size()<< endl;
	p.pop();
	cout << p.front() << " " << p.size()<< endl;
	p.pop();
	cout << p.front() << " " << p.size()<< endl;
	p.pop();
	cout << p.front() << " " << p.size()<< endl;
	p.pop();
	cout << p.front() << " " << p.size()<< endl;
	p.pop();


}