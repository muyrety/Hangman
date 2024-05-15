#include "Constants.h"
#include <cassert>
#include <fstream>

// used for writing the score to a file
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard)
{
	assert(guessed_easy >= 0 && guessed_medium >= 0 && guessed_hard >= 0);

	std::ofstream out_score(FileNames::score_file);

	out_score << guessed_easy << '\n';
	out_score << guessed_medium << '\n';
	out_score << guessed_hard << '\n';

	out_score.close();
}

bool readScore(int& guessed_easy, int& guessed_medium, int& guessed_hard) 
{
	std::ifstream score("score.txt");
	score >> guessed_easy
		>> guessed_medium
		>> guessed_hard;
	if (score.fail()) {
		score.close();
		return false;
	}
	else {
		score.close();
		return true;
	}
}

// used for changing the players score (in case of a win)
void changeScore(int difficulty, int& guessed_easy, 
	int& guessed_medium, int& guessed_hard) 
{

	switch (difficulty) {
	case 1:
		++guessed_easy;
		break;
	case 2:
		++guessed_medium;
		break;
	case 3:
		++guessed_hard;
		break;
	}
}