#ifndef OUTPUT_H
#define OUTPUT_H

#include <string_view>
#include <vector>

// prints out a picture of the hangman based on how many incorrect guesses have been made
void printHangmanPicture(int tries);

// prints the playing letters into the console
void printLetters(std::string_view game_letters);

// prints incorrectly guessed letters into the console
void printLetters(const std::vector <char>& incorrect_guesses);

// used for writing the score to score.txt
void writeScore(int guessed_easy, int guessed_medium, int guessed_hard);

// used for printing players score to console
void printScore(int guessed_easy, int guessed_medium, int guessed_hard);

// used to display the title screen
void titleScreen(int guessed_easy, int guessed_medium, int guessed_hard);

#endif