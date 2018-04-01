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
#include <limits>
#include "priorityqueue.hh"
#include "disjoint_set.hh"
#include "heapmin.hh"
#include <random>
//#include "queuePriority.hh"

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
          else w = 1;
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
  void addEdge(const V& src, const V& tgt, const W& w = 1) {
    assert(nodeExists(src));
    assert(nodeExists(tgt));//hasta este punto verifico que existan los dos nodos
    if (!edgeExists(src, tgt)) {//si no existe el arco lo agrego
      adj[src].push_back(tgt);
      weights[{src, tgt}] = w;// weights.insert({{src,tgt},w});
                                                                                            }
  }
  const unordered_set<V> getNodes() const { return nodes; } //retorna los nodos que existen en el grafo
  /// Returns the nodes whi#include <unordered_map>

  const NodeList& getAdjacentTo(const V& n) const { // con que nodos esta conectado un nodo en particular
    assert(nodeExists(n));
    return adj.find(n)->second;// *{bool,list(V)} //bool si esta y list(v) tipo del dato del value
  }
   unordered_map<pair<V,V>,W, WeightHash<V>, EdgeEqual<V>> getEdges() const{
    return weights;
  }

   W getWeight(const V& p, const V& s) {
    return weights[{p,s}];
  }


  /*convierte un grafo dirigo
	en uno no dirigido
	si es no dirigido no hace nada
  */
  void ConverToNotDirected (){// O(|E|) 
	if(weights.size()==0) return;
  unordered_map<pair<V, V>, W, WeightHash<V>, EdgeEqual<V>> temporalW;
	for(const pair<pair<V,V>,W> &m : weights){//O(|E|)
		V p= m.first.first;
		V s= m.first.second;
		W x=m.second;
		if(!edgeExists(s,p)){ 
      adj[s].push_back(p);
      temporalW[{s,p}]=weights[{p,s}];
    }
	}
  for(const pair<pair<V,V>,W> &m:temporalW ){//O(|E|)
    weights.insert(m);
  }
}


  void ConverToNotDirected2 (){// O(|V||E|) 
  if(weights.size()==0) return;
  for(const V &p: getNodes()){
    for(const V& s: adj[p]){
      if(!edgeExists(s,p)){ addEdge(s,p,weights[{p,s}]);}
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

  int OutDegree(){
    int res = 0;
    for( const V& n : getNodes()){
      res += adj[n].size();
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

  int inDegree3(){//O(2|V|+|E|*|V|)
    unordered_map<V,int> inDegreeVertex;
    for(const V& n: getNodes()){//O(|V|)
      inDegreeVertex[n]=0;
    }
    for(const V& n:getNodes()){//O(|V|)
      for(const V& v:adj[n]){//O(|E|)
        inDegreeVertex[v]+=1;
      }
    }
    int res=0;
    for(const V& n:getNodes()){//O(|V|)
      res+=inDegreeVertex[n];
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
void findComponents(const unordered_map< V, bool>& visited, unordered_map<V , int> &components, int &c , pair<int,int> &n){
  int x=0;
	for(const pair<V,bool> & v: visited){// recorremos la lista de visitados
		if(components[v.first] == 0 && v.second){ //si el elemento no esta en alguna componente conexa y ya fue visitado
			components[v.first]=c; //agregarlo a la componente conexa c
      x++;
			//components.insert({v.first, c});
		}
	}
  if(n.second < x){
    n.second = x;
    n.first = c;
  }
  
}

template <typename V, typename W>
unordered_map< V , int> connectedComponents (const AdjList<V,W> &g,   pair<int,int> &cb , int &i = 1){
	unordered_map< V,int> components; //donde va asociar cada componente a la componenete conexa que pertenece
	unordered_map< V, bool> visited; //donde va ir visitando los nodos por medio del BFS volviendo positivos los ya visitados
	for(const V &v: g.getNodes()){components[v]= 0;  visited[v] = false;} //inicializao las tablas
	//int i = 1;//el valor de la primera componente conexa
	while(moreToVisit(visited)){
		V n = ChooseNext(visited);
		dfs(g, n ,visited);
		findComponents(visited, components, i , cb);
    //cout << i << endl;
		i++;

	}
	i--;
	return components;
}



template <typename V, typename W>
void dijkstra(  AdjList<V,W> &g,unordered_map<V,W> &distancias ,
              unordered_map<V,V> &padre , unordered_map<V,bool> &visited , const V& start ){
  for(const V& n: g.getNodes()){
    padre[n] = n;
    distancias[n] = numeric_limits<int>::max();
    visited[n]=false;
  }
  PriorityQueue<V> q;
  distancias[start]=0;
  q.push(distancias[start],start);
  while(!q.empty()){
    V n = q.front();//O(|V|*log2(|V|)
    q.pop();

    if(!visited[n]){
      visited[n] = true; //encontre un camino desde el inicio hasta n
      //cout << g.getAdjacentTo(n).size()<< endl;
      for(const V& i: g.getAdjacentTo(n)){//O(|E|)
        if(!visited[i]){
        W dist = distancias[n] + g.getWeight(n,i);  //O(|V|*log2(|V|))
          if(distancias[i] > dist){
            distancias[i] = dist;
            padre[i]= n;
            q.push(distancias[i],i);
          }  
        }
      }
    }
  }
}

//O(|V|+|V|*log2(|V|+|E|+|V|*log2(|V|))=O(|V|+2|V|*log2(|V|)+|E|) =O(|V|+|E|+|V|*log2(|V|))

template <typename V, typename W>
void dijkstraDiameter( AdjList<V,W> &g,unordered_map<V,W> distancias ,
              unordered_map<V,V> padre , unordered_map<V,bool> visited , const V& start,
               W* HeavierRoad ){
  /*for(const V& n: g.getNodes()){
    padre[n] = n;
    distancias[n] = numeric_limits<int>::max();
    visited[n]=false;
  }*/
  PriorityQueue<V> q;
  distancias[start]=0;
  q.push(distancias[start],start);
  while(!q.empty()){
    V n = q.front();//O(|V|*log2(|V|)
    q.pop();

    if(!visited[n]){
      visited[n] = true; //encontre un camino desde el inicio hasta n
      if(*HeavierRoad < distancias[n]){
        *HeavierRoad  = distancias[n];
      }
      //cout << g.getAdjacentTo(n).size()<< endl;
      for(const V& i: g.getAdjacentTo(n)){//O(|E|)
        if(!visited[i]){
        W dist = distancias[n] + g.getWeight(n,i);  //O(|V|*log2(|V|))
          if(distancias[i] > dist){
            distancias[i] = dist;
            padre[i]= n;
            q.push(distancias[i],i);
          }  
        }
      }
    }
  }
}


template<typename V,typename W>
W Diameter( AdjList<V,W>& g, const int &BiggerCc , unordered_map< V , int>& ComponentC ){
  unordered_map<V,bool> visited;
  unordered_map<V,int> distancias;
  unordered_map<V,int> padre;
  //tabla int y int

  for(const V& n: g.getNodes()){
    if(ComponentC[n] == BiggerCc){
      padre[n] = n;
      distancias[n] = numeric_limits<int>::max();
      visited[n]=false;
    }
  }
    //for de las componentes conexas
  W Diam = W();
  for(const V& i : g.getNodes()){//O(|V|)
    if(ComponentC[i] == BiggerCc)
      dijkstraDiameter(g,distancias,padre,visited,i,&Diam); 
  }
  return Diam;
}


template<typename V,typename W>
W Diameter( AdjList<V,W>& g, const int &BiggerCc , unordered_map< V , int>& ComponentC ){
  unordered_map<V,bool> visited;
  unordered_map<V,int> distancias;
  unordered_map<V,int> padre;
  //tabla int y int

  for(const V& n: g.getNodes()){
    if(ComponentC[n] == BiggerCc){
      padre[n] = n;
      distancias[n] = numeric_limits<int>::max();
      visited[n]=false;
    }
  }
    //for de las componentes conexas
  W Diam = W();
  for(const V& i : g.getNodes()){//O(|V|)
    if(ComponentC[i] == BiggerCc)
      dijkstraDiameter(g,distancias,padre,visited,i,&Diam); 
  }
  return Diam;
}

  template<typename V,typename W>
unordered_set< pair<V,V> , WeightHash<V>, EdgeEqual<V>> prim( AdjList<V,W>& g, const V& start, unordered_map<V,bool>& visited,
                                                                 unordered_map<V,int>& dist, unordered_map<V,V>& prev){
     for(const V& i : g.getNodes()){
     visited[i]= false;
     dist[i]=std::numeric_limits<int>::max();
     prev[i]=i;
     }
     unordered_set< pair<V,V>, WeightHash<V>, EdgeEqual<V>> mst;
     dist[start]=0;
     PriorityQueue<V> q;
     q.push(dist[start],start);
     while(!q.empty()){
        V u = q.front();  //O(|v|log|v|)
         q.pop();
         visited[u]= true;
         if(prev[u]!=u){ //O(1)
          mst.insert({prev[u],u});
         }
         for(const V& i : g.getAdjacentTo(u)){ //O(|E|)
             if(visited[i] == false){
            if( g.getWeight(u,i) < dist[i]){
                     dist[i]= g.getWeight(u,i);
                     prev[i]= u ;
                     q.push(dist[i],i); //O(|v|log|v|)
                 }
             }
         }
     }
     return mst;
} // O(|v|log|v|) + o|E| + O(|v|log|v|) + o(|E|) = O(|E| + |V|log|V|)


template<typename V,typename W>
 void MstKruskal( AdjList<V,W>& g, const unordered_map<pair<V,V>,W, WeightHash<V>, EdgeEqual<V>> &weights
                                         ,unordered_set< pair<V,V>, WeightHash<V>, EdgeEqual<V>> &mst
                                          , unordered_map< V , int>& ComponentC , const int& MaxComponetC){
  DisjointSet<V> forest;
  for(const V& v: g.getNodes()){
    if(ComponentC[v] == MaxComponetC){
      forest.MakeSet(v);
    }
  }
  HeapMin<pair<W,pair<V,V>>> q;
  for(const pair<pair<V,V>,W> &e: weights){//O(E*LOG(E))
    V p = e.first.first;
    V s = e.first.second;
    W w = e.second;
    if(ComponentC[p] == MaxComponetC){
      q.insert({w,{p,s}}); 
    }
  }
  while(!q.empty()){
    pair<W,pair<V,V>> n = q.min();//O(|E|*LOG(|E|))
    q.removeMin();
    const V& p = n.second.first;
    const V& s = n.second.second;
    if(forest.FindSet(p) != forest.FindSet(s)){//O(1)
      //pair<W,pair<V,V>>
       mst.insert({p,s});
      forest.Union(p,s);
    }
  }
}

template<typename V,typename W>
 int KargerCut( AdjList<V,W>& g, const unordered_map<pair<V,V>,W, WeightHash<V>, EdgeEqual<V>> &weights
                                          , unordered_map< V , int>& ComponentC , const pair<int,int>& MaxComponetC
                                          ,mt19937 rEngine ,uniform_int_distribution<int> dist ){
  DisjointSet<V> forest;
  for(const V& v: g.getNodes()){
    if(ComponentC[v] == MaxComponetC.first){
      forest.MakeSet(v);
    }
  }
  /*random_device rDevice;
  mt19937 rEngine(rDevice());
  uniform_int_distribution<int> dist;*/
  HeapMin<pair<W,pair<V,V>>> q;
  for(const pair<pair<V,V>,W> &e: weights){//O(E*LOG(E))
    V p = e.first.first;
    V s = e.first.second;
    W w = e.second;
    if(ComponentC[p] == MaxComponetC.first){
      q.insert({dist(rEngine),{p,s}}); 
    }
  }
  int SuperNodes = MaxComponetC.second;
  while(SuperNodes > 2){
    pair<W,pair<V,V>> n = q.min();//O(|E|*LOG(|E|))
    q.removeMin();
    const V& p = n.second.first;
    const V& s = n.second.second;
    if(forest.FindSet(p) != forest.FindSet(s)){//O(|V|)
      forest.Union(p,s);
      SuperNodes--;
  }
}
  int Cut = 0;
  for(const pair<pair<V,V>,W> &e: weights){
    V p = e.first.first;
    V s = e.first.second;
    if(forest.FindSet(p) != forest.FindSet(s)){
      Cut++;
    }
  }
  return Cut;
  
}
template<typename V,typename W>
int MinCut( AdjList<V,W>& g,const unordered_map<pair<V,V>,W, WeightHash<V>, EdgeEqual<V>> &weights
           ,unordered_map< V , int>& ComponentC ,const pair<int,int>& MaxComponetC ){
  int resMincut = numeric_limits<int>::max();
  random_device rDevice;
  mt19937 rEngine(rDevice());
  uniform_int_distribution<int> dist;
  for (int i = 0 ; i < MaxComponetC.second ; i++){
    int n = KargerCut(g,weights,ComponentC , MaxComponetC,rEngine ,dist);
    if(n < resMincut){
      resMincut =n;
    }
    if(resMincut == 1) return resMincut;
  }
  return resMincut;
}


template<typename K,typename V>
bool operator <(const pair<K,pair<V,V>> &lhs , const pair<K,pair<V,V>> &rhs){
  return lhs.first < rhs.first;
}




#endif


//NOTA: poner complejidades
//funcion que elimina un nodo
//outdegre

    //cuando el arbol es no pesado sus pesos serian 0 dentro de la tabla de pesos para dijkstra eso me generaria problemas tener en cuenta
    //posible solucion cuando ingreso el archivo
