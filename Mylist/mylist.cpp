#include <iostream>
#include <cassert> //para generar los mensajes de error

using namespace std;

template <typename T>
 class Mylist {
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
  	//cout << "Llama cc" << endl;
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
      delete first;
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
  // complejidad lineal
  /*~Mylist() {
    while (first != nullptr)
      pop_front();
  }*/

  const T &back() const{
    assert(!empty());
    return last->getData();
  }

 T &back() {
    assert(!empty());
    return last->getData();
  }
//Inserta un elemento a la lista en una posicion dada
  // complejidad O(pos-1) lineal
void insert (int pos, T elem){
  assert(pos>0 && pos < size);
  Node *n =new Node(elem);
  Node *x= first;
  Node *z= first->getNext();
  for(int i=0; i < pos - 1 ; i++){
    x=x->getNext();
    z=z->getNext();
  }
  x->setNext(n);
  n->setNext(z);
  size++;
}
//Inserta una lista dentro de otra lista 
//O(pos-1)
void insert (int pos, const Mylist<T> &other){
  assert(pos > 0 && pos < size);
  Mylist<T> p(other);  
  Node *x = first;
  Node *z = first->getNext();
  for(int i=0; i < pos -1; i++){
    x=x->getNext();
    z=z->getNext();
  }
  x->setNext(p.first);
  p.last->setNext(z);
  size=size+p.getSize();

}
//Elimina un elemento de una posicion suminstrada que no este ni al final ni al principio de la lista
//O(pos-1) lineal
void erase (int pos){
  assert(!empty());
  assert(pos > 0 && pos < size -1);
  Node *x=first;
  Node *z=first->getNext()->getNext();
  for (int i=0; i < pos -1; i++){
    x=x->getNext();
    z=z->getNext();
  }
  Node *p = x->getNext();
  x->setNext(z);
  delete p;
  size--;
}
//elimina un rango de elementos de la lista sumistrado por el usuario 
//O(end)
void erase (int start , int end){
  assert(!empty() && start < end);
  if(start==0 && end==size-1){
    while(!empty()) {pop_front();}
    return;
  }
  Node *x = first;
  Node *z= first->getNext()->getNext();
  for(int i=0; i< start-1; i++){
    x=x->getNext();
    z=z->getNext();
  }
  for (int i= start; i < end+1; i++){
    Node *p= x->getNext();
    x->setNext(z);
    if(z!=nullptr){z=z-> getNext();}
    delete p;

    size--;
  }
  if(start==0){
    Node *y=first;
    first=first->getNext();
    size--;
    delete y;
  }

}

//destructor
  ~Mylist() {
    while (size != 0)
      pop_front();
  }


};

int main(void) {
  Mylist<int> q;
  Mylist<int> x;
  for (int i = 0; i < 10; i++)
    q.push_back(i);

  for (int i=5; i >= 0; i--)
    x.push_back(i);
   
   q.insert(2,x);

 x.print();
  q.print();
  
  // q.printf();

}