/*
 ============================================================================
 Name        : aa.c
 Description : OpenMP in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE 1000

int main(int argc, char *argv[]) {
		char result[MAX_LINE][8];
		char data[MAX_LINE][8];
		char dictionary[2][8];
		strcpy(dictionary[0],"semih");
		strcpy(dictionary[1],"ogulcan");

		srand(time(NULL));
		int i;

		for (i = 0; i < MAX_LINE; i++) {
			int r = (rand() % 5);
			if (r == 0) {
				strcpy(data[i], "semih");
			} else if (r == 1) {
				strcpy(data[i], "semihd");
			} else if (r == 2) {
				strcpy(data[i], "ogulcan");
			} else if (r == 3) {
				strcpy(data[i], "ogulcand");
			} else {
				strcpy(data[i], "asdasd");
			}
		}

	int j,k, r = 0, tid;

#pragma omp parallel private(i,j,k,r,tid)
	{

		tid = omp_get_thread_num();

		int dist = MAX_LINE / omp_get_num_threads();
		printf("dist:%d", dist);

		for (i = 0; (tid * dist) + i < (dist * tid) + dist; i++) {

			for(k=0;k<2;k++){

			for (j = 0; j < 8; j++) {

				if (data[(tid * dist) + i][j] == dictionary[k][j]) {
					r++;
				}


			if (r > 3 ) {

				strcpy(result[(tid * dist) + i], dictionary[k]);

			} else if(strlen(result[(tid * dist) + i])<5){
				strcpy(result[(tid * dist) + i], data[(tid * dist) + i]);
			}

			}r = 0;
		}}

	}
	for (i = 0; i < MAX_LINE; i++) {
		printf("result %d = %s\n", i, result[i]);

	}

	return 0;
}

