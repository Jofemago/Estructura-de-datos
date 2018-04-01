
#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include <algorithm>
#include <functional>
#include "Queue.hh"
#include <string>
#include <vector>
#include <utility>

using namespace std;

template <typename Key,typename Value>
class BST {
private:
	class Node{
	private:
		Key key_;
		Value value_;
		Node *left;
 		Node *right;
 	public:
 		Node(Key k,Value v){
 			key_=k;
 			value_=v;
 			left=nullptr;
 			right=nullptr;
 		}

 		const Key& getKey() const {return key_;}
 		//Key getKey() const {return key_;}
 		Key& getKey()  {return key_;}

 		const Value& getValue() const {return value_;}
 		Value getValue1()  {return value_;}
 		Value& getValue()  {return value_;}


 		Node *getLeft (){ return left;}   //retorna la direccion del hijo izquerdo
 		Node *getRight (){ return right;}  //retorna la direccion del hijo derecho

 		bool hasLeft () { return left != nullptr;} //verifica si existe hijo izquierdo
 		bool hasRight () { return right != nullptr;}// verifica si existe hijo derecho

 		void setLeft (Node *n) { left = n;}
 		void setRight (Node *n){ right = n;}

 		void setKey(Key k){key_=k;}
 		void setValue(Value v){value_=v;}

 		void setData(Key k, Value v){
 			key_=k;
 			value_=v;
 		}

	};
	Node *root_;
	size_t size_;

public:
	BST():root_(nullptr), size_(0){} //contructor de bst

	//MAKE CONSTRUCTOR COPY
//------------------------------------------------------------------
	void insert(Key key, Value value){	
		if(empty()){
			Node *n= new Node(key, value);
			root_=n;
			size_++;
		}else{ insert(root_,key,value);} //parte privada
	}

private:
//inserta un nodo en el arbol
	//complejidad  O(H)  

	void insert(Node *n,Key key, Value value){
		if(key==n->getKey()){return;}  //si tienen la misma llave no lo ingrese		
		if(n->getKey() < key){
			if(!n->hasRight()){
				Node *p= new Node(key, value);
				n->setRight(p);
				size_++;
			}else {insert(n->getRight(),key,value);}
		}
		else if(key < n->getKey()){
			if(!n->hasLeft()){
				Node *p= new Node(key, value);
				n->setLeft(p);
				size_++;
			}else{insert(n->getLeft(),key,value);}
		}

	}
//---------------------------------------------------------------------
public:

	//consultar la altura de un arbol
	int height() const{  //complejidad lineal
	if(empty()) return 0;
	else return height(root_); // parte privada
}

private:
  int height(Node *n) const{
  if (!n->hasLeft() && !n->hasRight()) return 1;
  int lh =0, rh =0;
  if(n->hasLeft()) lh=height(n->getLeft());
  if(n->hasRight()) rh=height(n->getRight());
  return 1 + max(lh,rh); //pertene a la libreria algorithm 
}
//-------------------------------------------------------------------
public:
//busca un elemto en el mapa y retorna su valor 
//complejidad O(H)
 pair<bool,Value> search (Key elem){
	return search(root_, elem);
}

private:
	pair<bool,Value> search (Node *n ,Key elem){
		if(n==nullptr)  return make_pair(false,Value());
		if(n->getKey()== elem){	return make_pair(true, n->getValue());}
		else if(n->getKey() < elem){return search(n->getRight(), elem);}
		else {return search(n->getLeft(), elem);}
	}
//------------------------------------------------------------------------
 public:
 	using F= function <void(Key,Value)>; //funcion que retorna void y  recibe dos valores

 	void inorder(F func){
 		assert(!empty());
 		inorder(root_,func);
 	}

 	void preorder(F func){
 		assert(!empty());
 		preorder(root_,func);
 	}

 	void posorder(F func){
 		assert(!empty());
 		posorder(root_,func);
 	}

 	void levelOrder(F func){
 		if(empty()) return;
 		Queue<Node *> c;
 		c.push(root_);
 		while(c.getSize()!=0){
 			func(c.front()->getKey(),c.front()->getValue());
 			if(c.front() -> hasLeft()){  c.push(c.front()->getLeft());  }
      		if(c.front() -> hasRight()){ c.push(c.front()->getRight()); }
      		c.pop();
 		}
 	}

 private:

 	void inorder(Node *n, F func){
 		if (n==nullptr) return;
 		inorder(n->getLeft(), func);
 		func(n->getKey(),n->getValue());
 		inorder(n->getRight(), func);
 	}

 	void preorder(Node *n, F func){
 		if (n==nullptr) return;
 		func(n->getKey(),n->getValue());
 		preorder(n->getLeft(), func);
 		preorder(n->getRight(), func);
 	}

 	void posorder(Node *n, F func){
 		if (n==nullptr) return;
 		posorder(n->getLeft(), func);
 		posorder(n->getRight(), func);
 		func(n->getKey(),n->getValue());
 	}
//complejidad de las 4 anteriores O(size)
//--------------------------------------------------------------------
public:
	void clear(){
		if(empty())return;
		clear(root_);
		size_=0;
		root_=nullptr;
	}
private:

	void clear (Node *n){
		if(n->hasLeft()){ clear(n->getLeft());}
		if(n->hasRight()){clear(n->getRight());}
		delete n;
	}//complejidad O(size)
//---------------------------------------------------------------------- 	
public:
	Value findMin () const{
		assert(!empty());
		return findMin(root_)->getValue();
	}

	Value findMax () const{
		assert(!empty());
		return findMax(root_)->getValue();
	}

private:
	Node* findMin(Node *n)const {//O(size) desbalanceado a la izquierda
		if(n->hasLeft()){
			return findMin(n->getLeft());
		}
		else{return n;}
	}

	Node* findMax(Node *n)const {//O(size) arbol desbalanceado a la derecha
		if(n->hasRight()){
			return findMax(n->getRight());
		}
		else{return n;}
	}

//------------------------------------------------------------------------------
public:

	void remove(Key elem){
		if(empty()){ return;}
		root_=remove(root_, elem);
	}

private:

	Node* remove(Node *n, Key elem){
		if(n==nullptr) return nullptr;//no encontro hijo
		if(elem < n-> getKey()) { n -> setLeft(remove(n->getLeft(), elem)); return n; }
 		if(n -> getKey() < elem) { n -> setRight(remove(n ->getRight(), elem)); return n;}
  		else {// n->getKey()== elem
    	if(!n->hasLeft() && !n->hasRight()){
      		delete n;
      		size_--;
      		return nullptr;
    }
    
    	if(!n->hasLeft()){//solo tiene hijo derecho
      		Node *tmp =n->getRight();
      		delete n;
      		size_--;
      		return tmp;
    }
    	if(!n->hasRight()){//solo tiene hijo izquierdo
      		Node *tmp =n->getLeft();
      		delete n;
      		size_--;
      		return tmp;
    }
    //tiene dos hijos
//ERROR
    //debo pasar todo el nodo completo
    	Node *m = findMax( n->getLeft());
    	Key tmp= n->getKey();
    	Value tmp2=n->getValue();
    	n->setData(m->getKey(),m->getValue()); //pongo el elemento a borrar en una hoja
    	m->setData(tmp,tmp2);
    	n->setLeft(remove(n->getLeft(), elem));
    	return n;


  }
 } 

//------------------------------------------------------------------------------------

public:
	~BST(){ clear();}
	bool empty()const { return size_==0;}
	size_t getSize()const { return size_;}

};


int main(void){
	BST<int,string> p;

	p.insert(7,"hola ");
	p.insert(3,"gente ");
	p.insert(17,"del ");
	p.insert(5,"nuevo ");
	p.insert(4,"mundo");
	p.insert(3,"pppp");
	
	/*pair<bool,string> a, b, c, d ,e ;
	a=p.search(7);
	b=p.search(3);
	c=p.search(17);
	d=p.search(5);
	e=p.search(4);

	vector<pair<bool,string> > h;
	h.push_back(a);
	h.push_back(b);
	h.push_back(c);
	h.push_back(d);
	h.push_back(e);

	for(auto i: h){
		if(i.first){
			cout<< i.second;
		}
	}
	cout << endl;

	cout<<p.getSize()<< endl;
	cout << p.height()<<endl;
	//p.clear();

	int sum1=0, sum2=0, sum3=0, sum4=0;
	p.inorder([&](int n, string q){sum1+=n;});
	p.preorder([&](int n, string q){sum2+=n;});
	p.posorder([&](int n, string q){sum3+=n;});
	p.levelOrder([&](int n, string q){sum4+=n;});

	cout<< sum1 << " "<< sum2 << " " << sum3 << " " << sum4 << endl;

	p.inorder([](int n, string q){cout<<q;});
	cout<<endl;
	p.preorder([](int n, string q){cout<<q;});
	cout<<endl;
	p.posorder([](int n, string q){cout<<q;});
	cout<<endl;
	p.levelOrder([](int n,string q){cout<<q;});
	cout<<endl;*/

	//cout << p.findMin()<< p.findMax()<< endl;


	pair<bool,string> a,b;
	a=p.search(7);
	cout << a.first << endl;
	//p.remove(7);
	b=p.search(8);
	cout << b.first << endl;

	p.remove(7);
	pair<bool,string> z = p.search(7);

	if(z.first){
		cout<< z.second << endl;
	}else cout << "false" << endl;
	return 0;
}
