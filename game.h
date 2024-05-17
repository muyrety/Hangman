#ifndef GAME_H
#define GAME_H

#include <string>
#include <string_view>
#include <vector>

bool checkGuess(char guess, std::string_view word);

// used to change game_letters to the players guess
void changeGameLetters(char guess, std::string& game_letters, std::string_view word);

// used for checking if the letter was previously guessed
bool previouslyGuessed(char guess, std::string_view game_letters, const std::vector <char>& incorrect_guesses);

#endif
