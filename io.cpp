#include <io.h>
#include <iostream>
#include <string_view>
#include <cstddef>
#include <vector>
#include <cassert>

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

// prints the playing letters into the console
void printLetters(std::string_view letters) 
{
	for (auto i : letters) 
	{
		std::cout << " " << i;
	}
	std::cout << '\n';
}

// prints letters into the console with spaces in between. works with std::vector <char> and std::string_view
void printLetters(const std::vector <char>& letters) 
{
	for (auto i : letters) 
	{
		std::cout << " " << i;
	}
	std::cout << '\n';
}