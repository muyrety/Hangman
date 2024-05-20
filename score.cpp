#include "score.h"
#include <cassert>
#include <fstream>

constexpr auto score_file{ "score.txt" };

// used for writing the score to a file
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard)
{
	std::ofstream out_score(score_file);

	out_score << guessed_easy << '\n';
	out_score << guessed_medium << '\n';
	out_score << guessed_hard << '\n';

	out_score.close();
}

bool readScore(int& guessed_easy, int& guessed_medium, int& guessed_hard) 
{
	std::ifstream score(score_file);

	if (!score)
		return false;

	score >> guessed_easy;
	score >> guessed_medium;
	score >> guessed_hard;

	assert(guessed_easy >= 0 && guessed_medium >= 0 && guessed_hard >= 0);

	score.close();
	return true;
}

// used for changing the players score (in case of a win)
void incrementScore(int game_mode, int& guessed_easy, 
	int& guessed_medium, int& guessed_hard) 
{
	assert(game_mode >= 1 && game_mode <= 3);

	switch (game_mode) 
	{
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