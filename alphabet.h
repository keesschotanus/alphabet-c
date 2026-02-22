
#ifndef ALPHABET_H
        #define ALPHABET_H
        /* Number of letters in the alphabet */
        #define LETTERS 26

        typedef struct {
                float score;
                char name[31];
        } highScore;

        void init(void);
        void readHighScores(void);
        float processInput(float times[LETTERS]);
        void printHistogram(float times[LETTERS]);
        void processScore(float score);
        int setupTerminal(void);
        void resetTerminal(void);
#endif


