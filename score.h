#ifndef SCORE_MANAGMENT_H
#define SCORE_MANAGMENT_H

// used for writing the score to a file
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard);

int readScore(int& guessed_easy, int& guessed_medium, int& guessed_hard);

// used for changing the players score (in case of a win)
void incrementScore(int game_mode, int& guessed_easy,
	int& guessed_medium, int& guessed_hard);

#endif