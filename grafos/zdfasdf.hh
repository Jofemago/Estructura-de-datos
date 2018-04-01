#ifndef __GRAPH_HH__
#define __GRAPH_HH__

#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * @brief Used to hash edges as pair of nodes.
 */
template <typename V>
class WeightHash {
public:
    size_t operator()(const pair<V, V>& key) const {
    return hash<V>()(key.first) ^ (hash<V>()(key.second) << 1);
  }
};
//sacar hash de una pareja de dos cosas de tipo v {V,V}
/**
 * @brief Used to determine when two edges are the same.
 */
template <typename V>
class EdgeEqual {
public:
  bool operator()(const pair<V, V>& lhs,
                  const pair<V, V>& rhs) const {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }
};// cuando dos parejas son iguales

template <typename V, typename W>
class AdjList {
public:
  // NodeList is the type used for a list of nodes
  using NodeList = list<V>; //nodos son tipo V

private:
  // Adjacency list
  unordered_map<V, NodeList> adj;

  // Set of nodes
  unordered_set<V> nodes;
  // Weigth storage
  unordered_map<pair<V, V>, W, WeightHash<V>, EdgeEqual<V>> weights;

public:
  AdjList()
      : adj()     // empty hashtable for the adjacency list
      , nodes()   // empty set of nodes
      , weights() // empty hashtable for weights
  {}
  AdjList(const string& fileName, bool weighted = false)
      : adj()
      ,nodes()
      , weights() {
    ifstream is(fileName);
    if (is.good()) {
      string line;
      while (getline(is, line)) {
        stringstream ss(line);
        V src;
        V tgt;
        W w;

        if (line[0] != '#') {
          ss >> src;
          ss >> tgt;
          if (weighted) ss >> w;
          addNode(src);
          addNode(tgt);
          addEdge(src, tgt, w);
        }
      }
    }
  }
  // Returns the number of nodes
  int numNodes() const { return adj.size(); }
  // Returns the number of edges
  int numEdges() const { return weights.size(); }
  // Tests whether node @a n is in the graph.
  bool nodeExists(const V& n) const { return adj.count(n) > 0; }
  // Tests whether the edge (src,tgt) is in the graph
  bool edgeExists(const V& src, const V& tgt) const {
    return weights.count({src, tgt}) > 0;
  }
  // Adds node @a n to the graph
  void addNode(const V& n) {
    if (!nodeExists(n)) {
      adj.insert({n, NodeList()});//se inserta el nodo y se le agrega una lista vacia donde van a ir con quien tiene arcos
      nodes.insert(n);  //lo inserto de una vez en el conjunto de nodos que tengo 
    }
  }
  // Adds the edge (src,tgt) to the graph
  void addEdge(const V& src, const V& tgt, const W& w = W()) {
    assert(nodeExists(src));
    assert(nodeExists(tgt));//hasta este punto verifico que existan los dos nodos
    if (!edgeExists(src, tgt)) {//si no existe el arco lo agrego
      adj[src].push_back(tgt);
      weights[{src, tgt}] = w;// weights.insert({{src,tgt},w});
                                                                     }
  }
  const unordered_set<V> getNodes() const { return nodes; } //retorna los nodos que existen en el grafo
  /// Returns the nodes which are adjacent to @a n
  const NodeList& getAdjacentTo(const V& n) const { // con que nodos esta conectado un nodo en particular
    assert(nodeExists(n));
    return adj.find(n)->second;// *{bool,list(V)} //bool si esta y list(v) tipo del dato del value
  }


  /*convierte un grafo dirigo
	en uno no dirigido
	si es no dirigido no hace nada
  */
  void ConverToNotDirected (){// O(|E|) 
	if(weights.size()==0) return;
	for(const pair<pair<V,V>,W> &m : weights){
		V p= m.first.first;
		V s= m.first.second;
		W x=m.second;
		if(!edgeExists(s,p)){ addEdge(s,p,x);
      //cout<< "addedge" << endl;
    }
	}
}

  int inDegree(){//O(|V|^2)
    int res=0;
    for(const V& v : getNodes()){
        for(const V& n : getNodes()){
          if(v != n && edgeExists(n,v)){
            res++;
          }

        }
    }
    return res/numNodes();
  }

  int inDegree2(){//O(|E|*|V|)
    int res=0;
    for(const V& n:getNodes()){//O(|V|)
      for(const pair<pair<V,V>,W> &e: weights){//O(|E|)
        const V &f= e.first.first;
        const V &s= e.first.second;
        if(f!= n && s == n){res++;}
      }
    }
    return res/numNodes();
  }
};

template <typename V, typename W>
void bfs(const AdjList<V, W>& g, const V& start,
         unordered_map<V, bool>& visited) {
  queue<V> q;
  q.push(start);
  visited[start] = true;
  while (!q.empty()) {
    const V& u = q.front();//O(|v|)
    q.pop();
    for (const V& v : g.getAdjacentTo(u)) {//O(|E|)
      if (!visited[v]) {
        visited[v] = true;
        q.push(v);
      }
    }
  }
}

template <typename V, typename W>
void dfs(const AdjList<V, W>& g, const V& start,
         unordered_map<V, bool>& visited) {
  stack<V> q;
  q.push(start);
  visited[start] = true;
  while (!q.empty()) {
    const V& u = q.top();
    q.pop();
    for (const V& v : g.getAdjacentTo(u)) {
      if (!visited[v]) {
        visited[v] = true;
        q.push(v);
      }
    }
  }
}

template <typename V>
bool moreToVisit (const unordered_map <V,bool> visited){ //O(|V|)
	for(const pair<V, bool> &v: visited){ 
		if(!v.second) return true; //este for va buscando elementos que no se han visitado
	}
	return false;//retorna falso por que no hay mas para visitar
}

template <typename V>
V ChooseNext (const unordered_map <V,bool> visited){ //O(|V|)
	for(const pair<V, bool> &v: visited){ 
		if(!v.second) return v.first; //este for va buscando elementos que no se han visitado
	}
	return V();//un elemento creado por el constructor ya que en nuestro grafo no hay siguiente para visitar
}

template <typename V> //O(|V|)
void findComponents(const unordered_map< V, bool>& visited, unordered_map<V , int> &components, int c){
	for(const pair<V,bool> & v: visited){// recorremos la lista de visitados
		if(components[v.first] == 0 && v.second){ //si el elemento no esta en alguna componente conexa y ya fue visitado
			components[v.first]=c; //agregarlo a la componente conexa c
			//components.insert({v.first, c});
		}
	}
}

template <typename V, typename W>
unordered_map< V , int> connectedComponents (const AdjList<V,W> &g, int &i = 1){
	unordered_map< V,int> components; //donde va asociar cada componente a la componenete conexa que pertenece
	unordered_map< V, bool> visited; //donde va ir visitando los nodos por medio del BFS volviendo positivos los ya visitados
	for(const V &v: g.getNodes()){components[v]= 0;  visited[v] = false;} //inicializao las tablas
	//int i = 1;//el valor de la primera componente conexa
	while(moreToVisit(visited)){
		V n = ChooseNext(visited);
		bfs(g, n ,visited);
		findComponents(visited, components, i);
		i++;
	}
	i--;
	return components;
}



#endif


//NOTA: poner complejidades
//funcion que elimina un nodo
//outdegree ^ indegree