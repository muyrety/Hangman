#ifndef IO_H
#define IO_H

#include <string_view>
#include <vector>

// prints out a picture of the hangman based on how many incorrect guesses have been made
void printHangmanPicture(int tries);

// prints the playing letters into the console
void printLetters(std::string_view game_letters);

// prints incorrectly guessed letters into the console
void printIncorrectLetters(const std::vector <char>& incorrect_guesses);

#endif