#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cassert>
//#include <iterator>

using namespace std;

int Hash(const int &k){
	return k;
}
int Hash(const string& s) {
  return s.size();
}

const int hashArraySize = 11;

template< typename K, typename V>
class HashTable{
private:
	vector<list<pair<K,V>>> storage_;
	size_t size_;
public:
	HashTable(): storage_(hashArraySize) , size_(0){}
	size_t size() const { return size_;}
	bool empty() const { return size_==0;}

private:
	bool contains (K key)  {
		int p = Hash(key) % storage_.size();
		for( pair<K,V> &i: storage_[p]){
			if(i.first == key){
				//i.second = value;
				return true;
			}
		}
		return false;
	}

	void Rehashing(){
		vector<list<pair<K,V>>> newstorage(storage_.size() * 2 + 1);
		for(list<pair<K,V>> v:storage_){
			for(pair<K,V> i: v){
				int p= Hash(i.first) % newstorage.size();
				newstorage[p].push_back(i);
			}
		}
		storage_=newstorage;
	}
public:
	void insert(K key, V value){
		if(contains(key)) return;
		else if(size_ + 1 >  storage_.size()){Rehashing();}
		
			int p = Hash(key) % storage_.size();
			storage_[p].push_back({key,value});
			size_++;
		
	}

	pair<bool,V> find(K key) const {
		int p = Hash(key) % storage_.size();
		for(  const pair<K,V> &i: storage_[p]){
			if(i.first==key){
				return make_pair(true,i.second);
			}
		}
		return make_pair(false,V());
	}

	V& operator[](K key){
		int p = Hash(key) % storage_.size();
		if(!contains(key)){ insert(key, V());}
		for(pair<K,V> &i : storage_[p]){
			if(i.first==key){
				return i.second;
			}
		}
	}

	void remove(K key){
		int p = Hash(key) % storage_.size();
		int i = 0, m = -1;
		for(pair<K,V> &h : storage_[p]){
			if(h.first == key){
				m= i;
			}else { i=i+1;}
		}
		if(m!=-1){
			storage_[p].erase();
			//storage_[p].erase(--m,m);
			size_--;
		}
	}

};

int main(){
	HashTable<int, int> k;
	k.insert(458,0);
	k.insert(548,0);
	k.insert(7869,0);
	k.insert(24,0);
	k.insert(11,0);
	k.insert(8,0);
	k.insert(9485,0);
	k.insert(125448,0);
	k.insert(54478,0);
	k.insert(2565,0);
	k.insert(54884,0);
	k.insert(4548,0);
	k.insert(11,0);
	k.insert(2565,25);
	cout << k.size() << endl;
	k[11]=8;
	k[17]=5;

	k.remove(7869);
	cout << k.size() << endl;


	
	const pair<bool,int> p = k.find(11);
	const pair<bool,int> m = k.find(17);
	if(p.first){ cout << p.second << endl; }
	if(m.first){ cout << m.second << endl; }
		
}
