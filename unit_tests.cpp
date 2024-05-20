#include "unit_tests.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include <cassert>
#include <string>
#include <vector>

void testcheckGuess()
{

#ifdef NDEBUG
	std::cerr << "NDEBUG is defined (asserts compiled out), tests can't be run\n";
	std::abort();
#endif

	assert(!checkGuess('a', "hello"));
	assert(!checkGuess('0', "dog"));
	assert(checkGuess('p', "alpha"));
	assert(checkGuess('e', "eel"));
	assert(!checkGuess(' ', "cat"));
	assert(!checkGuess('j', ""));
	assert(checkGuess('h', "h6"));
	assert(!checkGuess('7', "654"));
}

void testchangeGameLetters()
{

#ifdef NDEBUG
	std::cerr << "NDEBUG is defined (asserts compiled out), tests can't be run\n";
	std::abort();
#endif

	std::string test1{ "" };
	changeGameLetters('a', test1, "");
	assert(test1 == "");

	std::string test2{ "__ph_be_" };
	changeGameLetters('a', test2, "alphabet");
	assert(test2 == "a_phabe_");

	std::string test3{ "p_g" };
	changeGameLetters('i', test3, "pig");
	assert(test3 == "pig");

	std::string test4{ "1235" };
	changeGameLetters('k', test4, "1235");
	assert(test4 == "1235");

	std::string test5{ "_845_" };
	changeGameLetters('g', test5, "g845u");
	assert(test5 == "g845_");

	std::string test6{ "_" };
	changeGameLetters('g', test6, "b");
	assert(test6 == "_");

	std::string test7{ "    " };
	changeGameLetters('j', test7, " 5j ");
	assert(test7 == "  j ");

}

void testpreviouslyGuessed()
{

#ifdef NDEBUG
	std::cerr << "NDEBUG is defined (asserts compiled out), tests can't be run\n";
	std::abort();
#endif

	std::vector<char> test1{ 'h', 'j' };
	assert(!previouslyGuessed('i', "hell_", test1));

	std::vector<char> test2{};
	assert(!previouslyGuessed('j', "", test2));

	std::vector<char> test3{ 'k' };
	assert(previouslyGuessed('g', "g", test3));

	std::vector<char> test4{ '3', '1' };
	assert(!previouslyGuessed('j', "1o", test4));

	std::vector<char> test5{ 'a', 'b', 'q' };
	assert(!previouslyGuessed('y', "   ", test5));

}

void testgetGuess()
{
	constexpr char exitValue{ 'p' };
	std::vector<char> test{ 'h', 'j', 'a', '5', '7' , '\n' };
	char guess{};
	do
	{
		guess = getGuess(test, " e1z");
	} while (guess != exitValue);
}

void testgetGameMode()
{
	constexpr int exitValue{ 5 };
	int gameMode{};
	do
	{
		gameMode = getGameMode();
	} while (gameMode != exitValue);
}

void testincrementScore()
{
	int guessed_easy1{ 8 };
	int guessed_medium1{ 7 };
	int guessed_hard1{ 99 };
	incrementScore(2, guessed_easy1, guessed_medium1, guessed_hard1);
	assert(guessed_medium1 == 8);

	int guessed_easy2{ -8 };
	int guessed_medium2{ 48 };
	int guessed_hard2{ -771 };
	incrementScore(1, guessed_easy2, guessed_medium2, guessed_hard2);
	assert(guessed_easy2 == -7);

	int guessed_easy3{ 8 };
	int guessed_medium3{ 7 };
	int guessed_hard3{ 99 };
	incrementScore(3, guessed_easy3, guessed_medium3, guessed_hard3);
	assert(guessed_hard3 == 100);

	// Fail cases:
	// incrementScore(4, guessed_easy1, guessed_medium1, guessed_hard1);
	// incrementScore(0, guessed_easy1, guessed_medium1, guessed_hard1);
}