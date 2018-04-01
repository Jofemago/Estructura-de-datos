#ifndef __TREAP_HH
#define __TREAP_HH

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <functional>
#include <cassert>

template <typename Key>
class Treap {
private:
  /**
   * @brief Random number generator attributes
   */
  std::random_device rDevice;
  std::mt19937 rEngine;
  std::uniform_int_distribution<int> dist;
  /**
   * @brief Nodes in the treap
   */
  class Node {
  private:
    Key key;
    int priority;
    Node* left;
    Node* right;

  public:
    Node(Key k, int prio)
        : key(k)
        , priority(prio)
        , left(nullptr)
        , right(nullptr) {}
    Key getKey() { return key; }
    int getPriority() const { return priority; }
    bool hasLeft() const { return left != nullptr; }
    void setLeft(Node* newLeft) { left = newLeft; }
    Node* getLeft() { return left; }
    bool hasRight() const { return right != nullptr; }
    void setRight(Node* newRight) { right = newRight; }
    Node* getRight() { return right; }

    std::string toString() const {
      std::stringstream ss;
      ss << "\"" << key << "/" << priority << "\"";
      return ss.str();
    }
  };
  // Attributes
  Node* root;
  int size;

public:
  Treap()
      : rDevice()
      , rEngine(rDevice())
      , dist()
      , root(nullptr)
      , size(0) {}

  bool empty() const { return root == nullptr; }

  int getSize() const { return size(); }

  

  void insert(Key k) { root = insertBST(k, root); }

  void remove(Key k) {
  		root = remove(k, root);
  }

   bool find(Key k){
  	Node* x = find(k, root);
  	if(x == nullptr)
  		return false;
  	return true;
  }


private:
  Node* insertBST(Key k, Node* n) {
    if (n == nullptr) {
      Node* x = new Node(k, dist(rEngine));
      size++;
      return x;
    }
    if (k < n->getKey()) {
      n->setLeft(insertBST(k, n->getLeft()));
      if (n->getLeft()->getPriority() < n->getPriority()) {
        rotateRight(n);
        }
      return n;
    } else if (n->getKey() < k) {
      n->setRight(insertBST(k, n->getRight()));
      if (n->getRight()->getPriority() < n->getPriority()) {
        rotateLeft(n);
        }
      return n;
    } else {
      	if(k == n->getKey())
      		return n;
    }
  }

//remover un elemento del arbol
  Node* remove(Key key, Node *n){
  	if(key < n->getKey()){
  		n->setLeft(remove(key , n->getLeft()));
  	}
  	else if (n -> getKey() < key){
  		n-> setRight(remove(key, n->getRight()));
  	}
  	else if(key == n-> getKey()){
  		if(!n->hasLeft() && !n->hasRight()){
  			delete n;
  			n = nullptr;
  		}
  		else if(!n->hasLeft() && n->hasRight()) {
  			Node* tmp = n->getRight();
  			delete n;
  			n =tmp;
  		}
  		else if(!n->hasRight() && n->hasLeft()){
  			Node* tmp = n->getLeft();
  			delete n;
  			n = tmp;
  		}
  		else if(n->hasLeft() && n->hasRight()){
  			if(n->getRight()->getPriority() < n->getLeft()->getPriority()){
  				rotateRight(n);
  				n->setRight(remove(key, n->getRight()));
  			}else{
  				rotateLeft(n);
  				n->setLeft(remove(key, n->getLeft()));
  			}
  		}
  	}
  	return n;
  }


  Node* find(Key k, Node* n){
  	if(n == nullptr) return nullptr;
  	if(k == n->getKey()) return n;
  	if(k < n->getKey()) return find(k, n->getLeft());
  	else return find(k, n->getRight());
  }

  void rotateLeft(Node*& t) {
    Node* tmp = t;
    t = t->getRight();
    tmp->setRight(t->getLeft());
    t->setLeft(tmp);
  }

  void rotateRight(Node*& t) {
    Node* tmp = t;
    t = t->getLeft();
    tmp->setLeft(t->getRight());
    t->setRight(tmp);
  }

public:
 using F = std::function <void(Key)>;//atributo para poder llamar una funcion dentro de otra funcion

  void inorder( F f ){
    assert(!empty());
    inorder(root, f );
  }

private:
  void inorder(Node *n, F f ){
    if(n != nullptr){
      inorder(n -> getLeft(), f);
      f(n-> getKey());
      inorder(n -> getRight(), f);
    }
  }

public:
  /**
   * Outputs a textual representation of the BST.
   *
   * To visualize it, visit:
   * http://www.webgraphviz.com/
   * Visit http://sandbox.kidstrythisathome.com/erdos/
   */
  void print() const {
    using std::cout;
    using std::endl;

    cout << "digraph Treap {" << endl;
    if (empty())
      cout << endl;
    else if (!root->hasLeft() && !root->hasRight())
      cout << root->getKey() << endl;
    else {
      size_t nullnodes = 0;
      print(root, nullnodes);
    }
    cout << "};" << endl;
  }

private:
  void print(Node* n, size_t& nullnodes) const {
    using std::cout;
    using std::endl;

    if (n->hasLeft()) {
      cout << n->toString() << " -> " << n->getLeft()->toString() << ";"
           << endl;
      print(n->getLeft(), nullnodes);
    } else
      printNullNode(n, nullnodes++);

    if (n->hasRight()) {
      cout << n->toString() << " -> " << n->getRight()->toString() << ";"
           << endl;
      print(n->getRight(), nullnodes);
    } else
      printNullNode(n, nullnodes++);
  }

  void printNullNode(Node* n, size_t nullnodes) const {
    using std::cout;
    using std::endl;

    cout << "null" << nullnodes << " [shape=point];" << endl;
    cout << n->toString() << " -> null" << nullnodes << ";" << endl;
  }
};
#endif