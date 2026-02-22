#include <stdio.h>
#include <string.h>

#include "alphabet.h"

#define MAX_NUMBER_OF_HIGH_SCORES 10

static int numberOfHighScores = 0;
static highScore scores[MAX_NUMBER_OF_HIGH_SCORES];

void readHighScores() {
	FILE *file = fopen("highscores.txt", "r");
	if (file) {
		while (fscanf(file, "%f %30[^\n]",
                                &scores[numberOfHighScores].score,
                                scores[numberOfHighScores].name) == 2) {
        		++numberOfHighScores;
        		// Skip the newline character after the name
        		fgetc(file);
    		}
    
    		fclose(file);
	}
}

static void writeHighScores() {
	FILE *file = fopen("highscores.txt", "w+");
	if (file) {
		for (int i = 0; i < numberOfHighScores; i++) {
			fprintf(file, "%.3f %s\n", scores[i].score, scores[i].name);
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
                char name[30] = {0};
                fgets(name, sizeof(name), stdin);
                // Remove newline character if present
                name[strcspn(name, "\n")] = '\0';

                // Insert the new score in the correct position
                int i = numberOfHighScores - 1;
                while (i >= 0 && scores[i].score > score) {
                        scores[i + 1] = scores[i];
                        i--;
                }
                scores[i + 1].score = score;
                snprintf(scores[i + 1].name, sizeof(scores[i + 1].name), "%s", name);

                if (numberOfHighScores < MAX_NUMBER_OF_HIGH_SCORES) {
                        numberOfHighScores++;
                }

                writeHighScores();
        } else {
                printf("Sorry, you did not make it to the high scores.\n");
        }
}

