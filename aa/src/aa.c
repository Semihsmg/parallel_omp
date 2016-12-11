/*
 ============================================================================
 Name        : aa.c
 Author      : bellideil
 Version     : Nerden bileyim?!?
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_NUMBER 1000
#define MAX_WORD_NUMBER 1000

int main(int argc, char *argv[]) {

	char *fileDir = "D:\\text.txt";
	char *resultDir = "D:\\result.txt";

	FILE *txtFile = fopen(fileDir, "r");
	FILE *txtResult = fopen(resultDir, "w");

	if (txtFile != NULL) {

		printf("File dir found: %s\n", fileDir);
		int i = 0;
		char words[MAX_WORD_NUMBER][MAX_LINE_NUMBER];

		while (i < MAX_WORD_NUMBER && !feof(txtFile)) {
			fgets(words[i], MAX_LINE_NUMBER, txtFile);
			fputs(words[i], txtResult);
			i++;
		}
		printf("File process done!");

	} else {
		printf("%s not found!\n", fileDir);
	}

	fclose(txtFile);
	fclose(txtResult);

	printf("\n\n");

	int numThreads, tid;

	/* This creates a team of threads; each thread has own copy of variables  */
#pragma omp parallel private(numThreads, tid)
	{
		tid = omp_get_thread_num();
		printf("Hello World from thread number %d\n", tid);

		/* The following is executed by the master thread only (tid=0) */
		if (tid == 0) {
			numThreads = omp_get_num_threads();
			printf("Number of threads is %d\n", numThreads);
		}
	}
	return 0;
}

