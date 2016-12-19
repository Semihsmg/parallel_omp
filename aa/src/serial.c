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

	int j, k, r = 0;

	for (i = 0; i < MAX_LINE; i++) {
		// Dictionary length
		for (k = 0; k < 3; k++) {
			for (j = 0; j < 8; j++) {
				if (data[i][j] == dictionary[k][j]) {
					r++;
				}
				if (r > 3) {
					strcpy(result[i], dictionary[k]);

				} else if (strlen(result[i]) < 5) {
					strcpy(result[i], data[i]);
				}
			}
			r = 0;
		}

	}
	// Prints time spend value for each thread.
	printf("--------------------------\n");
	clock_t endTime = clock();

	double time_spent = (double) (endTime - begin) / CLOCKS_PER_SEC;
	printf("time spent:%f\n", time_spent);
	printf("--------------------------\n");
	//Print corrected results
	for (i = 0; i < 20; i++) {
		printf("result %d = %s\n", i, result[i]);
	}

	return 0;
}

