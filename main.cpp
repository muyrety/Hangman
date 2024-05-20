#define UNIT_TESTING
#ifdef UNIT_TESTING

#include "unit_tests.h"
#include <iostream>

int main()
{
	testcheckGuess();
	std::cout << "testcheckGuess() -- all tests passed\n";

	testchangeGameLetters();
	std::cout << "testchangeGameLetters() -- all tests passed\n";

	testpreviouslyGuessed();
	std::cout << "testpreviouslyGuessed() -- all tests passed\n";

	// testgetGuess();
	// std::cout << "testgetGuess() -- all tests passed\n";

	// testgetGameMode();
	// std::cout << "testgetGameMode() -- all tests passed\n";

	testincrementScore();
	std::cout << "testincrementScore() -- all tests passed\n";

	return 0;
}

#else
#include "constants.h"
#include "display.h"
#include "game.h"
#include "input.h"
#include "score.h"
#include "word_choosing.h"
#include <iostream>
#include <string>
#include <vector>

int main() 
{

	// stores how many words did the player guess previously (the score)
	int guessed_easy{};
	int guessed_medium{};
	int guessed_hard{};

	{	// nested block for score_error_code (isn't needed later)

		int score_error_code{ readScore(guessed_easy, guessed_medium, guessed_hard) };

		// if score retrieval was unsuccessful
		if (score_error_code == error_code::score_fail)
		{
			std::cerr << "Can't open the score file!\n";
			return 1;
		}
		// if negative score values were read
		else if (score_error_code == error_code::negative_score)
		{
			std::cerr << "Negative score values read!\n";
			return 1;
		}
	}

	titleScreen(guessed_easy, guessed_medium, guessed_hard);

	// used for storing the game_mode player wants to play on
	int game_mode{ getGameMode() };

	// if player selects "Reset score"
	while (game_mode == 4) 
	{
		guessed_easy = 0;										// score values are set to 0
		guessed_medium = 0;
		guessed_hard = 0;

		writeScore(guessed_easy, guessed_medium, guessed_hard);	// score values in the file are immediately replaced

		std::cout << "Score has been reset!\n";

		titleScreen(guessed_easy, guessed_medium, guessed_hard);
		game_mode = getGameMode();							// asks for a new game_mode value
	}

	// if player selects "Exit", program is terminated
	if (game_mode == 5)
		return 0;

	// stores a randomly selected topic by topicChooser()
	std::string topic{ topicChooser() };

	// if topicChooser() returns "error", it means the topic file couldn't be accessed
	if (topic == "error") 
	{
		std::cerr << "There has been an error while retrieving the topics\n";
		return 1;
	}

	// Word player is trying to guess. Is initialized with a random word from wordChooser().
	std::string word{ wordChooser(game_mode, topic) };

	// if wordChooser() returns "error1" that means there has been an error while opening the chosen difficulties
	// words file
	if (word == "error1") 
	{
		std::cerr << "There has been an error obtaining words!\n";
		return 1;
	}

	// if wordChooser() returns "error2" that means that the program couldn't find the topic in the selected words file
	if (word == "error2") 
	{
		std::cerr << "Topic not found in the word file!\n";
		return 1;
	}

	// main playing field, begins filled with underscores,
	// changes as the player guesses more letters
	std::string game_letters (word.size(), '_');

	// contains all the players incorrect guesses
	std::vector <char> incorrect_guesses{ };

	int tries{ 0 };

	bool game_won{ false };
	bool game_lost{ false };

	constexpr int max_tries{ 6 };

	// main playing function
	while (!game_lost && !game_won) 
	{

		bool guessed_correctly{ false };		// reset the guessed_correctly boolean since a new iteration has began

		printHangmanPicture(tries);
		std::cout << "Topic of the word: " << topic << '\n';
		std::cout << "Incorrect guesses:";
		printLetters(incorrect_guesses);
		printLetters(game_letters);


		char guess{ getGuess(incorrect_guesses, game_letters) };

		guessed_correctly = checkGuess(guess, word);
		
		if (guessed_correctly) 
		{
			std::cout << "Correct!\n";
			changeGameLetters(guess, game_letters, word);
		}

		else
		{
			std::cout << "You guessed incorrectly\n";
			incorrect_guesses.push_back(guess);
			++tries;
		}
	
		// checks if game has been lost
		if (tries >= max_tries) 
		{							 
			printHangmanPicture(tries);
			std::cout << "GAME OVER!\n";
			std::cout << "The correct word was " << word << '\n';
			game_lost = true;
		}

		// if game is not lost, checks if game is won
		else if (game_letters == word) 
		{
			printHangmanPicture(tries);
			printLetters(game_letters);
			std::cout << "Congrats! You won!\n";
			incrementScore(game_mode, guessed_easy, guessed_medium, guessed_hard);
			writeScore(guessed_easy, guessed_medium, guessed_hard);
			game_won = true;
		}
	}

	return 0;
}
#endif
