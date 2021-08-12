/*
**	This program lists all posible binary sequence with size N 
**	Modify N value for testing 
**
*/

#include <stdio.h> 
#include <stdlib.h> 

#define N 5

int A[N] = {0, };
int g_count = 0;
void print_A() {
	g_count++;
	printf("%3d :", g_count);
	for (int i = 0; i < N; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
}

void Try(int i) {
	A[i] = 0; 
	if (i == N - 1) 
		print_A();
	else 
		Try(i+1);

	A[i] = 1;
	if (i == N - 1) 
		print_A();
	else 
		Try(i+1);
	
}

int main(int argc, char ** argv) {
	Try(0);
}
