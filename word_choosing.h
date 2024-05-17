#ifndef WORD_CHOOSING_H
#define WORD_CHOOSING_H

#include <string>

std::string topicChooser();

// used for selecing a random word from a .txt file based on difficulty and topic
// Error codes:
// error1 - can't access the word file
// error2 - can't find the chosen topic in the word file
std::string wordChooser(int difficulty, std::string topic);

#endif