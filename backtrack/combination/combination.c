/*
** 	There is an array N elements from 1 -> N
**	This program lists all possible combination of N choose M
**	
*/

#include <stdio.h>
#include <stdlib.h>
#include "m_timer.h"

#define RESULT_OK 0 
#define RESULT_FAIL 1

int N, M;
int *A; 
int *B; 

int checkInput(int argc, char** argv) {
	if (argc != 3) {
		printf("Invalid input\n");
		printf("Usage: List combination N choose M. N element is 1, 2, ..., N \n") ;
		printf("%s param1 param2 // while param1 is N, param 2 is M\n", argv[0]);
		return RESULT_FAIL;
	}

	N = atoi(argv[1]);
	M = atoi(argv[2]);

	if (N < M || M < 1) {
		printf("Not satisfy param constrain\n");
		return RESULT_FAIL;
	}
	return RESULT_OK;
}

void init(){
	for (int i = 0; i < N; i++) 
		A[i] = i;
	for (int i = 1; i <= M; i++) 
		B[i] = -1;
	B[0] = 0;
}

void print_result() {
	for (int i = 1; i <= M; i++) 
		printf("%d ", B[i]);
	printf("\n");
}

void try(int n) {
	for (int i = B[n-1]+1; i <= N - M + n; i++) {
		B[n] = i;
		if (n == M) {
			print_result();
		}
		else {
			try(n + 1);
		}
	}
}

int main(int argc, char **argv) {
	if (checkInput(argc, argv) == RESULT_FAIL)
		return 0; 

	A = (int *) malloc(sizeof(int) * N);
	B = (int *) malloc(sizeof(int) * (M+1));

	long start_time = get_current_timestamp_ms();
	try(1);
	printf("Time consuming: %ld\n", get_current_timestamp_ms() - start_time);

	free(A);
	free(B);
	return 0;
}
