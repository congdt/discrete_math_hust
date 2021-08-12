/*
**	List all permutation of N elements
**	
**	Idea: detail in permuation_n_2.c 
**
*/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include "m_timer.h"

#define N 11


int A[N];
int count = 0;

void init() {
	for (int i = 0; i < N; i++)
		A[i] = -1;
}

void print_A() {
	for (int i = 0; i < N; i++) {
		printf(" %2d", A[i]);
	}
	printf("\n");
	count++;
}

int checkExistance(int n) {
	for (int i = 0; i < N; i++) {
		if (A[i] == n) 
			return 1;
	}

	return 0;
}

int permute(int n) {
	for (int i = 0; i < N; i++) {
		if (checkExistance(i)) 
			continue; 
		A[n] = i; 
		if (n == N - 1) 
			print_A();
		else 
			permute(n + 1);
	}

	// erase old value 
	A[n] = -1;
}


int main(int agrg, char **argv) {
	init();
	
	long start_time = get_current_timestamp_ms();
	permute(0);

	printf("Total permuation: %d\n", count);
	printf("\n Time consuming: %ld seconds\n", get_current_timestamp_ms() - start_time);

}
