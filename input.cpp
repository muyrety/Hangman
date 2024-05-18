#include "game.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string_view>
#include <vector>

static void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// does std::cin's failure handling
static bool extractionFailed()
{
	if (!std::cin)
	{
		if (std::cin.eof())
			std::exit(0);

		std::cin.clear();
		ignoreLine();
		return true;
	}
	return false;
}

// used for obtaining a valid guess from the user
char getGuess(const std::vector<char>& incorrect_guesses, std::string_view game_letters) 
{

	while(true)
	{
		std::cout << "Enter a letter: ";
		char guess{};
		std::cin >> guess;

		if (extractionFailed())	// if extraction failed
		{
			std::cout << "Invalid input! Try again.\n";
			continue;
		}

		if (std::cin.peek() != '\n')	// if there is extraneous input
		{
			ignoreLine();
			std::cout << "You must only enter one value! Try again.\n";
			continue;
		}

		if (!std::isalpha(guess))	// if player didn't guess a letter
		{
			std::cout << "You must input a letter! Try again.\n";
			continue;					
		}

		// if player guessed an uppercase letter, convert it to lowercase
		if (std::isupper(guess))
			guess = static_cast<char>(std::tolower(guess));

		// if players guess was guessed before
		if (previouslyGuessed(guess, game_letters, incorrect_guesses)) 
		{
			std::cout << "You already guessed this letter! Try again.\n";
			continue;										
		}

		// if it reaches here, guess must be valid
		return guess;
	}
}

// used to obtain a valid game_mode from the user
int getGameMode() 
{
	while(true)
	{ 
		std::cout << "Select your game mode: ";
		int game_mode{};
		std::cin >> game_mode;

		if (extractionFailed())	// if extraction failed
		{
			std::cout << "Invalid input! Try again.\n";
			continue;
		}

		if (std::cin.peek() != '\n')	// if there is extraneous input
		{
			ignoreLine();
			std::cout << "You must only enter one value! Try again.\n";
			continue;

		}

		constexpr int min_game_mode{ 1 };
		constexpr int max_game_mode{ 5 };

		if (game_mode < min_game_mode || game_mode > max_game_mode)	// if game_mode is out of range
		{
			std::cout << "Invalid input! Try again.\n";
			continue;
		}
	
		// if execution got here, input must be valid
		return game_mode;
	}
}