#ifndef WORD_CHOOSING_H
#define WORD_CHOOSING_H

#include <string>

std::string topicChooser();

// used for selecing a random word based on game_mode and topic
std::string wordChooser(int game_mode, std::string topic);

#endif