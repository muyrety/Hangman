#ifndef INPUT_H
#define INPUT_H

#include <string_view>
#include <vector>

// used for obtaining a valid guess from the user
char getGuess(const std::vector<char>& incorrect_guesses, std::string_view game_letters);

// used to obtain a valid game_mode from the user
int getGameMode();

#endif