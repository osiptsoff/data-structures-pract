#pragma once
#include <iostream>

class Graph
{
	static constexpr int maxVertices = 250;
	static constexpr int maxMultEdges = 10;

	int vertexCount;
	unsigned char** adjMatrix;
public:
	Graph() = delete;
	Graph(const Graph&) = delete;
	Graph(Graph&&) = delete;
	Graph(int vertCount);
	Graph(void* mark) : Graph(rand() % maxVertices) {};
	Graph(std::istream&);
	~Graph() {
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
			oStream.width(wid);
			oStream << ' ' << ' ';
			for (int i = 0; i < graph.vertexCount; ++i) {
				oStream.width(wid);
				oStream << i;
			}
			oStream << std::endl;
			oStream.width(wid);
			oStream << ' ' << ' ';
			for (int i = 0; i < graph.vertexCount; ++i) {
				oStream.width(wid);
				oStream << '_';
			}
			oStream << std::endl;

			for (int i = 0; i < graph.vertexCount; ++i) {
				oStream.width(wid);
				oStream << i << '|';
				for (int j = 0; j < graph.vertexCount; ++j) {
					oStream.width(wid);
					oStream << (int)graph.adjMatrix[i][j];
				}
				oStream << std::endl;
			}
		}
		return oStream;
	}
};

Graph::Graph(int vertCount) : vertexCount(vertCount), adjMatrix(new unsigned char* [vertCount]) {
	for (int i = 0; i < vertCount; ++i) {
		adjMatrix[i] = new unsigned char[vertCount];
		for (int j = 0; j < vertCount; ++j) adjMatrix[i][j] = rand() % maxMultEdges;
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

		for (int i = 0; i < vertexCount && errorCode == 0; ++i)
			for (int j = 0; j < vertexCount && errorCode == 0; ++j)
				if (!iStream.eof()) {
					iStream >> buff;
					if (!iStream.bad() && !iStream.fail())
						if (buff > maxMultEdges)
							errorCode = 2; // too big weight
						else
							adjMatrix[i][j] = buff;
					else
						errorCode = 3; // inappropriate symbol
				}
				else errorCode = 4; // unexpected EOF
	}
	else errorCode = 1; // cannot read the vertex count or unexpected EOF

	if (errorCode != 0)
		throw errorCode;
}