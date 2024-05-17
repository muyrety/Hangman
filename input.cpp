// used for obtaining a valid guess from the user (only 1 character - a letter, not previously guessed)
char getValidGuess(std::vector<char> incorrect_guesses, std::string game_letters) {

	char guess{};
	// request an input
	std::cout << "Enter a letter\n";
	std::cin >> guess;

	while (true) {

		// if player guessed more than one character (next character in the input buffer isn't \n)
		if (std::cin.peek() != '\n') {
			std::cout << "You can only guess 1 character at a time! Try again.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// 1. clear the input buffer
			std::cin >> guess;													// 2. get a new guess
			continue;															// 3. check if the new guess is valid
		}

		// if player didn't guess a letter
		if (!std::isalpha(guess)) {
			std::cout << "You must input a letter! Try again.\n";
			std::cin >> guess;													// 1. get a new guess
			continue;															// 2. check if the new guess is valid
		}

		// if player guessed an uppercase letter, convert it to lowercase (this is only reached if player
		// guessed only a single character and it is a letter)
		if (std::isupper(guess))
			guess = static_cast<char>(std::tolower(guess));

		// if players guess was guessed before
		if (previouslyGuessed(guess, game_letters, incorrect_guesses)) {
			std::cout << "You already guessed this letter! Try again.\n";
			std::cin >> guess;													// 1. get a new guess
			continue;															// 2. check if the new guess is valid
		}

		// if it reaches here, guess must be valid (player guessed only one character
		// that is a letter, not previously guessed)
		return guess;
	}
}

// used to obtain a valid difficulty value from the user
int getDifficulty() {

	int difficulty{ };

	std::cin >> difficulty;

	// while players input is an integer outside of the specified range or is not an integer
	while (difficulty < 1 || difficulty > 5 || std::cin.fail()) {

		if (std::cin.fail()) {
			std::cin.clear();													// clear std::cin's error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// clear the input buffer
		}

		std::cout << "Please enter a valid value\n";							// ask for a new guess
		std::cin >> difficulty;
	}
	return difficulty;
}