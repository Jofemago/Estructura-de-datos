
#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include "Mylist.hh"
using namespace std;


//LIFO last to in first to out
//se van ingresadndo y si se sca algun elemento sale el ultimo que ha sido ingresado
//todos los elementos se apilan colocandose uno encima de otro  y sacando desde encima

template <typename T>
class Stack{
private:
	Mylist<T> storage;
public:
	Stack(): storage() {}
	Stack(const Stack<T> &other): storage(other.storage) {}//O(getsize())
	bool empty() const {return storage.empty();} //O(1)

	//o(1)
	int getSize() const { return storage.getSize();}//devuelve el numero de elementos que hay en la cola

	void push (T elem){  storage.push_front(elem);} ///O(1), coloca un elemento encima de los otros 

	void pop() {   //elimina el elemento principal de la cola 
		assert(!empty());
		storage.pop_front();
	}
	const T &top() const{ //retorna el elemento de arriba de la pila
	assert(!empty());
	 return storage.front();
	}

	T &top(){
	assert(!empty());
	return storage.front();
	}

	void print() const {
		storage.print();
	}
};

template <typename T>
class Queue{
private:
	Stack<T> storage;
public:
	Queue():storage() {}
	Queue(const Queue<T> &other): storage(other.storage) {}

	void push (T elem){//O(2size), vacia una pila en otra dejando el ultimo en el primero
	//luego inserto el elemento en la primera y vuelvo a vaciar la pila en el storage orginal dejando el elemento ingresado de ultimo en la cola
		if(empty()){
			storage.push(elem);
			return;
		}
	Stack<T> swap;
	while(!empty()){
	swap.push(storage.top());
	storage.pop();
	}
	swap.push(elem);
	swap.print();
	while(!swap.empty()){
		storage.push(swap.top());
		swap.pop();
	}
}

	void pop(){ storage.pop();} //O(1);
	 const T& front() const { return storage.top();}
	  T& front()  { return storage.top();}
	  bool empty() const {return storage.empty();}
	  int getSize() const {return storage.getSize();}


void print() const {
		storage.print();
	}

};

int main (void){
	Queue<int> q;
	for (int i=0; i<5; i++)
		q.push(i*2);
	//Queue<int> p(q);
	
	cout << " Elementos q: " << q.getSize() << endl;
	q.print();
}