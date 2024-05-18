#ifndef DISPLAY_H
#define DISPLAY_H

#include <string_view>
#include <vector>

void printHangmanPicture(int tries);

// prints elements of a string with spaces in between
void printLetters(std::string_view letters);

// prints elements of a vector with spaces in between
void printLetters(const std::vector <char>& letters);

void printScore(int guessed_easy, int guessed_medium, int guessed_hard);

void titleScreen(int guessed_easy, int guessed_medium, int guessed_hard);

#endif