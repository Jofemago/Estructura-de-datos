#include <iostream>
#include <cassert> //para generar los mensajes de error

using namespace std;

template <typename T> class myvector {
private:
  T *storage; // puntero donde vamos a crear el arreglo incial en el vector
  int size;
  int capacity;

  void resize() { // aumenta el tamaño del arreglo cuando el pushback ha llegado
                  // al limite de este
    int newsize = capacity * (1.5); // tiene un incremento de 1.8
    T *newstorage = new T[newsize];
    for (int i = 0; i < size;i++) { // vacio el arreglo en el otro arreglo de mayor tamaño
      newstorage[i] = storage[i];
    }
    delete[] storage;
    storage = newstorage;
    capacity = newsize;
  }

	//O(n) elementos del vector
  void resize(int n) { // aumenta el tamaño del arreglo cuando el pushback ha llegado
                  // al limite de este
    int newsize = n; // tiene un incremento de 1.8
    T *newstorage = new T[newsize];
    for (int i = 0; i < size; i++) { // vacio el arreglo en el otro arreglo de mayor tamaño
      newstorage[i] = storage[i];
    }
    delete[] storage;
    storage = newstorage;
    capacity = newsize;
  }
	  

public:
  // constuctor 1
  myvector() {
    size = 0;
    capacity = 10;
    storage = new T[capacity];
  }
  // constructor 2
  myvector(int cap) {
    size = 0;
    capacity = cap;
    storage = new T[capacity];
  }

  // metodos o operaciones

  int getsize() const { // constante que no va modificar ningun atributo
    return size;
  }

  bool empty (){
    return size==0;
  }

  void push_back(T elem) { //Constante amortizada
    if (size == capacity)
      resize();
    storage[size] = elem;
    size++;
  }

  void push_front(T elem) {//O(n) n: elementos del vector
    if (size == capacity)
      resize();
    for (int i = size; i > 0; i--)
      storage[i] = storage[i - 1];
    storage[0] = elem;
    size++;
  }

  void pop_back() {   // constante
    assert(size != 0);
    size--;
  }

  void pop_front() {  //O(n) n: elementos del vector
    assert(size != 0);
    for (int i = 1; i < size; i++)
      storage[i - 1] = storage[i];
    size--;
  }

  void push_back(const myvector<T> &other) { //O(n) n: size +|other|
	  if(getsize()+other.getsize() > capacity)
	  
	  resize(getsize()+other.getsize());
	  
    for (int i = 0; i < other.getsize(); i++) {
      push_back(other[i]);
    }
  }

  void push_front(const myvector<T> &other) {
	  if(getsize()+other.getsize() > capacity)
	  resize(getsize()+other.getsize());

/*muevo los elementos del arreglo estorage other.getsize posiciones adelante de la que esta cada uno de ellos*/
  for (int i = getsize() - 1; i >= 0; i--)
    storage[i+other.getsize()]=storage[i];

//agrego los elementos del vector other al principio del storage del vector actual
  for(int i=0;i < other.getsize(); i++)
    storage[i]=other[i];

//modifico el nuevo size
  size=getsize()+other.getsize();
  }

/*INSERTA UN ELEMENTO EN UNA POSICION INDICADA
COMPLEJIDAD ĹINEAL O(size-pos)*/

  void insert (int pos, T elem){
    assert(size!= 0);
    assert(pos>=0 && pos<size);

    if(size == capacity)  resize();

    for (int i = size -1; i >= pos ; i--)
      storage[i+1]=storage[i];
    storage[pos]=elem;
    size++;
  }
/*inserta un vector desde una posicion indicada
  complejidad O(other.size +size - pos)*/
  void insert (int pos,const myvector<T> &other){
    assert(size!= 0);
    assert(pos>=0 && pos<size);

    if(getsize()+other.getsize()>capacity)  resize(getsize()+other.getsize());

    for (int i = size -1; i >= pos ; i--)
      storage[i+other.getsize()]=storage[i];
    
    for(int i=0;i<other.getsize();i++)
      storage[i+pos]=other[i];

    size=getsize()+other.getsize();
  }

  /*Elimina un elemento de una posicion indicada 
  Complejidad O(size-pos)*/
  void erase (int pos){
    assert(pos >= 0 && pos < size);

    for (int i =pos + 1; i < size ; i++)
      storage[i-1]=storage[i];
    size--;
  }
  /*elimina todos los elementos de un rango dado en un vector 
Complejidad O(size-end)
  */
  void erase (int start, int end){
    assert(start<end);
    assert(start >= 0 && end < size);
    int borrar= end - start + 1;
//mueve delete posiciones atras los elements despues de end
    for (int i = end + 1; i < size ; i++)
      storage[i - borrar ] = storage [i];

    size = size - borrar;
  }

  int waste() const {
    return capacity - size;
  } // la capacidad que tengo en capacity
  ~myvector() { delete[] storage; }

  T &at(int pos) {
    assert(pos >= 0 && pos < size); // asegurese que la posicion que le pasan
                                    // esten dentro de los limites del vector
    return storage[pos];
  } // acceder a los elementos

  const T &at(int pos) const {
    assert(pos >= 0 && pos < size); // asegurese que la posicion que le pasan
                                    // esten dentro de los limites del vector
    return storage[pos];
  }

  T operator[](int pos) const { // los corchetes reemplazan el llamado
    // por que en vez de llamar x.at(pos) seria x[]
    return at(pos);
  }
  void mostrar() const {
    for (int i = 0; i < size; i++)
      cout << " " << storage[i];
    cout << endl;
  }

  void quick (){
  	quicksort(0, getsize()-1);
  }

  //void quicksort(int lo, int hi){  }


};



/*void quicksort (myvector<int>& v){
        //ordenar v
}*/

// asi compilo  g++ -Wall -o "helloworld" "helloworld.cc"
// g++ -std=c++11 -o myvector myvector.cpp

int main() {
  myvector<int> x, y;
  for (int i = 1; i < 7; i++) {
    x.push_back(i);
  }

  for (int i = 0; i < 3; i++) {
    y.push_back(i * 2);
  }


y.insert(1,18);
x.insert(2,y);
   y.mostrar();

  x.mostrar();

x.erase(5,8);
y.erase(1);



     y.mostrar();

  x.mostrar();



  return 0;
}
