// cwPart1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

int getRandomNumber(int maxVal);
void setSeed(int argc, char*argv[]);
void visualiseCurrentState(char * pBlankWord, int iWrongGuessesLeft, int iLettersGuessed, int iWordLength, char *arrAvailable);
void revealLetter(char * pCurrentWord, char * pBlankWord, int iWordLength, char guess, int *iLettersGuessed);
void replaceChar(char * string, char oldChar, char newChar);
void getUserGuess(char *pCurrentWord, char *pBlankWord, int iWordLength, char *arrLetters, char*arrAvailable, int *iLettersGuessed, int *iWrongGuessesLeft);
bool playAgain();
void flushInputBuffer();

int main(int argc, char*argv[])
{
	if (argc > 2) return -1; //if more than one argument passed in, return error code

	//setting the seed either as the argument if one exists, or time if one does not
	setSeed(argc, argv);

	//initialising array of words and its size
	const char * arrWordList[] = { "magenta", "red", "purple", "teal", "cherry", "white", "yellow", "blue", "azure", "black", "green", "brown", "maroon" };	//array of words
	const int iWordCount = sizeof(arrWordList) / sizeof(char *);	//count of words in the array
	
	//creating variables to hold information on the current word
	int iTargetWordIndex;	//index of currently selected word
	int iWordLength;	//length of currently selected word

	//initialising the alphabet and array of available letters
	char arrLetters[27] = "abcdefghijklmnopqrstuvwxyz";	//array of all the 26 letters
	char arrAvailable[27];	//array of 26 letters which will be removed when they have been used
	char * pCurrentWord;	// currently selected word
	char * pBlankWord;		// a copy of the word, initially all '-' characters but will be filled in with guessed letters

	int iLettersGuessed;	//number of letters guessed so far
	int iWrongGuessesLeft;	// number of wrong guesses so far

	// game loop, running forever until user exits
	while (true) {

		//setting up the round

		strcpy_s(arrAvailable, sizeof(arrLetters), arrLetters);	//initially available letters is the whole alphabet

		//get random word from the array to play with
		iTargetWordIndex = getRandomNumber(iWordCount);
		iWordLength = strlen(arrWordList[iTargetWordIndex]);	//word length = strlen (doesn't include terminal character)

		//malloc memory of correct size for the currentWord and copy the value from the array into it
		pCurrentWord = (char *)malloc(iWordLength + 1);
		strcpy_s(pCurrentWord, iWordLength + 1, arrWordList[iTargetWordIndex] + '\0');

		//malloc memory of correct size for the word to play with
		pBlankWord = (char *)malloc(iWordLength + 1);	//+1 for end string character

		//generate the blank word
		memset(pBlankWord, '-', iWordLength);
		pBlankWord[iWordLength] = '\0';

		//setting up variables for beginning of the round
		iWrongGuessesLeft = 8; //user has 8 wrong guesses left
		iLettersGuessed = 0; //user hasn't made any correct guesses yet


		// while the user hasn't lost or won this round
		while (iWrongGuessesLeft > 0 && iLettersGuessed < iWordLength) {

			visualiseCurrentState(pBlankWord, iWrongGuessesLeft, iLettersGuessed, iWordLength, arrAvailable);

			getUserGuess(pCurrentWord, pBlankWord, iWordLength, arrLetters, arrAvailable, &iLettersGuessed, &iWrongGuessesLeft);
		
		}	
		//exit loop when either player has lost or won the round
		
		// if the player has won, tell them
		if (iLettersGuessed == iWordLength) {
			printf("Well done! The word was '%s'. You finished with %i wrong guesses left.\n", pCurrentWord, iWrongGuessesLeft);
		}
		//else if the player has lost, tell them
		else if (iWrongGuessesLeft == 0) {
			printf("You failed. The word was '%s'\n", pCurrentWord);
		}

		//free the malloced memory for the word arrays
		free(pBlankWord);
		free(pCurrentWord);

		_CrtDumpMemoryLeaks(); // checking for memory leaks

		// now we have finished the game round don't want to keep user letter guesses in the input buffer so clear it
		flushInputBuffer();// ie if the user has "----n" then guesses the word "green", n will remain in input buffer and if not cleared will auto leave the program when it reaches this choice

		//if the user has chose not to play again, break the infinite game loop
		if (!playAgain()) {
			break;
		}
	}

	printf("Thank you for playing, bye!");

	return 0;
}

//function for setting the seed either to the argument if one as passed in, or the current time if not.
void setSeed(int argc, char*argv[]) {
	//if argc equals 2, we passed in a seed so use it
	if (argc == 2) {
		//so use the argument as the seed for the random number generator
		srand(atoi(argv[1]));
	}
	//else we didn't pass in any arguments (besides program name)
	else {
		// so use time as the seed for the random number generator
		srand((unsigned int) time(0));
	}
}

//function for getting random number within the specified limit
int getRandomNumber(int maxVal) {
	return rand() % maxVal;
}

//function for printing the players current state in the game
void visualiseCurrentState(char * pBlankWord, int iWrongGuessesLeft, int iLettersGuessed, int iWordLength, char *arrAvailable) {
	printf("Guess a letter for the word: '%s'\n", pBlankWord);
	printf("You have %i wrong guesses left, and have guessed %d letters out of %d so far.\n", iWrongGuessesLeft, iLettersGuessed, iWordLength);
	printf("Available letters are: %s\n", arrAvailable);
}

//function for handling the users guess
void getUserGuess(char *pCurrentWord, char *pBlankWord, int iWordLength, char *arrLetters, char*arrAvailable,  int *iLettersGuessed, int *iWrongGuessesLeft) {
	char guessedLetter;

	while (true) {
		//defaulting guessedLetter to empty
		guessedLetter = '\0';
		printf("Input char from available letters to guess: ");
		scanf_s(" %c", &guessedLetter, 1);	//set guessedLetter to input from scanf, ' ' before the '%c' to tell it to ignore white space and '\n' characters from being added to buffer
		printf("\n");

		guessedLetter = tolower(guessedLetter);

		// if this letter is not in arrLetters it is not a valid letter
		if (!strchr(arrLetters, guessedLetter)) {
			printf("'%c' is not a valid letter! Try again.\n", guessedLetter);
		}
		// else if this is a valid letter but it is not in arrAvailable it has already been guessed
		else if (!strchr(arrAvailable, guessedLetter)) {
			printf("'%c' has already been guessed! Try again.\n", guessedLetter);
		}
		// else the letter isn't invalid and hasn't been already guessed, it is valid
		else{
		
			// if the letter is in the current word..
			if (strchr(pCurrentWord, guessedLetter)) {
				printf("'%c' is in the word, correct guess!.\n\n", guessedLetter);

				// reveal correctly guessed letter to the player
				revealLetter(pCurrentWord, pBlankWord, iWordLength, guessedLetter, iLettersGuessed);
			}

			// else the letter isn't in the current word
			else {
				printf("'%c' is not in the word, wrong guess!.\n\n", guessedLetter);

				// decrement wrrong guesses left counter
				*iWrongGuessesLeft-=1;
			}

			replaceChar(arrAvailable, guessedLetter, '.');

			// break the guessing loop as a valid guess has been input
			break;
			}
	}
}

//function for revealing the letter if guessed correctly
void revealLetter(char * pCurrentWord, char * pBlankWord, int iWordLength, char guess,int *iLettersGuessed) {
	// for each letter in the current word..
	for (int i = 0; i <= iWordLength; i++) {
		// if this letter is letter guessed, reveal it to the player and increase the letters guessed counter
		if (pCurrentWord[i] == guess) {
			*iLettersGuessed += 1;
			pBlankWord[i] = guess;
		}
	}
}

//function for replacing instances of a char with a different char (used to change available letters)
void replaceChar(char * string, char oldChar, char newChar) {

	for (int i = 0; i < (signed) strlen(string); i++) {
		if (string[i] == oldChar) {
			string[i] = newChar;
		}
	}

}

//function for getting user input on whether or not they want to play again, returning the truth value.
bool playAgain() {

	char userChoice = '\0';

	while (userChoice != 'y' && userChoice != 'n') {
		printf("Try again? (y/n): ");
		scanf_s(" %c", &userChoice,1);
		userChoice = tolower(userChoice);

	}
	
	return userChoice == 'y';
}

// clears the input buffer so you don't get unexpected behaviour.
void flushInputBuffer() {
	while ((getchar()) != '\n'); // empty loop which flushes the input char
}