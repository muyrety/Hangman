#include "display.h"
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

// prints out a picture of the hangman based on how many incorrect guesses have been made
void printHangmanPicture(int tries) 
{
	assert(tries >= 0 && tries <= 6);

	std::cout << "===================================\n";
	std::cout << "   _____\n";
	std::cout << "   |   |\n";

	switch (tries) 
	{
	case 0:
		std::cout << "       |\n";
		std::cout << "       |\n";
		std::cout << "       |\n";

		break;
	case 1:
		std::cout << "   0   |\n";
		std::cout << "       |\n";
		std::cout << "       |\n";

		break;
	case 2:
		std::cout << "   0   |\n";
		std::cout << "   |   |\n";
		std::cout << "       |\n";

		break;
	case 3:
		std::cout << "   0   |\n";
		std::cout << "  /|   |\n";
		std::cout << "       |\n";

		break;
	case 4:
		std::cout << "   0   |\n";
		std::cout << "  /|\\  |\n";
		std::cout << "       |\n";

		break;
	case 5:
		std::cout << "   0   |\n";
		std::cout << "  /|\\  |\n";
		std::cout << "  /    |\n";

		break;
	case 6:
		std::cout << "   0   |\n";
		std::cout << "  /|\\  |\n";
		std::cout << "  / \\  |\n";

		break;
	}

	std::cout << "      _|_\n";
	std::cout << "===================================\n";

}

// prints letters into the console with spaces in between
void printLetters(std::string_view letters)
{
	for (auto i : letters) 
	{
		std::cout << " " << i;
	}
	std::cout << '\n';
}

// prints letters into the console with spaces in between
void printLetters(const std::vector <char>& letters) 
{
	for (auto i : letters) 
	{
		std::cout << " " << i;
	}
	std::cout << '\n';
}

// used for printing players score to console
void printScore(int guessed_easy, int guessed_medium, int guessed_hard) {

	assert(guessed_easy >= 0 && guessed_medium >= 0 && guessed_hard >= 0);

	std::cout << "You already guessed:\n";

	// use "word" instead of "words" if player has only guessed one word
	std::cout << guessed_easy << " easy " << ((guessed_easy == 1) ? "word" : "words") << '\n';

	std::cout << guessed_medium << " medium " << ((guessed_medium == 1) ? "word" : "words") << '\n';

	std::cout << guessed_hard << " hard " << ((guessed_hard == 1) ? "word" : "words") << '\n';
}

// used to display the title screen
void titleScreen(int guessed_easy, int guessed_medium, int guessed_hard) 
{
	assert(guessed_easy >= 0 && guessed_medium >= 0 && guessed_hard >= 0);

	std::cout << "Welcome to Hangman!\n";

	printScore(guessed_easy, guessed_medium, guessed_hard);

	std::cout << "Select your game mode:\n";
	std::cout << "1. Easy\n";
	std::cout << "2. Medium\n";
	std::cout << "3. Hard\n";
	std::cout << "4. Reset score\n";
	std::cout << "5. Exit\n";
}