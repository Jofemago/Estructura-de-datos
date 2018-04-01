#ifndef _QUEUEPRIORITY_HH_
#define _QUEUEPRIORITY_HH_


#include <iostream>
#include <cassert> //para generar los mensajes de error
//#include <vector>
#include <utility>
#include <string>
#include "heapmin.hh"

template<typename T>
class PriorityQueue{
private:
	HeapMin<pair<int,T>> storage;
public:
	PriorityQueue(): storage() {}

	void push(T elem, int prio){ storage.insert({prio,elem}); }

	void pop(){ storage.removeMin(); }

	T front() const { return storage.min().second;}
	T& front()  { return storage.min().second;}

	int size(){return storage.size();}

};

template<typename K>
bool operator <(const pair<int,K> &lhs , const pair<int,K> &rhs){
	return lhs.first < rhs.first;
}

