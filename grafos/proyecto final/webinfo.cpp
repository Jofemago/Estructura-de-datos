#include "graph-simple.hh"
#include <iostream>
#include <unordered_map>

using namespace std;
int main() {
/*
  AdjList<int, int> g("web-Google.txt");
  cout << g.numNodes() << endl;
  cout << g.numEdges() << endl;
  g.ConverToNotDirected();
  cout << g.numNodes() << endl;
  cout << g.numEdges() << endl;*/


/*-----------------------------------------------------------------------------------
  AdjList<int, int> m;
  m.addNode(8);
  m.addNode(7);
  m.addNode(6);
  m.addNode(5);
  m.addNode(4);
  m.addNode(3);
  m.addNode(2);
  m.addEdge(8,4);
  m.addEdge(5,6);
  m.addEdge(4,2);
  m.addEdge(3,4);
  m.addEdge(7,5);
  m.addEdge(3,8);
  m.addEdge(6,7);
  m.addEdge(2,7);
  m.addEdge(4,7);
  m.addEdge(8,7);
  m.addEdge(5,8);
  m.addEdge(6,3);
 

  cout << m.numNodes() << endl;
  cout << m.numEdges() << endl;
  m.ConverToNotDirected();
  cout << m.numNodes() << endl;
  cout << m.numEdges() << endl;

  int x=1;
  unordered_map<int, int> p = connectedComponents(m,x);

  
  
    cout << " la cantidad de componentes conexas es: "<< x<< endl;
    cout<< "grado de salida"<< endl;
    cout<<m.inDegree()<< endl;
    cout<<m.inDegree2()<< endl;
    cout<<m.inDegree3()<< endl;*/
//-----------------------------------------------------
  /*unordered_map<int, bool> visited;
  for (const int& v : g.getNodes()) visited[v] = false;
  bfs(g, 0, visited);
  int i = 0;
  for (const auto& v : visited) {
    if (v.second) i++;
  }
  cout << "there are " << i << " elements in the same connected component as 0"
       << endl;*/

  AdjList<int, int> g;
  unordered_map<int,int> distancias;
  unordered_map<int,int> padre;
  unordered_map<int,bool> visited;
  //unordered_map<int,bool> visited;
  /*g.addNode(1);
  g.addNode(0);
  g.addNode(2);
  g.addNode(4);
  g.addNode(3);
  g.addNode(5);
  g.addNode(7);
  g.addNode(6);

  g.addEdge(0,1,1);
  g.addEdge(1,3,5);
  g.addEdge(3,5,8);
  g.addEdge(5,7,9);
  g.addEdge(5,6,8);
  g.addEdge(2,4,6);*/

  //g.addNode(0);
  g.addNode(1);
  g.addNode(2);
  g.addNode(3);
  g.addNode(4);
  g.addNode(5);
  g.addNode(6);
  g.addNode(7);
  g.addNode(8);
  g.addNode(9);
  g.addNode(10);
  g.addNode(11);
  g.addNode(12);
  int z;
  //g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(2,3);
  g.addEdge(4,3);
  g.addEdge(5,6);
  g.addEdge(6,7);
  g.addEdge(7,8);
  g.addEdge(8,9);
  g.addEdge(10,11);
  g.addEdge(11,12);

  //para kruskal
  unordered_map<pair<int,int>,int, WeightHash<int>, EdgeEqual<int>> weight = g.getEdges(); 
  g.ConverToNotDirected();
  


  pair<int,int> n = {1,0};
  int x = 1;
  unordered_map<int, int> CompConect = connectedComponents(g,n, x);
  unordered_map<int,int> diametro= Diameter(g,x,n,CompConect);
  cout << " El diametro de las componenetes conexaas"  << endl;
  cout << " Cc   diametro" << endl;
  for(const pair<int,int> &h : diametro){
    cout << h.first << "  " << h.second << endl;
  }

  cout << " la componente conexa mas grande tiene diametro de " << diametro[n.first] << endl;


  cout << "dijkstra" << endl;
  int m=0;
  dijkstra(g,distancias,padre,visited,3);

  //for(const int & n: visited){
  for(const pair<int,bool> & m: visited){
    const int& n=m.first;
    cout << n<< " " << distancias[n] << " " <<padre[n] << endl;
  }

  cout << "kruskal" << endl;



/*   unordered_set<  pair<int,int>, WeightHash<int>, EdgeEqual<int>> A; 
   MstKruskal(g,weight,A,CompConect,n.first);
   
 for (const pair<int,int> &e: A ){
    const int& a =e.first;
    const int& b =e.second;
    cout << e.first<< " , "<< e.second << " -> "<< g.getWeight(a,b)<< endl;
  }*/
  cout << "KargerCut" << endl;
 cout << MinCut(g,weight,CompConect,n)<< endl;
  

  /* unordered_set < pair<int,int> , WeightHash<int>, EdgeEqual<int> > mst = prim(g,2,visited,distancias,padre);
  for(const pair<int,int> & i : mst )
     cout<< i.first <<" , " << i.second <<" -> "<< g.getWeight(i.first,i.second)<< endl;
*/


 
cout << "outdegree" << g.OutDegree()<< endl;



  //cout << g.getWeight(2,0)<< endl;

cout << Diameter2(g,n.first,CompConect);
  return EXIT_SUCCESS;
}

