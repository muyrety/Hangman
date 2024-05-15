#define UNIT_TESTING

#ifdef UNIT_TESTING
#include "output.h"

void testprintLetters()
{
	// string_view oveload
	printLetters("hello");
	printLetters("this is a long string");
	printLetters("");

	// vector overload
	printLetters(std::vector<char>{'i', ' ', 'a', 'm', ' ', 'h', 'a', 'p', 'p', 'y'});
	printLetters(std::vector<char>{'a', 'h', 'h', '9', 'c'});
	printLetters(std::vector<char>{});

}

void testprintHangmanPicture()
{
	//printHangmanPicture(-1);
	printHangmanPicture(0);
	printHangmanPicture(1);
	printHangmanPicture(2);
	printHangmanPicture(3);
	printHangmanPicture(4);
	printHangmanPicture(5);
	printHangmanPicture(6);
	//printHangmanPicture(7);
	//printHangmanPicture(-111);
	//printHangmanPicture(500);
}

void testprintScore()
{
	printScore(1, 1, 1);
	printScore(1, 2, 2);
	printScore(5, 5, 5);
	printScore(0, 0, 0);
	printScore(500, 16, 567);
	//printScore(-1, 7, 5);

}

void testtitleScreen()
{
	titleScreen(5, 2, 5);
	//titleScreen(-1, 5, 6);
	titleScreen(8989, 635, 54);
}

void testwriteScore()
{
	writeScore(1, 256, 65);
}
int main()
{
	testwriteScore();
	return 0;
}


#else
#include "output.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// used for choosing a topic of playing or for returing "error" if it's not possible to retrieve it
std::string topicChooser();

// used for selecing a random word from a .txt file based on difficulty
// and for returning an error, would there be any problems while choosing the word
std::string wordChooser(int difficulty, std::string topic);

// used to obtain a valid difficulty value from the user
int getDifficulty();

// used for obtaining a valid guess from the user (only 1 character - a letter, not previously guessed)
// converts uppercase guesses to lowercase
char getValidGuess(std::vector<char> incorrect_guesses, std::string game_letters);

// used to check if the players guess is valid
bool checkGuess(char guess, std::string word);

// used for writing the score to score.txt
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard);

// used for changing the players score (in case of a win)
void changeScore(int difficulty, int& guessed_easy, int& guessed_medium, int& guessed_hard);

// used for reading the score from score.txt
bool readScore(int& guessed_easy, int& guessed_medium, int& guessed_hard);

// used to display the title screen
void titleScreen(int guessed_easy, int guessed_medium, int guessed_hard);

// used to change game_letters to the players guess
void changeGameLetters(char guess, std::string& game_letters, std::string word);


int main() {

	// stores how many words did the player guess previously (the score)
	int guessed_easy{ };
	int guessed_medium{ };
	int guessed_hard{ };

	// if readScore() returned false (score retrieval unsuccessful) send out an error message
	// note - this changes the score values since they are passed by reference
	if ( !readScore(guessed_easy, guessed_medium, guessed_hard) ) {
		std::cerr << "Error opening the score file!\n";
		return 1;
	}

	titleScreen(guessed_easy, guessed_medium, guessed_hard);

	// used for storing the difficulty player wants to play on
	int difficulty{ getDifficulty() };

	// if player selects "Reset score"
	while (difficulty == 4) {
		guessed_easy = 0;										// score values are set to 0
		guessed_medium = 0;
		guessed_hard = 0;

		writeScore(guessed_easy, guessed_medium, guessed_hard);	// score values in the file are immediately replaced

		std::cout << "Score has been reset!\n";

		titleScreen(guessed_easy, guessed_medium, guessed_hard);
		difficulty = getDifficulty();							// asks for a new difficulty value
	}

	// if player selects "Exit", program is terminated with an early return statement
	if (difficulty == 5)
		return 0;

	// stores a randomly selected topic by topicChooser()
	std::string topic{ topicChooser() };

	// if topicChooser() returns "error", it means the topic file could'nt be accessed
	if (topic == "error") {
		std::cerr << "There has been an error while retrieving the topics\n";
		return 1;
	}

	// Word player is trying to guess. Is initialized with a random word from wordChooser().
	std::string word{ wordChooser(difficulty, topic) };

	// if wordChooser() returns "error1" that means there has been an error while opening the chosen difficulties
	// words file
	if (word == "error1") {
		std::cerr << "There has been an error obtaining words!\n";
		return 1;
	}

	// if wordChooser() returns "error2" that means that the program could'nt find the topic in the selected words file
	if (word == "error2") {
		std::cerr << "Topic not found in the word file!\n";
		return 1;
	}

	// main playing field, begins filled with underscores,
	// changes as the player guesses more letters
	std::string game_letters (word.size(), '_');

	// contains all the players incorrect guesses
	std::vector <char> incorrect_guesses{ };

	int tries{ 0 };

	// players guess for a single iteration
	char guess{ };

	// determines whether the player guessed correctly for the iteration
	bool guessed_correctly{ };

	bool game_won{ false };
	bool game_lost{ false };

	// main playing function
	while (!game_lost && !game_won) {

		guessed_correctly = false;					 // reset the guessed_correctly boolean since a new iteration has began

		printHangmanPicture(tries);
		std::cout << "Topic of the word: " << topic << '\n';
		std::cout << "Incorrect guesses:";
		printLetters(incorrect_guesses);
		printLetters(game_letters);


		guess = getValidGuess(incorrect_guesses, game_letters);

		guessed_correctly = checkGuess(guess, word);
		
		if (guessed_correctly) {
			std::cout << "Correct!\n";
			changeGameLetters(guess, game_letters, word);
		}
		else {
			std::cout << "You guessed incorrectly\n";
			incorrect_guesses.push_back(guess);
			++tries;
		}
	
		// checks if game has been lost
		if (tries > 5) {							 // if player reaches more than 5 tries the game is lost
			printHangmanPicture(tries);
			std::cout << "GAME OVER!\n";
			std::cout << "The correct word was " << word << '\n';
			game_lost = true;
		}

		// if game is not lost, checks if game is won
		else if (game_letters == word) {
			printHangmanPicture(tries);
			printLetters(game_letters);

			std::cout << "Congrats! You won!\n";
			changeScore(difficulty, guessed_easy, guessed_medium, guessed_hard);
			game_won = true;
		}
	}

	return 0;
}
#endif
