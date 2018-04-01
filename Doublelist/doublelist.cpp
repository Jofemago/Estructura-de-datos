#include <iostream>
#include <cassert> //para generar los mensajes de error

using namespace std;

template <typename T>
class Dblist{
private:

//Creo una clase Nodo que son los que voy a enlazar para 
	class Node{
	private:
		T data;
		Node *next;
		Node *prev;
	public:
		Node (T d){ //O(1)
			data=d;
			next=nullptr;
			prev=nullptr;
		}
		const T &getData() const {return data; } //retorna el valor data de un nodo
    	T &getData() { return data; }// O(1)

    	 Node *getNext() {return next; }//O(1), devuelve la direccion del nodo siguiente
    	 Node *getPrev() {return prev; }//O(1), devuelve la direccion del nodo anterior

    	bool hasNext() {return next != nullptr; } 
    	bool hasPrev() {return prev != nullptr; } 

        void setNext(Node *n) { next = n; } //hace apuntar next de un nodo a una direccion n suministrada
        void setPrev(Node *n) { prev = n; }// hace apuntar prev de un nodo a una dieccion n sumistrada
	};
//-----------------------------------------------------------
	Node *first_;
	Node *last_;
	size_t size_;
	//int size;
public:
	Dblist (){ // constructor de listas vacias , Complejidad O(n)
		first_=nullptr;
		last_=nullptr;
		size_=0;
	}

	//complejidad O(size)
	//crea una lista que es una copia de otra que le otorgamos a la funcion.
	Dblist(Dblist<T> const &other){
		first_= nullptr;
    	last_ = nullptr;
    	size_= 0;
    	Node *x = other.first_;
    	while (x != nullptr) {
      		push_back(x->getData());
      		x = x->getNext();
		}
	}
	//agrega un elemento al final de la lista
	//O(1)
	void push_back(T elem){
		Node *x = new Node(elem);
		if(empty())
			first_=x;
		else{
			last_->setNext(x);
			x->setPrev(last_);
		}
		last_=x;
		size_++;
	}
	//Inserta los elementos por el inicio de la lista
	//O(1)
	void push_front(T elem){
		Node *x = new Node(elem); // haga que n apunte al nuevo elemento que creo en alguna parte de la memoria.
		if(empty())
			last_=x;
		else{
			first_->setPrev(x);
			x->setNext(first_);
		}
		first_=x;
		size_++;
	}
	//complejidad O(1)
	int getSize() const { return size_; }//O(1)

	//Complejidad O(1)
	bool empty() const { return size_==0;}
	//bool empty()  { return size_==0;}

	//complejidad O(1), elimina un elemento del principio de la lista
	void pop_front (){
		assert(!empty());
		Node *n= first_;
		first_=first_->getNext();
		if(first_==nullptr) // esto sucede si la lista solo tiene un elemento entonces entonces la lista quedaria sin elementos para hacer un fist->setprev
			last_=nullptr;
		else first_->setPrev(nullptr); //si la lista tiene mas de un elemento, entonces al nuevo fist su anterior debe ser nullptr
		delete n; //elimino el antiguo first_
		size_--;
	}

	//complejidad O(1), elimina un elemento del final de la lista
	void pop_back(){
		assert(!empty());
		Node *n = last_;
		last_=last_->getPrev();
		if(last_==nullptr)
			first_=nullptr;
		else last_->setNext(nullptr);
		delete n;
		size_--;
	}
	//-------------------------------------
	const T &front() const {
    assert(!empty());
    return first_->getData();
  }

  T &front() {
    assert(!empty());
    return first_->getData();
  }
//------------------------------------
	const T &back() const{
    assert(!empty());
    return last_->getData();
  }

 T &back() {
    assert(!empty());
    return last_->getData();
  }
//-----------------------------------
	//Complejidad O(size_)
	void print(void) const {

    if (empty()) {
      cout << "<>";
    } else {
      Node *t = first_;
      cout << "<";
      while (t != nullptr) {
        cout << " " << t->getData();
        t = t->getNext();
      }
      cout << ">";
    }
    cout << endl;
  }


  
};


int main (){
	Dblist <int> p;
	for (int i=0; i<10 ;i++)
		p.push_front(i);

	Dblist <int> q(p);

	for (int i=0; i<10 ;i++)
	//for (int i=9; i>=0 ;i--)
		p.push_back(i);
 	q.pop_back();
 	q.pop_front();
	q.print();
	p.print();
	cout << p.back() << endl;
}