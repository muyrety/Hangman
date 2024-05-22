#include "constants.h"
#include "random.h"
#include <cstddef>
#include <string>
#include <fstream>
#include <random>
#include <vector>

std::string topicChooser() 
{
	constexpr auto topic_file{ "topics.txt" };

	std::ifstream topic(topic_file);

	// if file can't be opened
	if (!topic)
		return error_code::topic_fail;
		
	// vector holding all the topics in the file
	std::vector<std::string> topics{};
	
	// garbage variable used for filling up topics vector
	std::string temp{};

	// puts strings in topics as long as there are strings to be read from topics.txt
	while (topic >> temp)
		topics.push_back(temp);

	if (topics.size() == 0)		// if no topics could be read into the file
		return error_code::topic_fail;

	// topic is a randomly chosen element from the topics vector
	return topics[Random::get<size_t>(0, topics.size() - 1)];
}

// used for selecing a random word based on game_mode and topic
std::string wordChooser(int game_mode, std::string topic) 
{
	constexpr auto easy_word_file{ "easywords.txt" };
	constexpr auto medium_word_file{ "mediumwords.txt" };
	constexpr auto hard_word_file{ "hardwords.txt" };

	// garbage value used for placing the cursor on the chosen topics words
	// and then for filling up the words vector
	std::string foo{};

	// used for holding all the words of the player selected game_mode, of the chosen topic
	std::vector <std::string> words{};

	// curly braces in each case to specify that these word ifstreams
	// only need to be available in the selected cases scope
	switch (game_mode) 
	{
	case 1:
	{
		std::ifstream easy(easy_word_file);

		if (!easy) 
			return "error1";
		
		// used for reading the file until selected topic is reached
		do 
		{
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

	// the selected word is a randomly chosen element from the words vector
	return words[Random::get<std::size_t>(0, words.size() - 1)];
}