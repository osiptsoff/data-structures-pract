#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main() {
	Graph* graph;
	ifstream i("i.txt");
	int choice;

	srand(time(nullptr));

	cout << "1 - input graph from i.txt, else - generate random graph. Your choice: ";
	cin >> choice;
	if (choice == 1)
		graph = new Graph(i);
	else {
		cout << "Graph with N vertices will be generated. Enter N: ";
		cin >> choice;
		graph = new Graph(choice);
	}

	cout << "Graph: \n" << *graph << "\nCycles: \n";
	graph->FindAllCycles();
	delete graph;

	return 0;
}