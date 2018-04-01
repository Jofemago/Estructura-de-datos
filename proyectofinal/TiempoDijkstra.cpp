#include "graph.hh"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <random>
#include <ctime>
#include <cmath>


using namespace std;

void Hora(){
		 time_t tSac = time(NULL); // instante actual
   tm tms = *localtime(&tSac);

   cout << "hh:mm:ss " << tms.tm_hour << ":" << tms.tm_min << ":"
                       << tms.tm_sec << endl;
   cout << "dd-mm-aaaa: " << tms.tm_mday << "-" << tms.tm_mon+1 << "-"
                          << tms.tm_year+1900 << endl;
	}

int ObtenerNodo(const unordered_set<int> &NC,const int &pos){
	int it = 0;
	assert(pos < NC.size());
		for( const int& h : NC){
			if(it == pos){
				return h;
			}
			it ++;
		}
}

int main (){
	random_device rDevice;
	mt19937 rEngine(rDevice());
	uniform_int_distribution<int> dist;
	cout << "TODO USA"<< endl;
	AdjList<int, int> g("USA-road-d.USA.gr",true);
	cout << "El numero de Vertices es: " << g.numNodes() << endl;
	cout << "El numero de Arcos es: " << g.numEdges() << endl;
	cout << endl;
	//------------------------------------------------------------
  	//Se escoge en este momento para disminuir la complejidad de kruskal y kargerMincut
  	unordered_map<pair<int,int>,int, WeightHash<int>, EdgeEqual<int>> TableEdges = g.getEdges();

  	cout << "CONVERTIMOS EL GRAFO A NO DIRIGIDO"<< endl;
  	Hora();
  	g.ConverToNotDirected();

  	cout << endl;
 //---------------------------------------------------------------------------------------------------------------
  	cout << "CALCULAMOS LAS COMPONENTES CONEXAS" << endl;
  	Hora();
  	pair<int,int> BiggerCc = {1,0};//pareja de la componente conexa mas grande y su numero de elementos
  	int NumCc = 1;
  	unordered_map<int, int> CompConect = connectedComponents(g,BiggerCc,NumCc);
  	cout <<"El numero de componentes conexas es: "<< NumCc << endl;
  	cout <<"El numero de elementos que tiene la componente conexa mas grande es: "<< BiggerCc.second << endl;
  	cout << endl;


	cout << "EL GRADO PROMEDIO ES: " << g.OutDegree() << endl;	
//TIEMPO PROMEDIO DE DIJKSTRA
 //------------------------------------------------------------------------------------------------------------
	unordered_map<int,int> distancias;
  	unordered_map<int,int> padre;
  	unordered_map<int,bool> visited;
  	unordered_set<int> NodesComponentC;
  	int b =0;

  	for(const int& n: g.getNodes()){
    	if(CompConect[n] == BiggerCc.first){
    		NodesComponentC.insert(n);
			padre[n] = n;
      		distancias[n] = numeric_limits<int>::max();
      		visited[n]=false;
    }
  }
  	clock_t	result = 0;
	int elements = 30;//numero de elementos con los que queremos scar la medida
	for(int i = 0 ; i < elements ; i++){
		int pos = dist(rEngine) % NodesComponentC.size();//del numero generado me devuelve un numero entre 0 - numnodes - 1
		//cantidad de componentes de la CC mas grande
		int NODO = ObtenerNodo(NodesComponentC,pos);
		clock_t t=clock();
		dijkstraDiameter(g,distancias,padre,visited,NODO,&b);
		t=clock() - t ;
		result += t;
	}
	result = result / elements;
	cout <<"El tiempo promedio de Dijkstra sobre un nodo es: "<< (result/CLOCKS_PER_SEC) << " segundos" << endl;
	cout <<"El tiempo del diametro sobre la componente es en promedio: " << ((result/CLOCKS_PER_SEC)) * NodesComponentC.size() << endl;
//---------------------------------------------------------------------------------------------------------------
//TIEMPO PROMEDIO DE EJECUCION DE KRUSKAL
	random_device rD;
  mt19937 rE(rD());
  uniform_int_distribution<int> ale;

  clock_t result2 = 0;
  int veces = 30;
  for(int i = 0; i < veces ; i++){
	clock_t t=clock();
	int n = KargerCut(g,TableEdges,CompConect , BiggerCc,rE ,ale);
	t=clock() - t ;
	result2 += t;
  }
  result2 = result2 / veces;
  cout <<"El tiempo promedio de KRUSKAL sobre un grafo o Componente C es: "<< (result2/CLOCKS_PER_SEC) << " segundos" << endl;
  cout <<"El tiempo del KARGERMINCUT sobre la componente es en promedio: " << ((result2/CLOCKS_PER_SEC)) * pow(BiggerCc.second,2) << endl;
}



