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

// used for obtaining a valid guess from the user (only 1 character - a letter, not previously guessed)
char getValidGuess(const std::vector<char>& incorrect_guesses, std::string_view game_letters) 
{

	while(true)
	{
		std::cout << "Enter a letter: ";
		char guess{};
		std::cin >> guess;

		if (!std::cin)
		{
			if (std::cin.eof())
				std::exit(0);

			std::cin.clear();
			ignoreLine();
			std::cout << "Invalid input! Try again.\n";
			continue;
		}

		if (std::cin.peek() != '\n')
		{
			ignoreLine();
			std::cout << "You must only enter one value! Try again.\n";
			continue;
		}

		// if player didn't guess a letter
		if (!std::isalpha(guess)) 
		{
			std::cout << "You must input a letter! Try again.\n";
			continue;												// ask for a new value
		}

		// if player guessed an uppercase letter, convert it to lowercase
		if (std::isupper(guess))
			guess = static_cast<char>(std::tolower(guess));

		// if players guess was guessed before
		if (previouslyGuessed(guess, game_letters, incorrect_guesses)) 
		{
			std::cout << "You already guessed this letter! Try again.\n";
			continue;												// ask for a new value
		}

		// if it reaches here, guess must be valid
		return guess;
	}
}

// used to obtain a valid difficulty value from the user
int getDifficulty() {

	int difficulty{ };

	std::cin >> difficulty;

	// while players input is an integer outside of the specified range or is not an integer
	while (difficulty < 1 || difficulty > 5 || std::cin.fail()) {

		if (std::cin.fail()) {
			std::cin.clear();													// clear std::cin's error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// clear the input buffer
		}

		std::cout << "Please enter a valid value\n";							// ask for a new guess
		std::cin >> difficulty;
	}
	return difficulty;
}