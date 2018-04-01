#ifndef _QUEUE_HH_
#define _QUEUE_HH_

#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include "Mylist.hh"
using namespace std;

//FIFO first to in firt to out
// los que entran se van acomodando al final y lo que salen son los que entraron de primeros


template <typename T>
class Queue {
private:
	Mylist<T> storage;
public:
	Queue(): storage() {}
	Queue(const Queue<T> &other): storage(other.storage) {} //constructor de copias de storage
	bool empty (){ return storage.empty();} // valida si la cola esta vacia

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

#endif