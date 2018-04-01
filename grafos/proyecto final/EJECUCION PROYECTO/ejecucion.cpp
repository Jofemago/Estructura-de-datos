#include "graph.hh"
#include <iostream>
#include <unordered_map>
#include <ctime>
using namespace std;
  
	void Hora(){
		 time_t tSac = time(NULL); // instante actual
   tm tms = *localtime(&tSac);

   cout << "hh:mm:ss " << tms.tm_hour << ":" << tms.tm_min << ":"
                       << tms.tm_sec << endl;
   cout << "dd-mm-aaaa: " << tms.tm_mday << "-" << tms.tm_mon+1 << "-"
                          << tms.tm_year+1900 << endl;
	}


int main (void){
  cout << "Road network of Texas" << endl;
	cout << "CARGAMOS EL GRAFO"<< endl;
	Hora();
	AdjList<int, int> g("roadNet-TX.txt");
	cout << "El numero de Vertices es: " << g.numNodes() << endl;
	cout << "El numero de Arcos es: " << g.numEdges() << endl;
	cout << endl;
	//------------------------------------------------------------
	/* 
	unordered_map<int,int> distancias;
  unordered_map<int,int> padre;
  unordered_map<int,bool> visited;
  */
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
  	cout <<"El numero que tiene la componente conexa mas grande es: "<< BiggerCc.second << endl;
  	cout << endl;
//---------------------------------------------------------------------------------------------------------------
  	cout << "CALCULAMOS EL DIAMETRO" << endl;
  	Hora();
  	unordered_map<int,int> diametro= Diameter(g,NumCc,BiggerCc,CompConect);
  	cout << " El diametro de las componenetes conexas"  << endl;
  	cout << " Cc     diametro" << endl;
  	for(const pair<int,int> &h : diametro){
    	cout << h.first << "      " << h.second << endl;
  	}

  	cout << " la componente conexa mas grande tiene diametro de " << diametro[BiggerCc.first] << endl;
  	cout << endl;
//-----------------------------------------------------------------------------------------------------------
  	cout << "CALCULAMOS EL KARGER MINCUT " << endl;
  	Hora();
  	cout << "El grado promedio es: " << g.OutDegree() << endl;
  	cout <<" La ruta mas fragil tiene " << MinCut(g,TableEdges,CompConect,BiggerCc) << " caminos alternos" << endl;
  	cout << endl;

  	cout << "FINALIZO" << endl;
  	Hora();


	return EXIT_SUCCESS;
}