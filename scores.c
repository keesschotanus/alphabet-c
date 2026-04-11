#include <stdio.h>
#include <string.h>

#include "alphabet.h"

#define MAX_NUMBER_OF_HIGH_SCORES 10

static int numberOfHighScores = 0;
static highScore scores[MAX_NUMBER_OF_HIGH_SCORES];

void readHighScores(void) {
	FILE *file = fopen("highscores.txt", "r");
	if (file) {
		while (fscanf(file, "%f %30[^\n]",
				&scores[numberOfHighScores].score,
				scores[numberOfHighScores].quote) == 2) {
			++numberOfHighScores;
			// Skip the newline character after the quote
			fgetc(file);
		}

		fclose(file);
	}
}

static void writeHighScores() {
	FILE *file = fopen("highscores.txt", "w+");
	if (file) {
		for (int i = 0; i < numberOfHighScores; i++) {
			fprintf(file, "%.3f %s\n", scores[i].score, scores[i].quote);
		}
		fclose(file);
	} else {
		fprintf(stderr, "Failed to open highscores.txt for writing\n");
	}
}

void processScore(float score) {
	printf("Your score: %.3f seconds\n", score);
	if (numberOfHighScores < MAX_NUMBER_OF_HIGH_SCORES || score < scores[numberOfHighScores - 1].score) {
		printf("Congratulations! You made it to the high scores!\n");
		printf("Enter your quote: ");
		char quote[31] = {0};
		fgets(quote, sizeof(quote), stdin);
		// Remove newline character if present
		quote[strcspn(quote, "\n")] = '\0';

		int insertScorePosition = findHighScorePosition(score);
		// Shift elements to make room for the new score
		for (int i = numberOfHighScores; i > insertScorePosition; i--) {
			scores[i] = scores[i - 1];
		}

		scores[insertScorePosition].score = score;
		snprintf(scores[insertScorePosition].quote, sizeof(scores[insertScorePosition].quote), "%s", quote);

		if (numberOfHighScores < MAX_NUMBER_OF_HIGH_SCORES) {
			numberOfHighScores++;
		}

		writeHighScores();
	} else {
		printf("Sorry, you did not make it to the high scores.\n");
	}
}

int findHighScorePosition(float score) {
	for (int i = 0; i < numberOfHighScores; i++) {
		if (score < scores[i].score) {
			return i;
		}
	}

	return numberOfHighScores;
}

