#include "Game.h"
#include "Board.h"
#include <stdio.h>
#include <iostream>
#include <cctype>

// Declaring a new board
Board* board; 

// Empty constructor to set default values of attributes 
Game::Game() {
	
}

// Getter for the current player
bool Game::getPlayer() {
	return this->currentPlayer;
}

// Getter for the Y-axis (row) of the player's move
char Game::getChoiceRow() {
	return this->userMove[0];
}

// Getter for the X-axis (column) of the player's move
char Game::getChoiceColumn() {
	return this->userMove[1];
}

// Setter for the player's move updating 'userMove' attribute
void Game::setUserMove(char input[3]){
	this->userMove[0] = input[0];
	this->userMove[1] = input[1];
}

// Setter for the current player playing updating 'currentPlayer' attribute
void Game::setPlayer(bool newPlayer) {
	this->currentPlayer = newPlayer;
}

int Game::requestSize() {

	// Declaring a variable to store the size of the board.
	int size;

	// Requesting input from user
	std::cout << "Enter board size (between 3 and 10): ";
	std::cin >> size;

	//  If board size chosen is not between 3 and 10
	if (!(size >= 3 && size <= 10)) {

		do {
			
			// Clear error flags
			std::cin.clear();

			// Emptying buffer
			while (getchar() != '\n');

			// Requesting user input again
			printf("Enter a correct choice:\n");
			std::cin >> size;

		} while (!(size >= 3 && size <= 10)); // Loop until size is not between 3 and 10

	}

	// Emptying buffer
	while (getchar() != '\n');

	return size;
}

char Game::requestChoice(){

	// Declaring a variable to store player 1's symbol.
	char choice;

	// Requesting input from user
	printf("Player 1, select symbol: 'X' or 'O' \n");
	std::cin >> choice;

	// Changing the input to lowercase
	choice = tolower(choice);

	//  If the symbol is not an 'x' or an 'o' (upper or lowercase)
	if (!(choice == 'x' ||  choice == 'o')) {

		do {

			// Emptying buffer
			while (getchar() != '\n');

			// Requesting input from user
			printf("Enter a correct choice:\n");
			std::cin >> choice;

			// Changing the input to lowercase
			choice = tolower(choice);
		
		// Keep looping until the symbol is not an 'x' or an 'o' (upper or lowercase)
		} while (!(tolower(choice) == 'x' || tolower(choice) == 'o'));

	}

	// Emptying buffer
	while (getchar() != '\n');

	if (choice == 'x') {
		return 1; // Returning 1 corresponding to cell type 1 ('X')

	}else if(choice == 'o') {
		return 2; // Returning 2 corresponding to cell type 2 ('O')
	}

}

void Game::requestMove() {

	// Creating a string to store a player's move
	char move[3];

	// Requesting input from user
	printf("Player %d's move: ",this->getPlayer()+1);
	std::cin.get(move, sizeof(move));

	// Converting the alphabetic part from an ASCII value to its corresponding numeric index
	move[0] = tolower(move[0]) - 'a';

	// Converting the numeric part from an ASCII value to its corresponding numeric index
	move[1] = move[1] - '0';

	// If it is not true that: alphabetic part is between 0 and the board size, the numeric part is also between 0 and the board size and the cell is unfilled
	if (!((move[0] >= 0 && move[0] < 0 + board->getSize()) && (move[1] >= 0 && move[1] < 0 + board->getSize()) && board->getEntry(move[0],move[1]).getType() == 0)) {
		do {

			// Clear error flags
			std::cin.clear();

			// Emptying buffer
			while (getchar() != '\n');

			// If the move chosen is incorrect
			if (!((move[0] >= 0 && move[0] < 0 + board->getSize()) && (move[1] >= 0 && move[1] < 0 + board->getSize()))) {
				printf("Enter a correct choice: ");
			}else{
				printf("Cell already filled. Try again: ");
			}	

			// Requesting input from user
			std::cin.get(move, sizeof(move));

			// Converting the alphabetic part from an ASCII value to its corresponding numeric index
			move[0] = tolower(move[0]) - 'a';

			// Converting the numeric part from an ASCII value to its corresponding numeric index
			move[1] = move[1] - '0';


			// Keep looping while it is not true that: alphabetic part is between 0 and the board size, the numeric part is also between 0 and the board size and the cell is unfilled
		} while (!((move[0] >= 0 && move[0] < 0 + board->getSize()) && (move[1] >= 0 && move[1] < 0 + board->getSize()) && board->getEntry(move[0], move[1]).getType() == 0));

	}

	// Emptying buffer
	while (getchar() != '\n');

	// Updating 'userMove' attribute with the player's coordinates
	this->setUserMove(move);

}

void Game::updateGameState(int* currPlayerRows, int* currPlayerCols, int* currPlayerDiag, int* p2Rows, int* p2Cols, int* p2Diag) {
	
	// If opponent hasn't already played in the row
	if (*(p2Rows + this->getChoiceRow()) == 0) {
		(*(currPlayerRows + this->getChoiceRow()))++; // Increment the current player's number of symbols in that row
	
	}else{
		// Set both players' number of symbols in that row to -1 (unwinnable row)
		*(currPlayerRows + this->getChoiceRow()) = -1; 
		*(p2Rows + this->getChoiceRow()) = -1;
	}

	// If player has played on the leading diagonal
	if (this->getChoiceRow() == this->getChoiceColumn()) {

		// If opponent hasn't already played in it
		if (*p2Diag == 0)
			(*currPlayerDiag)++; // Increment the current player's number of symbols in the diagonal
		else {
			// Set both players' number of symbols in that diagonal to -1 (unwinnable diagonal)
			*currPlayerDiag = -1;
			*p2Diag = -1;
		}
	}

	// If player has played on the antidiagonal
	if (this->getChoiceRow() == board->getSize() - this->getChoiceColumn() - 1) {

		// If opponent hasn't already played in it
		if (*(p2Diag + 1) == 0)
			(*(currPlayerDiag + 1))++; // Increment the current player's number of symbols in the diagonal
		else {
			// Set both players' number of symbols in that diagonal to -1 (unwinnable diagonal)
			*(currPlayerDiag + 1) = -1;
			*(p2Diag + 1) = -1;
		}
	}

	// If opponent hasn't already played in the column
	if (*(p2Cols + this->getChoiceColumn()) == 0) {
		(*(currPlayerCols + this->getChoiceColumn()))++; // Increment the current player's number of symbols in that column
	
	}else{

		// Set both players' number of symbols in that column to -1 (unwinnable diagonal)
		*(currPlayerCols + this->getChoiceColumn()) = -1;
		*(p2Cols + this->getChoiceColumn()) = -1;
	}
}

void Game::makeMove(int type, int* currPlayerRows, int* currPlayerCols, int* currPlayerDiag, int* p2Rows, int* p2Cols, int* p2Diag) {

	// Updating the entry chosen by the player to the player's corresponding symbol
	board->setEntry(this->getChoiceRow(), this->getChoiceColumn(), type);

	// Updating the state of the game
	this->updateGameState(currPlayerRows, currPlayerCols, currPlayerDiag, p2Rows, p2Cols, p2Diag);

	// Displaying the updated board to the user 
	board->display();

}

int Game::checkWin(int* currPlayerRows, int* currPlayerCols, int* currPlayerDiag){

	int isWon = 0; // Declaring a variable to keep track if a player has won or tied
	int tie = 0; // Declaring a variable to keep track if game has tied

	// If current player has the same number of symbols in either diagonal as the board size
	if (*currPlayerDiag == board->getSize() || *(currPlayerDiag + 1) == board->getSize()) {
		isWon = 1; // Updating isWon variable to represent that the game has been won
		return isWon;
	}

	// Looping through the board length
	for (int i = 0; i < board->getSize(); i++) {

		// If current player has any row or any column with the same number of symbols as the board size
		if (*(currPlayerRows + i) == board->getSize() || *(currPlayerCols + i) == board->getSize()) {
			isWon = 1; // Updating isWon variable to represent that the game has been won
			break;
		}

		// If current row is unwinnable (-1);
		if (*(currPlayerRows + i) == -1) {
			tie++;
		}

		// If current column is unwinnable (-1);
		if (*(currPlayerCols + i) == -1) {
			tie++;
		}

		// If tie counter is equal to number of rows + columns (meaning all columns and rows are unwinnable)
		// and both diagonals are unwinnable
		if (tie == board->getSize() * 2 && *currPlayerDiag == -1 && *(currPlayerDiag + 1) == -1) {
			isWon = 2; // Updating isWon variable to represent that the game has tied
			break;
		}
	}

	return isWon;
}

int Game::run() {

	std::cout << "\t\t\t**********************************************************\n";
	std::cout << "\t\t\t*                     TIC TAC TOE                        *\n";
	std::cout << "\t\t\t*                                                        *\n";
	std::cout << "\t\t\t**********************************************************\n\n\n\n";

	// Initialising a board to the size specified by the user
	board = new Board(requestSize());

	int* p1Rows = (int*)malloc(sizeof(int) * board->getSize()); // Allocating memory for an array counting player 1's symbol in each row
	int* p1Cols = (int*)malloc(sizeof(int) * board->getSize()); // Allocating memory for an array counting player 1's symbol in each column
	int* p2Rows = (int*)malloc(sizeof(int) * board->getSize()); // Allocating memory for an array counting player 2's symbol in each row
	int* p2Cols = (int*)malloc(sizeof(int) * board->getSize()); // Allocating memory for an array counting player 2's symbol in each column

	//  If memory allocation fails
	if (p1Rows == NULL || p1Cols == NULL || p2Rows == NULL || p2Cols == NULL)
	{
		// Freeing all allocated memory for the board
		board->~Board();
		free(p1Rows);
		free(p1Cols);
		free(p2Rows);
		free(p2Cols);
		return EXIT_FAILURE;
	}

	// Initialising all arrays to 0
	for (int i = 0; i < board->getSize(); i++) {
		*(p1Rows + i) = 0;
		*(p1Cols + i) = 0;
		*(p2Rows + i) = 0;
		*(p2Cols + i) = 0;
	}

	int diagonalPlayer1[2] = { 0,0 }; // Creating an array to count player 1's symbols in each diagonal
	int diagonalPlayer2[2] = { 0,0 }; // Creating an array to count player 2's symbols in each diagonal

	// Obtaining player 1's symbol
	char player1Symbol = requestChoice();

	// Creating a variable to set player 2's symbol accordingly
	char player2Symbol = 0;

	if (player1Symbol == 1) {

		player2Symbol = 2;

	}else if(player1Symbol == 2) {

		player2Symbol = 1;
	}

	// Displaying the board to the user for the first time
	board->display();

	do{

		// Setting player 1 as current player
		this->setPlayer(0);

		// Requesting a move
		this->requestMove();

		// Applying the move with player 1's symbol
		this->makeMove(player1Symbol, p1Rows, p1Cols, diagonalPlayer1, p2Rows, p2Cols, diagonalPlayer2);

		// Checking if player 1 has won or game is tied
		int win = this->checkWin(p1Rows, p1Cols, diagonalPlayer1);
		if (win == 1) {
			printf("Player 1 has won!");
			// Freeing all allocated memory for the board
			board->~Board();
			free(p1Rows);
			free(p1Cols);
			free(p2Rows);
			free(p2Cols);
			return EXIT_SUCCESS;
		}
		else if (win == 2) {
			printf("It's a tie!");
			// Freeing all allocated memory for the board
			board->~Board();
			free(p1Rows);
			free(p1Cols);
			free(p2Rows);
			free(p2Cols);
			return EXIT_SUCCESS;
		}

		// Setting player 2 as current player
		this->setPlayer(1);

		// Requesting a move
		this->requestMove();
		
		// Applying the move with player 2's symbol
		this->makeMove(player2Symbol, p2Rows, p2Cols, diagonalPlayer2, p1Rows, p1Cols, diagonalPlayer1); //change 7

		// Checking if player 2 has won or game is tied
		win = this->checkWin(p2Rows, p2Cols, diagonalPlayer2);
		if (win == 1) {
			printf("Player 2 has won!");
			// Freeing all allocated memory for the board
			board->~Board();
			free(p1Rows);
			free(p1Cols);
			free(p2Rows);
			free(p2Cols);
			return EXIT_SUCCESS;
		}
		else if (win == 2) {
			printf("It's a tie!");
			// Freeing all allocated memory for the board
			board->~Board();
			free(p1Rows);
			free(p1Cols);
			free(p2Rows);
			free(p2Cols);
			return EXIT_SUCCESS;
		}

	} while (true); // Infinite loop until an if statement breaks the loop


}

