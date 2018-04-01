#include <cassert>
#include <string>
#include <iostream>
#include <ctime>
#include <random>
//#include <algorithm>
//#include <functional>


using namespace std;


template <typename T>
class SkipList{
private:

	random_device rd;
    mt19937 gen;
    bernoulli_distribution d;

	class Node{
	private:
		Node *left, *right, *up , *down;
		T data;
	public:
		Node(T elem): left(nullptr) , right(nullptr) , up(nullptr), down(nullptr) , data(elem) {}

		Node* getLeft(){ return left;}
		Node* getRight(){return right;}
		Node* getUp(){ return up;}
		Node* getDown(){return down;}

		const T& getData()const { return data;}
		T& getData(){ return data;}

		bool hasLeft(){return left!=nullptr;}
		bool hasRight(){return right!=nullptr;}
		bool hasUp(){return up!=nullptr;}
		bool hasDown(){return down!=nullptr;}

		void setLeft(Node *l){ left =l;}
		void setRight(Node *r){right =r;}
		void setUp(Node *u){up = u;}
		void setDown(Node *d){down = d;}
		void setData(T elem){data=elem;}
	};

	Node *lastlevel_;// Lh
	Node *firstlevel_;//l0
	size_t size_;	


public:
	SkipList(): lastlevel_(nullptr), firstlevel_(nullptr), size_(0), rd() , gen(rd()) , d(0.5) {}
	size_t size() const { return size_;}
	bool empty() const { return size()== 0;}


//mirar de que forma vamos a insertar
	void insert(T elem){ 
		if(empty()){// si esta totalmente vacio 
			lastlevel_= new Node(elem);
			firstlevel_ = new Node(elem);
			lastlevel_->setDown(firstlevel_);
			firstlevel_->setUp(lastlevel_);
			size_++;
			//crear la base
		}
		else if(elem < lastlevel_->getData()){ // si es menor que la base 
			Node *p = new Node(lastlevel_->getData());
			RepairHead(lastlevel_, elem);
			elemInsert(firstlevel_, p);
			size_++;
			
		}else{ //se debe de insertar en algun lado.
			Node *n= new Node(elem);
			insert(lastlevel_, n );
			
		}
	}

private:
	//Nodo p es el nodo a insertar
	void insert(Node *n, Node *p){
		T x= n->getData();
		T y= p->getData();
		if(x < y){//si el elemento esta a la derecha
			if(n->hasRight())
				insert(n->getRight(), p);
			else if(n->hasDown())
				insert(n->getDown(),p);
			else{
				assert(!n->hasRight() && !n->hasDown()); //estamos en L0
				size_++;
				elemInsert(n ,p); //conecte p a la derecha de n
			}
		}
		else if(y < x){// Si el num a insertar es menor
			if(n->getLeft()->hasDown())
				insert(n->getLeft()->getDown(), p); 
			else{
				assert(!n->getLeft()->hasDown());//estamos en L0
				size_++;
				elemInsert(n->getLeft(),p);
			}
		}
		else return;
	}

	//todos los elementos de la base los cambia con el valor otorgado
	void RepairHead(Node *n, T elem){//O(logn) 
		if(n == nullptr) return;
		n->setData(elem);
		RepairHead(n->getDown(), elem);
	}

	//conecta un nodo i a la dercha de n.
	void elemInsert(Node *n ,Node *i, const bool &ntx = true){
		i->setRight(n->getRight());
		if(n->hasRight()) n->getRight()->setLeft(i);
		n->setRight(i);
		i->setLeft(n);
		//size++;
		NextLevel(i,ntx); //vamos a ver si sube
	}

	void NextLevel(Node *n, const bool &ntx){//LANZAMIENTO DE MONEDA
		if(!ntx) return;
		if(d(gen)){ //lanzamos la moneda
			Node *p = n->getLeft();
			Upper(p , n);
		}
	}

	//conecta un elemnto de ln a ln+1(La lista de arriba)
	void Upper(Node *p, Node *n){
		if(p->hasUp() && p->getData()!= firstlevel_->getData()){// NO ES LA PRIMERA VEZ QUE SUBE
			Node *x= new Node(n->getData());
			x->setDown(n);
			n->setUp(x);
			elemInsert(p->getUp(),x);// con la posibilidad de volver a subir
			return;
		}
		if(p->hasUp() && p->getData() == firstlevel_->getData()){ //aqui miraremos si es la primera vez que sube
			if(p->getUp()== lastlevel_){ //ES LA PRIMERA VEZ QUE SUBE
				Node *x=new Node(lastlevel_->getData());
				lastlevel_->setUp(x);
				x->setDown(lastlevel_);
				lastlevel_=x;//subo a lastlevel una lista mas para insertar uno en la lista vacia.
				Node *z =new Node(n->getData());
				z->setDown(n);
				n->setUp(z);
				elemInsert(p->getUp(),z,false);
				//como esta subiendo por primera vez no sube mas por eso el false
				return;
			}
			else{
				assert(p->getUp()!=lastlevel_);
				assert(p->getUp()->hasRight());
				Node *x = new Node(n->getData());
				x->setDown(n);
				n->setUp(x);
				elemInsert(p->getUp(), x);
				return;
			}
		}
		Upper(p->getLeft(),n);
	}
//disminuir lineas de codigo

public:
	void print(){
		print(lastlevel_);
	}
private:
	void print(Node *n){
		if(n==nullptr) return;
		cout << n->getData()<< " ";
		Node *x = n->getRight();
		while(x != nullptr){
		cout << x->getData() << " ";
		x= x->getRight();	
		}
		cout << endl;
		print(n->getDown());
	}

	//----------------------------------------------
public:
	bool search(const T &elem)const{
		if(empty()) return false;
		search(lastlevel_, elem);
	}
private:
	bool search (Node *n,const T &elem) const{
		const T &m= n->getData();
		if(m < elem){
			if(n->hasRight())
				search(n->getRight(), elem );
			else if(n->hasDown())
				search(n->getDown(), elem);
			else{
				assert(!n->hasRight() && !n->hasDown());
				return false;
			}
		}
		else if(elem < m){
			if(!n->hasLeft()) return false;
			if(n->getLeft()->hasDown())
				search(n->getLeft()->getDown(), elem);
			else{
				assert(!n->getLeft()->hasDown());
				return false;
			}
		}
		else if(elem == m) return true;
	}
//--------------------------------------------------------------
public:
	void remove(const T &elem){
		if(empty()) return;
		remove(lastlevel_ , elem);
	}
private:
	void remove (Node *n,const T &elem){
		const T &m= n->getData();
		if(m < elem){
			if(n->hasRight())
				remove(n->getRight(), elem );
			else if(n->hasDown())
				remove(n->getDown(), elem);
			else{
				assert(!n->hasRight() && !n->hasDown());
				return ; //El elemento no esta
			}
		}
		else if(elem < m){
			if(!n->hasLeft()) return;
			if(n->getLeft()->hasDown())
				remove(n->getLeft()->getDown(), elem);
			else{
				assert(!n->getLeft()->hasDown());
				return ;
			}
		}
		else if(elem == m){
			if(m == firstlevel_->getData()){
				DeleteHead();
			}
			else deleteNode(n);
			size_--;
		}

	}

	void DeleteHead(){
		if(firstlevel_->hasRight()){
			RepairHead(lastlevel_,firstlevel_->getRight()->getData());
			Node *n = firstlevel_->getRight();
			while(n->hasUp()){
				n = n->getUp();
			}
			deleteNode(n);
		}else{
			deleteNode(lastlevel_);
		}
	}

	void deleteNode(Node *n){
		if(n==nullptr) return;
		Node *m = n-> getDown();
		n->getLeft()->setRight(n->getRight());
		if(n->hasRight())
			n->getRight()->setLeft(n->getLeft());
		delete(n);
		deleteNode(m);
	}

};

int main(){
	SkipList<int> sk;
	sk.insert(8);
	sk.insert(4);
	//sk.print();
	sk.insert(5);
	sk.insert(6);
	sk.insert(17);
	sk.insert(45);
	sk.insert(35);
	sk.insert(17);
	sk.insert(3);
	cout<< sk.size()<< endl;
	sk.print();
	//sk.remove(45);
	sk.remove(3);
	cout<< sk.size()<< endl;
	sk.print();

	/*
	cout << sk.search(28) << endl;
	cout << sk.search(18) << endl;
	cout << sk.search(16) << endl;
	cout << sk.search(3) << endl;
	cout << sk.search(45) << endl;*/

	return 0;
}