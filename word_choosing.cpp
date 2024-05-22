#include "constants.h"
#include "random.h"
#include <string>
#include <fstream>
#include <random>
#include <vector>

std::string topicChooser() 
{
	constexpr auto topic_file{ "topics.txt" };

	std::ifstream topic(topic_file);

	if (!topic)
		return error_code::topic_fail;
		
	// vector holding all the topics in the file
	std::vector<std::string> topics{};
	
	// garbage variable used for filling up topics vector
	std::string temp{};

	// puts strings in topics as long as there are strings to be read from topics.txt
	while (topic >> temp)
		topics.push_back(temp);

	if (topics.size() == 0)
		return error_code::topic_fail;

	// topic is a randomly chosen element from the topics vector
	return topics[Random::get<size_t>(0, topics.size() - 1)];
}

// used for selecing a random word from a .txt file based on game_mode and topic
// Error codes:
// error1 - can't access the word file
// error2 - can't find the chosen topic in the word file
std::string wordChooser(int game_mode, std::string topic) {

	// garbage value used for placing the cursor on the chosen topics words
	// and then for filling up the words vector
	std::string foo{ };

	// used for holding all the words of the player selected game_mode, of the chosen topic
	std::vector <std::string> words{ };

	// curly braces in each case to specify that these word ifstreams
	// only need to be available in the selected cases scope
	switch (game_mode) {
	case 1:
	{
		std::ifstream easy("easywords.txt");

		if (easy.fail()) {
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

		if (medium.fail()) {
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

		if (hard.fail()) {
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