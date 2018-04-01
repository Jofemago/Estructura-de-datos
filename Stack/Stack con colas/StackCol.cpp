#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include "Mylist.hh"
//#include "Colalist.hh"

using namespace std;
//------------------------------------------------------------------------
template <typename T>
class Queue {
private:
	Mylist<T> storage;
public:
	Queue(): storage() {}
	Queue(const Queue<T> &other): storage(other.storage) {} //constructor de copias de storage
	bool empty() const{ return storage.empty();} // valida si la cola esta vacia

	void push(T elem){ storage.push_back(elem);} //agrega un elemento al final de la cola 

	void pop(){
		assert(!empty());
		storage.pop_front();} // saca un elemento por el principio dee la cola 

	const T &front() const{ //muestra el primer elemento de la cola
		assert(!empty());
		return storage.front();
	}

	T &front() { //muestra el primer elemento de la cola
		assert(!empty());
		return storage.front();
	}

	int getSize() const {return storage.getSize();} //muestra cuantos elementos tiene

	void print() const { storage.print();} //muestra la cola

};
//-----------------------------------------------------------------------------------

template <typename T>
class Stack{
	private:
		Queue<T> storage;
	public:
		Stack(): storage()  {}
		Stack(const Stack<T> & other): storage(other.storage) {}

		bool empty() const { return storage.empty(); } //O(1)

		int getSize() const { return storage.getSize();}//O(1)

		void push(T elem){  storage.push(elem);} //pone un elemento de storage en la pila, O(1)

		const T& top() const {
			Queue<T> c(storage);
			while(c.getSize()!=1){
				c.front();
			}
			return c.front();
		}

		T& top()  {
			Queue<T> c(storage);
			while(c.getSize()!=1){
				c.pop();
			}
			return c.front();
		}

		void pop(){
			assert(!empty());
			int n= getSize() -1;
			while (n>0){
				storage.push(storage.front());
				storage.pop();
				n--;
			}
			storage.pop();
		}

		void print() const {
		storage.print();
	}



};

int main(){
	Stack<int> t;
	for (int i=0; i<5; i++)
		t.push(rand()%5);
	Stack<int> x(t);
	
	x.print();
	for(int i=0;i<5; i++){
		t.print();
		cout << t.top() << endl;
	t.pop();
	t.print();}
	return 0;


}