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

#define MAX_LINE_NUMBER 1000
#define MAX_WORD_NUMBER 1000

int main(int argc, char *argv[]) {
	clock_t begin = clock();
	char *fileDir = "C:\\Users\\ogulcan\\Paralel\\text.txt";
	char *resultDir = "C:\\Users\\ogulcan\\Paralel\\result.txt";

	FILE *txtFile = fopen(fileDir, "r"); // open as read only
	FILE *txtResult = fopen(resultDir, "w"); // open as read and write

	printf("File directory found: %s\n", fileDir);
	int i = 0;
	char words[MAX_LINE_NUMBER][MAX_WORD_NUMBER];
	char * prt;

	while (i < MAX_LINE_NUMBER && !feof(txtFile)) {

		fgets(words[i], MAX_WORD_NUMBER, txtFile);
		prt = strtok(&words[i], "' ','\n'");
		while (prt != NULL) {
			printf("%s\n", prt);
			fputs(prt, txtResult);
			putc('\n', txtResult);
			prt = strtok(NULL, "' ','\n'");
		}
		i++;
	}

	fclose(txtFile);
	fclose(txtResult);

	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("\n %f = timespent", time_spent);

	return 0;
}
