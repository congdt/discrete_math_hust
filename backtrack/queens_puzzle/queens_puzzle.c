#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "m_timer.h"


int *A; 	// store result 
int *B;		// store status of Chess Table 
int N; 		// size of chess table (NxN)
int count = 0;

void init() {
	A = (int*) malloc (sizeof(int) * N * 2);
	B = (int*) malloc (sizeof(int) * N * N);

	for(int i = 0; i < N; i++) 
		A[2*i] = i;
	memset(B, 0, sizeof(int) * N * N);
}

void deinit(){
	free(A);
	free(B);
}

void print_result() 
{
	for (int i = 0 ; i < N; i++) {
		printf("%d %d\n", A[i*2], A[i*2 + 1]);
	}
	printf("----------------------------\n\n");
}

int check_input(int argc, char **argv) {
	if (argc != 2) {
		printf("Invalid input\n");
		printf("Usage: \n");
		printf("./%s param1  // param1 is N, number of rows & col in table\n", argv[0]);
		return 0;
	}

	N = atoi(argv[1]);
	if (N <= 0) {
		printf("Invalid Input value: N=%d, argv[1] = %s\n", N, argv[1]);
		return 0;
	}

	return 1;
}


void print_B_debug() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) 
			printf(" %d", *(B + i*N + j));

		printf("\n");
	}
	printf(" ========================\n\n");
}


/*
**	Idea: 
**		Backtrack to check all possible case 
**		To decrease number of cases, when we perform step i, we will mark all unallowed position in step i+1 -> N 
**
*/
int try(int n) {
	//printf(" ############### step %d #################\n", n);
	
	for (int i = 0; i < N; i++) {
		if (*(B + n*N + i) == 0) {
			// printf(" ===== (%d, %d) ====\n", n, i);
			// print_result();
			*(A + n*2 + 1) = i;
			if (n == N - 1) {
				count++;
				print_result();
			}
			else {
				// mark cells
				for (int j = n+1; j < N; j++) {
					*(B + j*N + i) += 1;
				}
				for (int j = n + 1, k = i + 1; j < N && k < N; j++, k++) 
					*(B + j*N + k) += 1; 

				for (int j = n + 1, k = i - 1; j < N && k >= 0; j++, k--) 
					*(B + j*N + k) += 1;

				// print_B_debug();
				
				try(n+1);

				// unmark cells
				for (int j = n+1; j < N; j++) {
					*(B + j*N + i) -= 1;
				}
				for (int j = n + 1, k = i + 1; j < N && k < N; j++, k++) 
					*(B + j*N + k) -= 1; 

				for (int j = n + 1, k = i - 1; j < N && k >= 0; j++, k--) 
					*(B + j*N + k) -= 1;
			}

		}
	}
}

int main(int argc, char ** argv) 
{
	if (!check_input(argc, argv)) 
		return 0;

	init();

	long start_time = get_current_timestamp_ms();
	try(0);

	deinit();

	printf("Number of result: %d\n", count);
	printf("TimeConsuming = %ld\n", get_current_timestamp_ms() - start_time);

	return 0;
}
