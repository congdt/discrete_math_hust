/*
read from file, the data structure of the tree 

First line: N: number of Vertext 
N next line: is adjeacency Matrix represent Graph 

*/


#include <stdio.h>
#include <stdlib.h> 

int input_data(int** adjMatrix, int *size, char *filename) {
	FILE *file = fopen(filename, "r");
	
	if (!file) {
		printf("ERROR: Fail to open file %s\n", filename);
		return 0;
	}
	int n, tmp;
	int *matrix;
	
	fscanf(file, "%d", &n);
	matrix = (int *) malloc(n * n * sizeof(int));
	if (!matrix) 
		return 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(file, "%d", &tmp);
			*(matrix + i * n + j) = tmp;
		}
	}

	*size = n;
	*adjMatrix = matrix;
	fclose(file);
	return 1;
}

void test_input_data(int *adjMatrix, int size) {
	printf("\n ============ ===== = \n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf(" %d", *(adjMatrix + i * size + j));
		}
		printf("\n");
	}
	printf("===================== \n");
}


void dfs(int *matrix, int v, int size, int *visited) {
	printf(" -> %d ", v);
	visited[v] = 1;
	for (int i = 0; i < size; i++) {
		if (!visited[i] && matrix[v*size + i] == 1) {

			dfs(matrix, i, size, visited);
		}
	}
}


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: %s input_file\n", argv[0]);
		return 0;
	}

	int *adjMatrix = 0;
	int n = 0;
	int *visited;
	if (!input_data(&adjMatrix, &n, argv[1])) return 0;
	test_input_data(adjMatrix, n);

	visited = (int *) malloc(n * sizeof(int));
	memset(visited, 0, n * sizeof(int));
	dfs (adjMatrix, 0, n, visited); 

	printf("\n");

	free(adjMatrix);
	adjMatrix = 0;
	return 0;
}