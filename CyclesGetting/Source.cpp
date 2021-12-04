#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main() { // tried input/output. rewrite
	ifstream i("i.txt");

	srand(time(nullptr));
	Graph k(10);
	cout << k;
	k.FindAllCycles();
	return 0;
}