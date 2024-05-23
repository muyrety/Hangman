#include "word_choosing.h"
#include "constants.h"
#include "random.h"
#include <cassert>
#include <cstddef>
#include <string>
#include <fstream>
#include <vector>

static std::string getFileName(int game_mode)
{
	assert(game_mode >= 1 && game_mode <= 3);

	constexpr auto easy_word_file{ "easywords.txt" };
	constexpr auto medium_word_file{ "mediumwords.txt" };
	constexpr auto hard_word_file{ "hardwords.txt" };

	switch (game_mode)
	{
	case 1:
		return easy_word_file;
	case 2:
		return medium_word_file;
	case 3:
		return hard_word_file;
	}
	return "";		// shouldn't be possible to reach this
}

// returns true on success, false on failure
static bool getToLine(std::ifstream& in, std::string_view line)
{
	std::string temp{};
	while (std::getline(in >> std::ws, temp))
	{
		if (temp == line)
			return true;
	}
	return false;
}

std::string topicChooser() 
{
	constexpr auto topic_file{ "topics.txt" };

	std::ifstream topic{ topic_file };

	// if file can't be opened
	if (!topic)
		return error_code::topic_fail;
		
	// vector holding all the topics in the file
	std::vector<std::string> topics{};
	
	// temporary variable used for filling up topics vector
	std::string temp{};

	// puts strings in topics as long as there are strings to be read from topics.txt
	while (topic >> temp)
		topics.push_back(temp);

	if (topics.size() == 0)		// if no topics could be read into the vector
		return error_code::topic_fail;

	// topic is a randomly chosen element from the topics vector
	return topics[Random::get<std::size_t>(0, topics.size() - 1)];
}

// used for selecing a random word based on game_mode and topic
std::string wordChooser(int game_mode, std::string topic) 
{
	std::ifstream word{ getFileName(game_mode) };

	if (!word)
		return error_code::word_fail;

	if (!getToLine(word, "TOPIC: " + topic))
		return error_code::word_topic_not_found;

	std::vector <std::string> words{};
	std::string temp{};

	// used for filling words vector with words in between the selected topics name and next topic label
	while (word >> temp) 
	{
		if (temp == "TOPIC:")
			break;
		
		words.push_back(temp);
	}

	if (words.size() == 0)	// if no words could be read
		return error_code::word_fail;

	// the selected word is a randomly chosen element from the words vector
	return words[Random::get<std::size_t>(0, words.size() - 1)];
}