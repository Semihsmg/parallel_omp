/*
 ============================================================================
 Name        : aa.c
 Description : OpenMP in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 130000

int main(int argc, char *argv[]) {

	clock_t begin = clock();

	char result[MAX_LINE][8];
	char data[MAX_LINE][8];
	char dictionary[3][8];
	strcpy(dictionary[0], "semih");
	strcpy(dictionary[1], "ogulcan");
	strcpy(dictionary[2], "omer");

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
			strcpy(data[i], "ogulcad");
		} else {
			strcpy(data[i], "omeree");
		}

	}

	//Print input data
	for (i = 0; i < 20; i++) {
		printf("Data %d: %s\n", i, data[i]);
	}

	int j, k, r = 0, tid, totalThreadNum;

#pragma omp parallel private(i,j,k,r,tid,totalThreadNum)
	{
		// Get thread ID
		tid = omp_get_thread_num();
		//Total thread number
		totalThreadNum = omp_get_num_threads();

		// Divide MAX_LINE to total number of threads
		// To find how many lines assigned to each thread
		int dist = MAX_LINE / totalThreadNum;

		// Start and end gives range to each thread for "for loop"
		int start = (tid * dist);
		int end = (dist * tid) + dist;

		// Only master thread prints this section
		if (tid == 0) {
			printf("--------------------------\n");
			printf("Total thread: %d\n", totalThreadNum);
			printf("Distance: %d\n", dist);
			printf("--------------------------\n");
		}

		// Each thread covers its distance (e.g. 0 -> 20.000)
		for (i = 0; start + i < end; i++) {
			// Dictionary length
			for (k = 0; k < 3; k++) {
				for (j = 0; j < 8; j++) {
					if (data[start + i][j] == dictionary[k][j]) {
						r++;
					}
					if (r > 3) {
						strcpy(result[start + i], dictionary[k]);

					} else if (strlen(result[start + i]) < 5) {
						strcpy(result[start + i], data[start + i]);
					}
				}
				r = 0;
			}
		}

		// Prints time spend value for each thread.
		printf("--------------------------\n");
		clock_t endTime = clock();

		double time_spent = (double) (endTime - begin) / CLOCKS_PER_SEC;
		printf("Thread ID: %d\n", tid);
		printf("Time spend: %f\n", time_spent);
		printf("--------------------------\n");
	}
#pragma omp barrier//Barrier for each thread to finish

	//Print corrected results
	for (i = 0; i < 20; i++) {
		printf("result %d = %s\n", i, result[i]);
	}

	return 0;
}
