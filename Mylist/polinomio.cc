#include "list.hh"
#include <iostream>

using namespace std;

class Term {
private:
  int coefficient_;
  int exponent_;

public:
  Term() {}
  /*construye un termino del polinomio*/
  Term(int c, int e) {
    coefficient_ = c;
    exponent_ = e;
  }
  int getCoef() const { return coefficient_; }

  int getExp() const { return exponent_; }
};

ostream &operator<<(ostream &os, const Term &t) {
  os << t.getCoef() << "*x^" << t.getExp();
  return os;
}

class Poly {
private:
  Mylist<Term> poly_;

public:
  Poly() : poly_() {}


/*Complejidad O(2size)*
Agrega un elemento al polinomio donde el elemento anterios es de mayor grado y el siguiente es de menor grado
*/
  void addTerm(int c, int e) { // modificar esta para que cuando iingrese un
                               // grado y lo yubique dnde debe estar
    if(poly_.empty())
       poly_.push_back(Term(c,e));
 else{
     assert(poly_.front().getExp()!=e && poly_.back().getExp() != e);
          if(poly_.front().getExp()<e){
            poly_.push_front(Term(c,e));
          }

          else if(poly_.back().getExp()>e){
             poly_.push_back(Term(c,e));
          }
           else{
                //Mylist<Term> newpoly_;
                Mylist<Term> p(poly_);
                while(!poly_.empty()){//O(size)
                  poly_.pop_front();
                } //vaceamos poly_ para luego llenarlo con el resultado
                int x=0;
                while(!p.empty())  //O(size)
                {

                 if(x==0){
                  //const Term &tp= p.front();

                         const Term &tp=p.front();
                         assert(tp.getExp()!=e);
                         if(tp.getExp()>e){
                          poly_.push_back(tp);
                          p.pop_front();
                         }
                         else{
                          poly_.push_back(Term(c,e));
                          poly_.push_back(tp);
                          p.pop_front();
                          x=1;
                        
                
                         }
                 }

              if(x==1 && !p.empty()){
                const Term &tp=p.front();
                poly_.push_back(Term(tp.getCoef(),tp.getExp()));
                p.pop_front();
              }

                }//while
           }
  }
}

//Complejidad constante
  int size() const { return poly_.getSize(); }
//Complejidad constante, retorna el grado del polinomio
  int degree() const { return poly_.front().getExp(); }

/*Suma dos polinomios
 Complejidad O(elementos de r)
*/
  Poly add(const Poly &other) const {
    Mylist<Term> p(poly_);
    Mylist<Term> q(other.poly_); // para no afectar la lista original creo una
                                 // copia de estas
    Poly r; // creo la variable donde voy a retornar el proceso

    assert(!p.empty() || !q.empty());

    while (!p.empty() && !q.empty()) {
      const Term &tp = p.front();
      const Term &tother = q.front();

      if (tp.getExp() == tother.getExp()) { // si los exponentes son iguales  se
                                            // suman los coeficientes y se
                                            // ingresa con el mismo exponente
        r.addTerm(tp.getCoef() + tother.getCoef(), tp.getExp());
        p.pop_front();
        q.pop_front();
      }

      else if (tp.getExp() > tother.getExp()) {
        r.addTerm(tp.getCoef(), tp.getExp());
        p.pop_front();
      } else {
        r.addTerm(tother.getCoef(), tother.getExp());
        q.pop_front();
      }
    } // while

    while (!p.empty()) {
      r.addTerm(p.front().getCoef(), p.front().getExp());
      p.pop_front();
    }
    while (!q.empty()) {
      r.addTerm(q.front().getCoef(), q.front().getExp());
      q.pop_front();
    }

    return r;
  }


          /*
          Multiplica todo un polinomio ppor un termino
      //complejidad O(2*poly.size())
          */
  Poly mult(const Term &t) const {
    assert(!poly_.empty());
    Mylist<Term> q(poly_); // complejidad O(size)
    Poly r;
    while (!q.empty()) {
      const Term &tq = q.front();
      r.addTerm(t.getCoef() * tq.getCoef(), t.getExp() + tq.getExp());
      q.pop_front();
    }

    return r;
  }
/*Multiplica un polinomio por otro 
Complejidad O(Other.size + size* (r.size+ size))
*/
  Poly mult(const Poly &other) const {
    assert(!poly_.empty() && !other.poly_.empty());
    Mylist<Term> q(other.poly_);
    Poly r;
    while (!q.empty()) {
      const Term &tq = q.front();
	  r = r.add(mult(tq)); // este igual  no fuciona bien luego del primer ciclo
      q.pop_front();
    }
    return r;
  }
//constante
  void PrintfPoly() const { poly_.print(); }
};

int main() {
  cout << "Polinomios" << endl;

  Term x(2, 2);
  Poly p;
 p.addTerm(5,9);
  p.addTerm(2, 7);
  p.addTerm(3,8);
  p.addTerm(4, 5);
  p.addTerm(2, 1);
  p.addTerm(4, 4);
  p.PrintfPoly();
  Poly q;
  q.addTerm(5, 6);
  q.addTerm(7, 3);
  q.PrintfPoly();
  Poly sum=q.add(p);
  sum.PrintfPoly();
  Poly r;
  r = sum.mult(q);
  r.PrintfPoly();

  return 0;
}
