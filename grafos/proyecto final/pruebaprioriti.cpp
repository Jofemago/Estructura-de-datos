#include <unordered_map>
#include <iostream>
#include <cassert> //para generar los mensajes de error
#include <vector>
#include <utility>
#include <string>
#include "priorityqueue.hh"

using namespace std;

int main(){
	PriorityQueue<char> v;
	v.push(8,'a');
	v.push(6,'b');
	v.push(5,'c');
	v.push(17,'d');
	v.push(34,'e');
	v.push(15,'f');
	v.pop();
	v.print();

}