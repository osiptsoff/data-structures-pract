#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main() { // tried input/output. rewrite
	ofstream o;
	ifstream i;

	o.open("o.txt", ios::out);
	i.open("i.txt", ios::in);

	Graph m(i);
	srand(time(nullptr));
	o << Graph(10);
	cout << m;
	return 0;
}