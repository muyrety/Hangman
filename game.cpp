#include "game.h"
#include <cassert>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

bool checkGuess(char guess, std::string_view word) 
{
	for (auto i : word) 
	{
		if (guess == i)
			return true;		// if guess matches with any word's letter, guess is correct.
	}
	return false;
}

// used to change game_letters to the players guess
void changeGameLetters(char guess, std::string& game_letters, std::string_view word) 
{
	assert(game_letters.size() == word.size());

	for (std::size_t i{ 0 }; i < word.size(); ++i)
	{
		// if guess matches with some word's letter
		if (guess == word[i])
			game_letters[i] = guess;	// change the character of game_letters in that spot to guess
	}
}

// used for checking if the letter was previously guessed
bool previouslyGuessed(char guess, std::string_view game_letters, const std::vector <char>& incorrect_guesses) 
{
	for (auto i : game_letters) 
	{
		if (guess == i)
			return true;
	}

	for (auto i : incorrect_guesses) 
	{
		if (guess == i)
			return true;
	}

	// if the guess is not equal to either any game_letters element or any incorrect_guesses element
	// it must not be previously guessed
	return false;
}