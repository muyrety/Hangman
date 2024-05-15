#ifndef SCORE_MANAGMENT_H
#define SCORE_MANAGMENT_H

// used for writing the score to a file
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard);

bool readScore(int& guessed_easy, int& guessed_medium, int& guessed_hard);

// used for changing the players score (in case of a win)
void changeScore(int difficulty, int& guessed_easy,
	int& guessed_medium, int& guessed_hard);

#endif