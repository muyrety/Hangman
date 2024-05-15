#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <cctype>

// prints out a picture of the hangman based on how many incorrect guesses have been made
void hangmanPicture(int tries) {
	switch (tries) {
	case 0:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "       |\n"
				  << "       |\n"
				  << "       |\n"
				  << "      _|_\n"
				  << "===================================\n";
		break;
	case 1:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "   0   |\n"
				  << "       |\n"
				  << "       |\n"
				  << "      _|_\n"
				  << "===================================\n";
		break;
	case 2:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "   0   |\n"
				  << "   |   |\n"
				  << "       |\n"
				  << "      _|_\n"
				  << "===================================\n";
		break;
	case 3:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "   0   |\n"
				  << "  /|   |\n"
				  << "       |\n"
				  << "      _|_\n"
				  << "===================================\n";
		break;
	case 4:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "   0   |\n"
				  << "  /|\\  |\n"
				  << "       |\n"
				  << "      _|_\n"
				  << "===================================\n";
		break;
	case 5:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "   0   |\n"
				  << "  /|\\  |\n"
				  << "  /    |\n"
				  << "      _|_\n"
				  << "===================================\n";
		break;
	case 6:
		std::cout << "===================================\n"
				  << "   _____\n"
				  << "   |   |\n"
				  << "   0   |\n"
				  << "  /|\\  |\n"
				  << "  / \\  |\n"
				  << "      _|_\n"
				  << "===================================\n"
				  << "GAME OVER!\n";
		break;
	}
}

// prints the playing letters into the console
void printLetters(std::string game_letters) {
	for (size_t i{ 0 }; i < game_letters.size(); ++i) {
		std::cout << " " << game_letters[i];
	}
	std::cout << '\n';
}

// prints incorrectly guessed letters into the console
void printIncorrectLetters(std::vector <char> incorrect_guesses) {
	std::cout << "Incorrect guesses:";
	for (size_t i{ 0 }; i < incorrect_guesses.size(); ++i) {
		std::cout << " " << incorrect_guesses[i];
	}
	std::cout << '\n';
}

// used for selecing a random word from a .txt file based on difficulty and topic
// Error codes:
// error1 - can't access the word file
// error2 - can't find the chosen topic in the word file
std::string wordChooser(int difficulty, std::string topic) {

	// garbage value used for placing the cursor on the chosen topics words
	// and then for filling up the words vector
	std::string foo{ };

	// used for holding all the words of the player selected difficulty, of the chosen topic
	std::vector <std::string> words{ };

	// curly braces in each case to specify that these word ifstreams
	// only need to be available in the selected cases scope
	switch (difficulty) {
	case 1:
	{
		std::ifstream easy("easywords.txt");

		if ( easy.fail() ) {
			return "error1";
		}

		// used for reading the file until selected topic is reached
		do {
			easy >> foo;
			if (foo == "endoffile")	// if end of file is reached without reaching topic first, topic is not in the file
				return "error2";
		} while (foo != topic);

		// used for filling words vector with words in between the selected topics name and "endoftopic"
		while (true) {
			easy >> foo;
			if (foo == "endoftopic")
				break;
			else words.push_back(foo);
		}

		easy.close();
	}
	break;
	case 2:
	{
		std::ifstream medium("mediumwords.txt");

		if ( medium.fail() ) {
			return "error1";
		}

		do {
			medium >> foo;
			if (foo == "endoffile")
				return "error2";
		} while (foo != topic);

		while (true) {
			medium >> foo;
			if (foo == "endoftopic")
				break;
			else words.push_back(foo);
		}

		medium.close();
	}
	break;
	case 3:
	{
		std::ifstream hard("hardwords.txt");

		if ( hard.fail() ) {
			return "error1";
		}

		do {
			hard >> foo;
			if (foo == "endoffile")
				return "error2";
		} while (foo != topic);

		while (true) {
			hard >> foo;
			if (foo == "endoftopic")
				break;
			else words.push_back(foo);
		}

		hard.close();
	}
	break;
	}

	// initialize a marsenne twister PRNG with the seed from random_device()
	std::mt19937 random_number{ std::random_device{}() };

	// initialize an uniform_int_distribution of type size_t. Minimum value - 0.
	// Maximum value - the index of the last element in the words vector.
	std::uniform_int_distribution<size_t> word_index{ 0, words.size() - 1 };

	// the selected word is a randomly chosen element from the words vector
	return words[word_index(random_number)];
}

// used for checking if the letter was previously guessed
bool previouslyGuessed(char guess, std::string game_letters, std::vector <char> incorrect_guesses) {

	// checks if the guess is equal to any game_letters element, returns true if it is
	for (size_t i{ 0 }; i < game_letters.size(); ++i) {
		if (guess == game_letters[i])
			return true;
	}

	// checks if the guess is equal to any incorrect_guesses element, returns true if it is
	for (size_t i{ 0 }; i < incorrect_guesses.size(); ++i) {
		if (guess == incorrect_guesses[i])
			return true;
	}

	// if the guess is not equal to either any game_letters element or any incorrect_guesses element
	// it must not be previously guessed
	return false;
}

// used for obtaining a valid guess from the user (only 1 character - a letter, not previously guessed)
char getValidGuess(std::vector<char> incorrect_guesses, std::string game_letters) {

	char guess{};
	// request an input
	std::cout << "Enter a letter\n";
	std::cin >> guess;

	while (true) {

		// if player guessed more than one character (next character in the input buffer isn't \n)
		if (std::cin.peek() != '\n') {
			std::cout << "You can only guess 1 character at a time! Try again.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// 1. clear the input buffer
			std::cin >> guess;													// 2. get a new guess
			continue;															// 3. check if the new guess is valid
		}

		// if player didn't guess a letter
		if ( !std::isalpha(guess) ) {
			std::cout << "You must input a letter! Try again.\n";
			std::cin >> guess;													// 1. get a new guess
			continue;															// 2. check if the new guess is valid
		}

		// if player guessed an uppercase letter, convert it to lowercase (this is only reached if player
		// guessed only a single character and it is a letter)
		if ( std::isupper(guess) )
			guess = static_cast<char>( std::tolower(guess) );

		// if players guess was guessed before
		if ( previouslyGuessed(guess, game_letters, incorrect_guesses) ) {
			std::cout << "You already guessed this letter! Try again.\n";
			std::cin >> guess;													// 1. get a new guess
			continue;															// 2. check if the new guess is valid
		}

		// if it reaches here, guess must be valid (player guessed only one character
		// that is a letter, not previously guessed)
		return guess;
	}
}

// used for writing the score to score.txt
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard) {
	std::ofstream out_score("score.txt");

	out_score << guessed_easy << '\n'
			  << guessed_medium << '\n'
			  << guessed_hard << '\n';

	out_score.close();
}

// used for changing the players score (in case of a win)
void changeScore(int difficulty, int& guessed_easy, int& guessed_medium, int& guessed_hard) {

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

	writeScore(guessed_easy, guessed_medium, guessed_hard);
}

// used for printing players score to console
void printScore(int guessed_easy, int guessed_medium, int guessed_hard) {

	std::cout << "You already guessed:\n";

	// use "word" instead of "words" if player has only guessed one word
	if (guessed_easy == 1)
		std::cout << guessed_easy << " easy word\n";

	else std::cout << guessed_easy << " easy words\n";

	if (guessed_medium == 1)
		std::cout << guessed_medium << " medium word\n";

	else std::cout << guessed_medium << " medium words\n";

	if (guessed_hard == 1)
		std::cout << guessed_hard << " hard word\n";

	else std::cout << guessed_hard << " hard words\n";
}

// used to display the title screen
void titleScreen(int guessed_easy, int guessed_medium, int guessed_hard) {
	std::cout << "Welcome to Hangman!\n";
	printScore(guessed_easy, guessed_medium, guessed_hard);
	std::cout << "Select your game mode:\n"
			  << "1. Easy\n"
			  << "2. Medium\n"
			  << "3. Hard\n"
			  << "4. Reset score\n"
			  << "5. Exit\n";
}

// used to obtain a valid difficulty value from the user
int getDifficulty() {

	int difficulty{ };

	std::cin >> difficulty;

	// while players input is an integer outside of the specified range or is not an integer
	while ( difficulty < 1 || difficulty > 5 || std::cin.fail() ) {

		if ( std::cin.fail() ) {
			std::cin.clear();													// clear std::cin's error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// clear the input buffer
		}

		std::cout << "Please enter a valid value\n";							// ask for a new guess
		std::cin >> difficulty;
	}
	return difficulty;
}

bool readScore(int& guessed_easy, int& guessed_medium, int& guessed_hard) {
	std::ifstream score("score.txt");
	score >> guessed_easy
		  >> guessed_medium
		  >> guessed_hard;
	if ( score.fail() ) {
		score.close();
		return false;
	}
	else {
		score.close();
		return true;
	}
}

std::string topicChooser() {
	std::ifstream topic("topics.txt");
	if ( topic.fail() )
		return "error";
	
	// vector holding all the topics in the file
	std::vector<std::string> topics{};

	// garbage variable used for filling up topics vector
	std::string foo{};

	// puts strings in topics as long as there are strings to be read from topics.txt
	while (topic >> foo)
		topics.push_back(foo);

	// initialize a marsenne twister PRNG with a seed from std::random_device
	std::mt19937 random_number{ std::random_device{}() };

	// initialize an uniform_int_distribution of type size_t. Minimum value - 0.
	// Maximum value - the index of the last element in the topics vector.
	std::uniform_int_distribution<size_t> topics_index{ 0, topics.size() - 1 };

	// topic is a randomly chosen element from the topics vector
	return topics[topics_index(random_number)];
}

bool checkGuess(char guess, std::string word) {
	for (size_t i{ 0 }; i < word.size(); ++i) {
		if (guess == word[i])
			return true;		// if guess matches with any word's letter, guess is correct.
								// Note - guess is guaranteed not to be guessed before (since getValidGuess() checks that)
	}
	return false;
}

// used to change game_letters to the players guess
void changeGameLetters(char guess, std::string& game_letters, std::string word) {
	for (size_t i{ 0 }; i < word.size(); ++i) {
		// if guess matches with some word's letter
		if (guess == word[i])
			game_letters[i] = guess;	// change the character of game_letters in that spot to guess
	}
}
