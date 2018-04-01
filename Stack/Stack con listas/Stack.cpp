
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

int main(){
	Stack<int> t;
	for (int i=0; i<5; i++)
		t.push(rand()%5);
	Stack<int> x(t);
	
	x.print();
	for(int i=0;i<5; i++){
		cout << t.top() << endl;
	t.pop();
	t.print();}
	return 0;

}