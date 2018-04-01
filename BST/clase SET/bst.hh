#ifndef __BST_HH__
#define __BST_HH__

#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include <algorithm>
#include <functional>
#include "Queue.hh"

using namespace std;

template <typename T>
class BST {
 private:
  class Node{
  private:
    T data;
    Node *left;
    Node *right;
    
  public:
    Node (T d){
      left=nullptr;
      right=nullptr;
      data=d;
    }

    const T& getData () const { return data; }
    T& getData (){ return data ;}
    

    Node * getLeft (){ return left;}   //retorna la direccion del hijo izquerdo
    Node * getRight (){ return right;}  //retorna la direccion del hijo derecho

    bool hasLeft () { return left != nullptr;} //verifica si existe hijo izquierdo
    bool hasRight () { return right != nullptr;}// verifica si existe hijo derecho

    void setLeft (Node *n) { left = n;}
    void setRight (Node *n){ right = n;}

    void setData (T elem){ data=elem;}

  };

  Node *root; // es el pade del arbol
  size_t size;

  void insert (Node *n, T elem){ 
    if(elem == n -> getData() ) { return;} // si es igual simplemente no se va retornar
    if(elem < n -> getData()){

      if(!n -> hasLeft()){ // si no existe nodo  izquierdo colocarle un hijo a el nodo
        Node *k = new Node(elem);
        n->setLeft(k);
        size++;
      }else {
        insert(n->getLeft(), elem);// si tiene hijo, ya evaluar los arboles del nodo para ver donde iria elem
      }

    }else if(n -> getData() < elem){

      if(!n -> hasRight()){ //si no existe nodo derecho colocarle un hijo al nodo
        Node *k = new Node(elem);
        n -> setRight(k);
        size++;
      }else {
        insert(n -> getRight(), elem); // si tiene hijo, ya evaluar los arboles del nodo para ver donde iria elem
      }
    }

  }  //complejidad O(h) siendo h los niveles del arbol.


   void print(Node* n, size_t& nullnodes) const {

    if (n->hasLeft()) {
      cout << n->getData() << " -> " << n->getLeft()->getData() << ";" << endl;
      print(n->getLeft(), nullnodes);
    } else
      printNullNode(n->getData(), nullnodes++);

    if (n->hasRight()) {
      cout << n->getData() << " -> " << n->getRight()->getData() << ";" << endl;
      print(n->getRight(), nullnodes);
    } else
      printNullNode(n->getData(), nullnodes++);
  }

  void printNullNode(T data, size_t nullnodes) const {

    cout << "null" << nullnodes << " [shape=point];" << endl;
    cout << data << " -> null" << nullnodes << ";" << endl;
  }

  

public:

  BST (): root(nullptr) , size(0) {}

  BST (const BST<T> &other){
    root=nullptr;
    size=0;
    other.preorder([&](T n){ insert(n);});
  }

  void insert (T elem){  //inserta un elemento al arbol, complejidad O(h)
    if(empty()){
      Node *n= new Node(elem);
      root = n;
      size++;
    
    }else { insert (root , elem);} //parte privada
  }

/**
   * Outputs a textual representation of the BST.
   *
   * To visualize it, visit:
   * http://www.webgraphviz.com/
   * Visit http://sandbox.kidstrythisathome.com/erdos/
   */
  void print() const { //complejidad O(size)

    cout << "digraph BST {" << endl;
    if (empty())
      cout << endl;
    else if (!root->hasLeft() && !root->hasRight())
      cout << root->getData() << endl;
    else {
      size_t nullnodes = 0; 
      print(root, nullnodes); // parte privada
    }
    cout << "};" << endl;
  }
//----------------------------------------------------------------
  int height() const{  //complejidad lineal
  if(empty()) return 0;
  else return height(root); // parte privada
}

private:
  int height(Node *n) const{
  if (!n->hasLeft() && !n->hasRight()) return 1;
  int lh =0, rh =0;
  if(n->hasLeft()) lh=height(n->getLeft());
  if(n->hasRight()) rh=height(n->getRight());
  return 1 + max(lh,rh); //pertene a la libreria algorithm 
}

//---------------------------------------------------------------------------------
public:
  size_t getSize() const { return size; }
  bool empty () const { return root==nullptr; }

bool search (T elem ) const {
  return search(root, elem);
}

private:

bool search (Node *n, T elem) const {  // complejidad O(h)
  if (n==nullptr) return false;
  if(n -> getData()== elem) { return true;}
  if(elem < n -> getData()) { return search(n->getLeft() , elem );} 
  else { return search(n-> getRight() , elem);}
}


//--------------------------------------------------------------------------------------------------------
  public:

   using F = function <void(T)> ;//atributo para poder llamar una funcion dentro de otra funcion

  void inorder( F f ){
   if(empty()){ return;}
    inorder(root, f );
  }

  void preorder( F f ){
   if(empty()){ return;}
    preorder(root , f);
  }

  void posorder( F f ){
    if(empty()){ return;}
    posorder(root , f);
  }

   void levelOrder (F f){
    if(empty()){ return;}
    Queue<Node *> c;
    c.push(root);
    while(c.getSize()!=0){
      f(c.front() -> getData());
      if(c.front() -> hasLeft()){  c.push(c.front()->getLeft());  }
      if(c.front() -> hasRight()){ c.push(c.front()->getRight()); }
      c.pop();
    }
  }

//-------------------------------------------------------------------

  void inorder( F f ) const{
   if(empty()){ return;}
    inorder(root, f );
  }

  void preorder( F f )const {
   if(empty()){ return;}
    preorder(root , f);
  }

  void posorder( F f )const{
    if(empty()){ return;}
    posorder(root , f);
  }

   void levelOrder (F f)const{
    if(empty()){ return;}
    Queue<Node *> c;
    c.push(root);
    while(c.getSize()!=0){
      f(c.front() -> getData());
      if(c.front() -> hasLeft()){  c.push(c.front()->getLeft());  }
      if(c.front() -> hasRight()){ c.push(c.front()->getRight()); }
      c.pop();
    }
  }

private:
//complejidad O(size)
  void inorder(Node *n, F f ){
    if(n != nullptr){
      inorder(n -> getLeft(), f);
      f( n-> getData());
      inorder(n -> getRight(), f);
    }
  }

  void preorder(Node *n, F f){
    if(n != nullptr){
      f( n-> getData());
      preorder(n -> getLeft() , f);
      preorder(n -> getRight() , f);
    }
  }

  void posorder(Node *n, F f){
    if(n != nullptr){
      posorder(n -> getLeft(), f);
      posorder(n -> getRight(), f);
      f( n-> getData());
    }
  }
  //------------------------------------------------------------------

   void inorder(Node *n, F f )const{
    if(n != nullptr){
      inorder(n -> getLeft(), f);
      f( n-> getData());
      inorder(n -> getRight(), f);
    }
  }

  void preorder(Node *n, F f)const{
    if(n != nullptr){
      f( n-> getData());
      preorder(n -> getLeft() , f);
      preorder(n -> getRight() , f);
    }
  }

  void posorder(Node *n, F f)const{
    if(n != nullptr){
      posorder(n -> getLeft(), f);
      posorder(n -> getRight(), f);
      f( n-> getData());
    }
  }
  


//--------------------------------------------------------------------------------------

public:
//encuentra eel maximo y el minimo en un arbol de busqueda binaria
  T findMax () const { //Compejidad O(size)
    assert(! empty());
    return findMax(root)->getData();
  }

  T findMin () const {  //compleidad O(Size)
    assert(! empty());
    return findMin(root)->getData();
  }

private:

  Node *findMax(Node *n) const{
    if(n->hasRight()){
      return findMax(n->getRight());
    }
    else { return n;}
  }

  Node *findMin(Node *n) const{
    if(n->hasLeft()){
      return findMin(n->getLeft());
    }
    else { return n;}
  } 
//---------------------------------------------------------
public:
//vacia un arbol de busqueda binaria 
  //complejidad O(size)
  void clear (){
    if(empty()) return;
    clear(root);
    size=0;
    root=nullptr;
  }

private:

  void clear(Node *n){
    if (n -> hasLeft())
      clear(n->getLeft());
    if(n->hasRight())
      clear(n->getRight());
      delete n;
  }
//------------------------------------------------------------------

public:

  ~BST(){ clear();}

  void remove (T elem){
    if(empty()) return;
    root=remove(root,elem);
  }

 private:

 Node* remove(Node *n, T elem){
  if(elem < n-> getData()) { n -> setLeft(remove(n->getLeft(), elem)); return n; }
  if(n -> getData() < elem) { n -> setRight(remove(n ->getRight(), elem)); return n;}
  else {// n->getData()== elem
    if(!n->hasLeft() && !n->hasRight()){
      delete n;
      size--;
      return nullptr;
    }
    if(!n->hasLeft()){//solo tiene hijo derecho
      Node *tmp =n->getRight();
      delete n;
      size--;
      return tmp;
    }
    if(!n->hasRight()){//solo tiene hijo izquierdo
      Node *tmp =n->getLeft();
      delete n;
      size--;
      return tmp;
    }
    //tiene dos hijos
    Node *m = findMax( n->getLeft());
    T tmp= n->getData();
    n->setData(m->getData()); //pongo el elemento a borrar en una hoja
    m->setData(tmp);
    n->setLeft(remove(n->getLeft(), elem));


  }
 } 

};


#endif