#pragma once
#include <iostream>
#include <iomanip>

class Graph
{
	static constexpr int maxVertices = 250; // max vertex number gragh can be generated with
	static constexpr int maxMultEdges = 5; // weight cannot be more then this
	static constexpr int zeroChance = 3;    // no edge between two vertices wits 1/zeroChance possibility

	int vertexCount;
	unsigned char** adjMatrix;
public:
	Graph() = delete;
	Graph(const Graph&) = delete;
	Graph(Graph&&) = delete;
	Graph(int vertCount);
	Graph(void*) : Graph(rand() % maxVertices) {};
	Graph(std::istream&);
	~Graph() {
		if(adjMatrix != nullptr)
			for (int i = 0; i < vertexCount; ++i) delete[] adjMatrix[i];
		delete[] adjMatrix;
	}

	void FindCycles(); // to implement
	Graph& operator=(const Graph&) = delete;
	Graph& operator=(Graph&&) = delete;

	friend std::ostream& operator<<(std::ostream& oStream, const Graph& graph) {
		if (graph.vertexCount > 250 || &oStream == &std::cout && graph.vertexCount > 25)
			oStream << "Graph is too big\n";
		else {
			int wid = 4;
			oStream << std::setw(wid) << ' ' << ' ';
			for (int i = 0; i < graph.vertexCount; ++i)
				oStream << std::setw(wid) << i;
			oStream << std::endl;
			oStream << std::setw(wid) << ' ' << ' ';
			for (int i = 0; i < graph.vertexCount; ++i) 
				oStream << std::setw(wid) << '_';
			oStream << std::endl;

			for (int i = 0; i < graph.vertexCount; ++i) {
				oStream << std::setw(wid) << i << '|';
				for (int j = 0; j < graph.vertexCount; ++j)
					oStream << std::setw(wid) << (int)graph.adjMatrix[i][j];
				oStream << std::endl;
			}
		}
		return oStream;
	}
};

Graph::Graph(int vertCount) : vertexCount(vertCount), adjMatrix(new unsigned char* [vertCount]) {
	for (int i = 0; i < vertCount; ++i) {
		adjMatrix[i] = new unsigned char[vertCount];
		for (int j = 0; j < vertCount; ++j) adjMatrix[i][j] =(rand() % zeroChance > 0) ? rand() % maxMultEdges + 1 : 0;
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