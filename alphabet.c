#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "alphabet.h"

int main(void) {
	float times[LETTERS];

	init();

	readHighScores();
	float score = processInput(times);
	resetTerminal();

	printHistogram(times);
	processScore(score);

	return EXIT_SUCCESS;
}

void init() {
	if (setupTerminal() != 0) {
		fprintf(stderr, "Failed to set up terminal\n");
		exit(EXIT_FAILURE);
	}
	atexit(resetTerminal);

	puts("Alphabet game");
	puts("Type the alphabet as fast as you can!");
	puts("Press any key to start...");
	getchar();
	puts("Go!");
}

static char *alphabet = "abcdefghijklmnopqrstuvwxyz";

float processInput(float times[LETTERS]) {
	struct timespec start_time, end_time;
	float totalTime = 0.0f;
	char letter;

	for (int i = 0; i < LETTERS; i++) {
		clock_gettime(CLOCK_MONOTONIC, &start_time);
		do {
			letter = getchar();
			if (tolower(letter) != alphabet[i]) {
				putchar('\a');
			}
		} while (tolower(letter) != alphabet[i]);
		clock_gettime(CLOCK_MONOTONIC, &end_time);

		float time = (end_time.tv_sec - start_time.tv_sec) + 
           		(end_time.tv_nsec - start_time.tv_nsec) / 1e9f; 
		times[i] = time;
		totalTime += time;
		printf("%c (%.3fs)\n", letter, times[i]);
 	}

	printf("Total time  : %.3f seconds\n", totalTime);
	return totalTime;
}

void printHistogram(float times[LETTERS]) {
	// Compute the maximum time of a single letter to scale the histogram
	float maxTime = 0.0f;
	for (int i = 0; i < LETTERS; i++) {
		if (times[i] > maxTime) {
			maxTime = times[i];
		}
	}

	const int MAX_ROWS = 20;
	for (int row = 1; row <= MAX_ROWS; row++) {
		for (int i = 0; i < LETTERS; i++) {
			float threshold = maxTime * (1.0f - (row / (float)MAX_ROWS));
			putchar(times[i] >= threshold ? '#' : ' ');
		}
		putchar('\n');
	}
	puts(alphabet);
}
