/**
 * @brief Setsup the terminal for single character mode
 */

#include <termios.h>
#include <unistd.h>

static struct termios originalTtystate;

/**
 * @brief Sets up the terminal for non-canonical input mode (raw mode).
 * This allows the program to read input one character at a time,
 * without waiting for a newline and to disable echoing of typed characters.
 */
int setupTerminal() {
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	originalTtystate = ttystate;
	ttystate.c_lflag &= ~(ICANON | ECHO);
	// read one char at a time
	ttystate.c_cc[VMIN] = 1;
	// set the terminal attributes immediately			
	return tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);	
}

/**
 * @brief Undo actions performed in setupTerminal() to restore normal terminal behavior.
 */
void resetTerminal() {
	tcsetattr(STDIN_FILENO, TCSANOW, &originalTtystate);
}
