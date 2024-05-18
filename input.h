#ifndef INPUT_H
#define INPUT_H

#include <string_view>
#include <vector>

// used for obtaining a valid guess from the user (only 1 character - a letter, not previously guessed)
char getValidGuess(const std::vector<char>& incorrect_guesses, std::string_view game_letters);

// used to obtain a valid difficulty value from the user
int getDifficulty();

#endif