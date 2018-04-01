#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include <vector>
#include <utility>
#include <string>
#include "disjoint_set.hh"
#include <random>
using namespace std;

void Hora(){
     time_t tSac = time(NULL); // instante actual
   tm tms = *localtime(&tSac);

   cout << "hh:mm:ss " << tms.tm_hour << ":" << tms.tm_min << ":"
                       << tms.tm_sec << endl;
   cout << "dd-mm-aaaa: " << tms.tm_mday << "-" << tms.tm_mon+1 << "-"
                          << tms.tm_year+1900 << endl;
  }


int main (){
	DisjointSet<int> q;
   for(int i=0;i<16;i++){
   	q.MakeSet(i);
   }
   q.Union(1,0);
   q.Union(3,2);
   q.Union(4,5);
   q.Union(5,6);
   q.Union(4,3);
   q.Union(1,2);
   q.Union(7,8);
   q.Union(9,15);
   q.Union(7,15);
   q.Union(15,3);


   Hora();
  q.print();
  cout<< q.ExistsSet(7) <<endl;

 /*unordered_map<int, int*> x;
  for(int i=0; i < 7 ; i++){
      int m=i;
      int *n = &m;
     x[i]= n;
  }
  int *n =x[3];
  cout << *n << endl;
  x[5]=n;
  for( pair<int,int*> i : x){
    cout<< i.first <<" , "<<*(i.second)<<endl;
   
    }
  
  cout << *x[5]<<endl;*/
    Hora();

    random_device rDevice;
  mt19937 rEngine(rDevice());
  uniform_int_distribution<int> dist;

  cout << endl;
  for(int i = 0 ; i < 10 ; i++){
    cout << dist(rEngine) << " ,";
  }

  random_device mDevice;
  mt19937 mEngine(mDevice());
  uniform_int_distribution<int> aasd;

  cout << endl;
  for(int i = 0 ; i < 10 ; i++){
    cout << dist(rEngine) << " ,";
  }

  cout << endl;
  Hora();


  
}	



