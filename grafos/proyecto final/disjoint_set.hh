#ifndef _DISJOINSET_HH_
#define _DISJOINSET_HH_
#include <iostream>

using namespace std;

template<typename T>
class DisjointSet{
private:
	unordered_map<T,T> parent; 
	unordered_map<T,int> rank;

public:

	DisjointSet():parent() , rank() {}

	void MakeSet(const T& elem){
		assert(!parent.count(elem)>0); //que solo este una vez el elemento en la estructura
		parent[elem]=elem;
		rank[elem]=0;
	}

	/*T FindSet(const T& elem){  
		assert(rank.count(elem)>0);
		if(parent[elem]==elem)
			return elem;
		else
			return FindSet(parent[elem]);
	}*/


	T FindSet(const T& x){
		if(x!=parent[x])
			parent[x]=FindSet(parent[x]);
		return parent[x];
	}

	void Union(const T& x, const T& y){
		Link(FindSet(x),FindSet(y));
	}

	bool ExistsSet(const T& elem){
		return rank.count(elem)>0;
	}


	void Link(const T& a, const T& b){ // O(1)
	 	if(rank[b] < rank[a])   //if the rank of b is smaller than a
	 		parent[b]=a;
	 	else if(rank[a]<rank[b]) //if the rank of a is smaller than b
	    	parent[a]=b;
	 	else{
	 		assert(rank[a]==rank[b]);
	    	parent[a]=b; // if both are equal 
        	rank[b]++;
	 	}
	}

 	void print(){ //(size of set)
		for(const pair<T,T>& i : parent)
		cout<< i.first <<" , "<< i.second<<endl;
	} 

};

#endif