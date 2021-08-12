#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <utility>

using namespace std;

class Graph {
public : 
	virtual void setEdgeWeight(int i, int j, int weight) = 0;
	virtual int getEdgeWeight(int i, int j) = 0; 
	virtual void printGraph() = 0;
	virtual void bfs(int v) = 0;
};

class AdjMatrixGraph : Graph {

public: 
	AdjMatrixGraph(int size) {
		this->size = size;
		adjMatrix = new int[size * size];
		memset(adjMatrix, 0, size * size * sizeof(int));
		// bfsQueue = new queue<int>();
		visited = new int[size];
		memset(visited, 0, size * sizeof(int));
	}

	~AdjMatrixGraph() {
		printf("Destroy AdjMatrixGraph\n");
		delete adjMatrix;
		delete visited;

		adjMatrix = 0;
	}

	int getEdgeWeight (int i, int j) {
		return *(adjMatrix + i*size + j);
	}

	void setEdgeWeight (int i, int j, int weight) {
		*(adjMatrix + i*size + j) = weight;
		*(adjMatrix + j*size + i) = weight;
	}

	void printGraph () {
		printf("+++ printGraph\n");
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf(" %d", *(adjMatrix + i*size + j));
			}
			printf("\n");
		}
	}

	void bfs(int v) {
		bfsQueue.push(v);
		while (!bfsQueue.empty()) {
			int visiting = bfsQueue.front();
			bfsQueue.pop();
			printf(" -> %d ", visiting);
			visited[visiting] = 1;
			for (int j = 0; j < size; j++) {
				if (!visited[j] && *(adjMatrix + visiting *size + j) == 1) {
					bfsQueue.push(j);
				}
			}
		}
	}

private :
	int size; 
	int* adjMatrix;
	queue<int> bfsQueue;
	int *visited;
};


class AdjListGraph : Graph 
{

public : 
	AdjListGraph (int size) {
		this->size = size; 
		// adjList = new std::vector<std::vector<pair<int, int> > >(size);
		for (int i = 0; i < size; i++) {
			vector<pair<int, int> >v1;
			adjList.push_back(v1);
		}
	}

	void setEdgeWeight(int i, int j, int weight){
		if (i >= size || j >= size) return;
		setEdgeWeight_impl(i, j, weight);
		setEdgeWeight_impl(j, i, weight);
	}

	void setEdgeWeight_impl(int i, int j, int weight) {
		// check if this edge exist
		int idx = 0; 
		for (idx = 0; idx < adjList[i].size(); idx++) {
			if (adjList[i][idx].first == j) {
				adjList[i][idx].second = weight;
				break;
			}
		}
		if (idx == adjList[i].size()) {	// not exist
			pair<int, int> e;
			e.first = j; 
			e.second = weight;
			adjList[i].push_back(e);
		}

	}

	int getEdgeWeight(int i, int j) {
		int idx; 
		for (idx = 0; idx < adjList[i].size(); idx++) {
			if (adjList[i][idx].first == j) 
				return adjList[i][idx].second;
		}
		return 0;
	}

	void printGraph() {
		for (int i = 0; i < adjList.size(); i++) {
			printf("edge[%d]: ", i);
			for (int j = 0; j < adjList[i].size(); j++) 
				printf(" <%d, %d>", adjList[i][j].first, adjList[i][j].second);
			printf("\n");
		}}

	void bfs(int v) {
		int visited[size] = {0, };
		queue<int> bfsQueue; 

		bfsQueue.push(v);
		while (!bfsQueue.empty()) {
			int i = bfsQueue.front();
			printf(" -> %d", i);
			visited[i] = 1;
			bfsQueue.pop();
			for (int j = 0; j < adjList[i].size(); j++) {
				if (!visited[adjList[i][j].first]) {
					bfsQueue.push(adjList[i][j].first);
				}
			}
		}
	}

private: 
	int size; 
	std::vector<std::vector<pair<int, int> > > adjList;
};

int main (int argc, char **argv) {
	AdjMatrixGraph *graph = new AdjMatrixGraph(6); 
	// AdjListGraph *graph = new AdjListGraph(6);

	((Graph*)graph)->setEdgeWeight(0, 1, 1);
	((Graph*)graph)->setEdgeWeight(0, 4, 1);
	((Graph*)graph)->setEdgeWeight(1, 2, 1);
	((Graph*)graph)->setEdgeWeight(1, 3, 1);
	((Graph*)graph)->setEdgeWeight(3, 5, 1);
	((Graph*)graph)->printGraph();
	printf("hahaha\n");
	((Graph*)graph)->bfs(0);

	printf("\n");
	delete graph;
	return 0;
}

