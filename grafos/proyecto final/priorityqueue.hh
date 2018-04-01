#ifndef _PRIORITYQUEUE_HH_
#define _PRIORITYQUEUE_HH_

#include <unordered_map>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include <vector>
#include <utility>
#include <string>

using namespace std;

template <typename T>
class PriorityQueue{
private:
	unordered_map<T,int> positions_; //aca vamos a guarda los elementos de la cola con sus posiciones en el vector que lo estrucutra
	vector<pair<int,T>> storage_;

	int getLeft(int n) const{return 2*n+1;}	 //obtiene la pos del hijo izquierdo
	bool hasLeft(int n) const {return getLeft(n) < size();}  //devuelve si existe hijo izquierdo
	int getRight(int n) const { return 2*n+2;} //obtiene la pos del hijo derecho
	bool hasRight(int n) const { return getRight(n) < size();}//valida si existe hijo derecho
	bool isRoot(int n) const { return n==0;}//valida si la pos ingresada es el root
	int parent (int n)  const { return (n-1)/2;}//devuelve la pos del papa de un nodo

public:
	PriorityQueue(): positions_() , storage_() {}
	//PriorityQueue(const unordered_map<T,int,WeightHash<V>, EdgeEqual<V>> &other): positions_(other) , storage_() {}
	bool empty() const { return storage_.size()==0;}
	int size() const {return storage_.size();}

	void print()  {
		for( const pair<int,T> &a :storage_){
			cout << a.first<<"/"<<a.second << " ";
		}
		cout << endl;
	}

private:

	const T& min() const { assert(!empty()); return storage_[0].second;}
	T& min()  {
	 	assert(!empty());
	  	return storage_[0].second;
	  }

	  /*int ElemPosition (T elem){
	  	assert(positions_.count(elem)>0);//debe existir el elemento 
	  	return positions_[elem]; //retorne en que posicion se encuentra
	  }*/

	 void Swap(int p , int q){
	 	positions_[storage_[p].second] = q;
	 	positions_[storage_[q].second] = p;
	 	swap(storage_[p] , storage_[q]);
	 }

	void insert(int prio , const T& elem){//O(log(n))
		if(positions_.count(elem)>0){ //si existe el elemento en la cola
			if(prio < storage_[positions_[elem]].first ){ //si la prioridad nueva es menor
			storage_[positions_[elem]].first = prio;
			//cout << "chance" << endl;
			heapiFy_up(positions_[elem]);
			}else{									//si la prioridad nueva es mayor 
				assert(storage_[positions_[elem]].first < prio );
				return;
			}
		}else {
		storage_.push_back({prio,elem});
		positions_[elem]=size()-1;
		heapiFy_up(size()-1);
		}
	}

	void heapiFy_up(int q){
		if(!isRoot(q)){
			int p=parent(q);
			if(storage_[q].first < storage_[p].first ){
				Swap(p,q);
				heapiFy_up(p);
			}
		}
	}

	void removeMin(){
		if(empty()) return;
		Swap(0, size()-1);
		positions_.erase(storage_[size()-1].second);
		storage_.pop_back();
		heapiFy_down(0);
	}

	void heapiFy_down(int q){
		if(empty()) return;
		if(!hasRight(q) && !hasLeft(q)) return;
		if(hasRight(q) && hasLeft(q)){
			int right = getRight(q);
			int left = getLeft(q);
			if(storage_[right].first < storage_[left].first){
				if(storage_[right].first < storage_[q].first){
					Swap(q , right);
					heapiFy_down(right);
				}
			}else{
				if(storage_[left].first < storage_[q].first){
					Swap(q, left);
					heapiFy_down(left);
				}
			}
		}
		else if(hasLeft(q) && !hasRight(q)){
			//int right = getRight(q);
			int left = getLeft(q);
			if(storage_[left].first < storage_[q].first){
				Swap(q, left);
			}
		}
	}

	public:
		void push(int prio, const T& elem){ insert(prio ,elem); }
		void pop(){ removeMin(); }
		const T& front() const { return min();}
		T front()  { return min();}

};


#endif