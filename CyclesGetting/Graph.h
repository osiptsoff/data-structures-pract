#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using std::endl;
using std::setw;
using std::vector;

template<class T> bool find(const vector<T> &vect, T toFind) {
	for (int vSize = vect.size(), i = 0; i < vSize; ++i)
		if (vect[i] == toFind)
			return true;
	return false;
}

class Graph
{
	static constexpr int maxVertices = 250; // max vertex number gragh can be generated with
	static constexpr int maxMultEdges = 1; // weight cannot be more then this
	static constexpr int zeroChance = 50;    // no edge between two vertices wits zeroChance % possibility

	int vertexCount;
	unsigned char** adjMatrix;

	void GetVertexCycles(int, int, vector<int>&);
public:
	Graph() = delete;
	Graph(const Graph&) = delete;
	Graph(Graph&&) = delete;
	Graph(int);
	Graph(void*) : Graph(rand() % maxVertices) {};
	Graph(std::istream&);
	~Graph() {
		if(adjMatrix != nullptr)
			for (int i = 0; i < vertexCount; ++i) delete[] adjMatrix[i];
		delete[] adjMatrix;
	}

	void FindAllCycles();
	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = delete;

	friend std::ostream& operator<<(std::ostream& oStream, const Graph& graph) {
		if (graph.vertexCount > 250 || &oStream == &std::cout && graph.vertexCount > 25)
			oStream << "Graph is too big\n";
		else {
			int wid = 4;
			oStream << setw(wid) << ' ' << ' ';
			for (int i = 0; i < graph.vertexCount; ++i)
				oStream << setw(wid) << i;
			oStream << endl;
			oStream << setw(wid) << ' ' << ' ';
			for (int i = 0; i < graph.vertexCount; ++i) 
				oStream << setw(wid) << '_';
			oStream << endl;

			for (int i = 0; i < graph.vertexCount; ++i) {
				oStream << setw(wid) << i << '|';
				for (int j = 0; j < graph.vertexCount; ++j)
					oStream << setw(wid) << (int)graph.adjMatrix[i][j];
				oStream << endl;
			}
		}
		return oStream;
	}
};

Graph::Graph(int vertCount) : vertexCount(vertCount), adjMatrix(new unsigned char* [vertCount]) {
	for (int i = 0; i < vertCount; ++i) {
		adjMatrix[i] = new unsigned char[vertCount];
		for (int j = 0; j < vertCount; ++j) adjMatrix[i][j] = (rand() % 100 >= zeroChance) ? rand() % maxMultEdges + 1 : 0;
	}
}

Graph::Graph(std::istream& iStream) : vertexCount(0),  adjMatrix(nullptr) {
	int errorCode = 0;
	int buff;

	iStream >> vertexCount;
	if(iStream.good()) {
		adjMatrix = new unsigned char* [vertexCount];
		for (int i = 0; i < vertexCount; ++i)
			adjMatrix[i] = new unsigned char[vertexCount];

		for (int i = 0; i < vertexCount && !errorCode; ++i)
			for (int j = 0; j < vertexCount && !errorCode; ++j) {
				if (!iStream.eof()) {
					iStream >> buff;
					if (!iStream.bad() && !iStream.fail())
						adjMatrix[i][j] = buff;
					else errorCode = 2; // cannot read next element
				}
				else errorCode = 3; //unexpected EOF
			}
	}
	else errorCode = 1; // cannot read the vertex count

	if (errorCode != 0)
		throw errorCode;
}

void Graph::GetVertexCycles(int start, int current, vector<int>& stack) {
	if (start == current && !stack.empty()) {
		stack.push_back(current);
		for (int size = stack.size(), i = 0; i < size; ++i)
			std::cout << stack[i] << " ";
		std::cout << std::endl;
		stack.pop_back();
		return;
	}

	if(find(stack, current) || current < start)
		return;

	stack.push_back(current);

	for (int i = 0; i < vertexCount; ++i)
		if(adjMatrix[current][i])
			GetVertexCycles(start, i, stack);
	stack.pop_back();
}

void Graph::FindAllCycles() {
	vector<int> stack = {};

	for (int i = 0; i < vertexCount; ++i) {
		GetVertexCycles(i, i, stack);
		stack.clear();
	}
}