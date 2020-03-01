// cwPart1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// to change arguments: right click on 'cwPart2', properties, debugging, arguments

#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>
#include <vector>
#include <string>
#include <fstream>

int getRandomNumber(int maxVal);
void visualiseCurrentState(std::string strBlankWord, int iWrongGuessesLeft, int iLettersGuessed, int iWordLength, std::string strAvailable);
void revealLetter(std::string strCurrentWord, std::string *strBlankWord, int iWordLength, char guess, int *iLettersGuessed);
void getUserGuess(std::string strCurrentWord, std::string *strBlankWord, int iWordLength, std::string strLetters, std::string *strAvailable, int *iLettersGuessed, int *iWrongGuessesLeft);
bool playAgain();
void flushInputBuffer();

std::vector<std::string> readWordList(std::string filePath);

int main(int argc, char*argv[])
{
	std::vector<std::string> vecWordList; //stores the words that are to be played with

	if (argc > 2) return -1; //if more than one argument passed in, return error code
	else if (argc == 2) vecWordList = readWordList(argv[1]); // if an argument is passed in, assume it is the link to the word list file
	else vecWordList = readWordList("wordlist.txt"); // no arguments (besides program name) passed in, use the default word file

	//setting the seed for the random number generator as the current time
	srand((unsigned int)time(0));

	const int iWordCount = vecWordList.size();	//count of words in the words list

	//creating variables to hold information on the current word
	int iTargetWordIndex;	//index of currently selected word
	int iWordLength;	//length of currently selected word

	//initialising the alphabet and array of available letters
	std::string strLetters = "abcdefghijklmnopqrstuvwxyz";	//array of all the 26 letters
	std::string strAvailable;	//array of 26 letters which will be removed when they have been used
	std::string strCurrentWord;	// currently selected word
	std::string strBlankWord;		// a copy of the word, initially all '-' characters but will be filled in with guessed letters

	int iLettersGuessed;	//number of letters guessed so far
	int iWrongGuessesLeft;	// number of wrong guesses so far

	// game loop, running forever until user exits
	while (true) {

		//setting up the round

		//initially available letters is the whole alphabet
		strAvailable = strLetters;

		//get random word from the array to play with
		iTargetWordIndex = getRandomNumber(iWordCount);
		strCurrentWord = vecWordList.at(iTargetWordIndex);
		iWordLength = strCurrentWord.size();
		strBlankWord.assign(iWordLength,'-'); //hiding the blank word by filling with '-'

		//setting up win/lose conditions for beginning of the round
		iWrongGuessesLeft = 8; //user has 8 wrong guesses left
		iLettersGuessed = 0; //user hasn't made any correct guesses yet


		// while the user hasn't lost or won this round
		while (iWrongGuessesLeft > 0 && iLettersGuessed < iWordLength) {

			visualiseCurrentState(strBlankWord, iWrongGuessesLeft, iLettersGuessed, iWordLength, strAvailable);

			getUserGuess(strCurrentWord, &strBlankWord, iWordLength, strLetters, &strAvailable, &iLettersGuessed, &iWrongGuessesLeft);

		}
		//exit loop when either player has lost or won the round

		// if the player has won, tell them
		if (iLettersGuessed == iWordLength) {
			std::cout<<"Well done! The word was "<<strCurrentWord<<". You finished with "<<iWrongGuessesLeft<<" wrong guesses left.\n";
		}
		//else if the player has lost, tell them
		else if (iWrongGuessesLeft == 0) {
			std::cout << "You failed. The word was '"<<strCurrentWord<<"'\n";
		}

		// now we have finished the game round don't want to keep user letter guesses in the input buffer so clear it
		flushInputBuffer();

		//if the user has chose not to play again, break the infinite game loop
		if (!playAgain()) {
			break;
		}
	}

	std::cout<<"Thank you for playing, bye!";

	return 0;
}

// C++ Functions

//function for getting random number within the specified limit
int getRandomNumber(int maxVal) {
	return rand() % maxVal;
}

//function for printing the players current state in the game
void visualiseCurrentState(std::string strBlankWord, int iWrongGuessesLeft, int iLettersGuessed, int iWordLength, std::string strAvailable) {
	std::cout << "Guess a letter for the word: " << strBlankWord << "\n";
	std::cout << "You have " << iWrongGuessesLeft << " wrong guesses left, and have guessed " << iLettersGuessed << " letters out of " << iWordLength << " so far.\n";
	std::cout << "Available letters are: " << strAvailable << "\n";
}


//function for handling the users guess
void getUserGuess(std::string strCurrentWord, std::string *strBlankWord, int iWordLength, std::string strLetters, std::string *strAvailable, int *iLettersGuessed, int *iWrongGuessesLeft) {
	char guessedLetter = '\0';

	while (true) {
		std::cout << "Input char from available letters to guess: ";
		std::cin >> guessedLetter;	//set guessedLetter to input from standard stream
		std::cout << "\n";

		guessedLetter = tolower(guessedLetter);

		// if this letter is not in strLetters it is not a valid letter
		if (strLetters.find(guessedLetter) == std::string::npos) {
			std::cout << "'" << guessedLetter << "' is not a valid letter! Try again.\n";
		}
		// else if this is a valid letter but it is not in arrAvailable it has already been guessed
		else if ((*strAvailable).find(guessedLetter) == std::string::npos) {
			std::cout << "'" << guessedLetter << "' has already been guessed! Try again.\n";
		}
		// else the letter isn't invalid and hasn't been already guessed, it is valid
		else {

			// if the letter is in the current word..
			if (strCurrentWord.find(guessedLetter) != std::string::npos) {
				std::cout << "'" << guessedLetter << "' is in the word, correct guess!\n";

				// reveal correctly guessed letter to the player
				revealLetter(strCurrentWord, strBlankWord, iWordLength, guessedLetter, iLettersGuessed);
			}

			// else the letter isn't in the current word
			else {
				std::cout << "'" << guessedLetter << "' is not in the word, incorrect guess!\n";

				// decrement wrrong guesses left counter
				*iWrongGuessesLeft -= 1;
			}

			(*strAvailable).at((*strAvailable).find(guessedLetter))='.';

			// break the guessing loop as a valid guess has been input
			break;
		}
	}
}

//function for revealing the letter if guessed correctly
void revealLetter(std::string strCurrentWord, std::string *strBlankWord, int iWordLength, char guess, int *iLettersGuessed) {

	// for each letter in the current word..
	for (int i = 0; i < iWordLength; i++) {
		// if this letter is letter guessed, reveal it to the player and increase the letters guessed counter
		if (strCurrentWord.at(i) == guess) {
			*iLettersGuessed += 1;
			(*strBlankWord).at(i) = guess;
		}
	}

	
}

std::vector<std::string> readWordList(std::string filePath) {
	
	std::vector<std::string> vecWordList;

	std::ifstream file(filePath);
	std::string word;

	while (std::getline(file, word)) {
		vecWordList.insert(vecWordList.begin(), word);
	}

	file.close();

	return vecWordList;
}

//function for getting user input on whether or not they want to play again, returning the truth value.
bool playAgain() {

	char userChoice ='\0';

	while (userChoice != 'y' && userChoice != 'n') {
		std::cout << "Try again? (y/n): ";
		std::cin >> userChoice;
		userChoice = tolower(userChoice);
		std::cout << "\n";

	}

	return userChoice == 'y';
}

// basic function for clearing the input buffer so its results from one section of the program do not interfere with another
void flushInputBuffer() {
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}