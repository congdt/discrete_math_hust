/*
**	This program lists all Permutation 
**
*/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include "m_timer.h"

#define N 11


int A[N];
char B[N];
int count = 0;

void init() {
	for (int i = 0; i < N; i++){
		A[i] = -1;
		B[i] = 1;
	}

}

void print_A() {
	for (int i = 0; i < N; i++) {
		printf(" %2d", A[i]);
	}
	printf("\n");
	count++;
}

/*
**	Idea: 
**	+ 1. pick 1 value for 1st position 
**	+ 2. do permute() for n-1 remaining elements until there is no element left => we have one permutation 
**		+ Continue it recusively, 2nd position now become 1st position 
**	+ FOR loop is used for change value for each position 
**	
**	
**	B array will save status [used/unused] of element i in A 
*/
int permute(int n) {
	for (int i = 0; i < N; i++) {
		if (B[i]) {
			B[i] = 0;
			A[n] = i; 
			if (n == N-1) {
				print_A();
			}
			else {
				permute(n+1);
			}

			// reset status for B[]
			B[i] = 1;
		}
	}

}


int main(int agrg, char **argv) {
	init();
	
	long start_time = get_current_timestamp_ms();
	permute(0);

	printf("Total permuation: %d\n", count);
	printf("\n Time consuming: %ld seconds\n", get_current_timestamp_ms() - start_time);

}
