#ifndef _LIST_HH_
#define _LIST_HH_

#include <fstream>
#include <cmath>
#include <iostream>
#include <cassert> //para generar los mensajes de error

using namespace std;

template <typename T> class Mylist {
private:
  class Node {
  private:
    T data;
    Node *next;

  public:
    Node(T d) {
      data = d;
      next = nullptr;
    } // constructor de nodos
    const T &getData() const {
      return data;
    } // que valor contiene el nodo constante
    T &getData() { return data; } // que valor contiene el nodo sin ser
                                  // constante
    Node *getNext() {
      return next;
    } // conseguir el nodo al que apunta el nodo acutal
    bool hasNext() {
      return next != nullptr;
    } // si el siguiente nodo existe sera True de lo contrario False
    void setNext(Node *n) { next = n; } // hace que el nodo apunte al nodo n
  };

  Node *first; // primer elemento de la lista
  Node *last; // ultimo elemento de la lista
  int size; // Numero de elementos que contiene la lista

public:
  /*construye una lista vacia
   * complejidad O(1)
   * */
  Mylist() {
    first = nullptr;
    last = nullptr;
    size = 0;
  }

  /*contruye una copia de una lista
  que se le ingresa
  */
  Mylist(Mylist<T> const &other) {
    //cout << "cctor" << endl;
    first = nullptr;
    last = nullptr;
    size = 0;
    Node *x = other.first;
    while (x != nullptr) {
      push_back(x->getData());
      x = x->getNext();
    }
  }

  /*pop_front elimina el primer elemento de la lista
complejidad constante
  */
  void pop_front() {
    assert(!empty()); // valida si la lista esta vacia
    Node *x = first;
    first = first->getNext();
    delete x;
    if (first == nullptr) // si este es null llegamos al final de la lista
      last = nullptr;
    size--;
  }

  /*pop_back  complejidad lineal
  quita un elemento del final
  se debe recorrer todo el arreglo para llegar al anterior que last y cuando se
  esta ahi se elimina el contenido de
  last y se hace que last apunte a ese anterior al que se llego recorriendo toda
  la lista*/
  void pop_back() {
    assert(!empty());
    if (first == last) {
      size--;
      first = nullptr;
      last = nullptr;
      return;
    }
    Node *x = first;
    while (x->getNext() != last)
      x = x->getNext();
    delete last;
    last = x;
    last->setNext(nullptr);
    size--;
  }

  /*valida si la lsita esta vacia
   * complejidad O(1)
   * */
  bool empty() const { return size == 0; } // valida si esta vacia una lista

  /*Inserta el elemento elem al final de la lista
   * complejidad O(1)
   * */
  void push_back(T elem) {

    Node *n = new Node(elem);
    if (empty()) { // si es vacio
      first = n; // el priemro va apuntar al nodo que se creo con el elemento
                 // deseado
    } else {
      last->setNext(n); // hace que el ultimo apunte a nuevo nodo que se ingresa de ultimo
    }
    last = n; // ahora hacemos que last contega la direccion del ultimo
    size++; // como agregamos otro elemento se suma en el size
  }
  /*agrega un elemento al principio de la lista
   * complejidad O(1)
   * */
  void push_front(T elem) { // complejidad constante
    Node *n = new Node(elem);
    if (empty())
      last = n; // si esta vacia hace el ultimo n y el primero n ya que este
                // seria el unico elemento de la list
    else
      n->setNext(first); // le agrego a n toda la cola de la lista
    first = n; // hago first n ya que este se vuelve el primero de la lista y
               // first queda apuntando al segundo.
    size++; // aumento el size pq agregue un elemento nuevo
  }

  /*retorna cuantos elementos tiene la lsita
   * complejidad O(1)
   * */
  int getSize() const { return size; }

  /*imprime en pantalla los elementos de una lista */

  void print(void) const {

    if (empty()) {
      cout << "<>";
    } else {
      Node *t = first;
      cout << "<";
      while (t != nullptr) {
        cout << " " << t->getData();
        t = t->getNext();
      }
      cout << ">";
    }
    cout << endl;
  }
  // muestra el primer elemento de la lista, complejidad constante
  const T &front() const {
    assert(!empty());
    return first->getData();
  }

  T &front() {
    assert(!empty());
    return first->getData();
  }

 const T &back() const{
    assert(!empty());
    return last->getData();
  }

 T &back() {
    assert(!empty());
    return last->getData();
  }

   ~Mylist() {
    while (size != 0)
      pop_front();
  
};
  

#endif
