#pragma once

#include <stdio.h>

class Game
{

// Declaring attributes for a cell object
private:

	bool currentPlayer = 0; // Giving the game a way to track which player is now playing.
	char userMove[2] = {'0','0'}; // Giving the game a way to track a player's next move.

public:

	// Default constructor
	Game();

	// Declaring the getters for each attribute:
	bool getPlayer();
	char getChoiceColumn();
	char getChoiceRow();

	// Declaring the setters for each attribute:
	void setPlayer(bool newPlayer);
	void setUserMove(char input[3]);

	// Declaring a method to ask the user the size of the board to play on.
	int requestSize();

	// Declaring a method to ask player 1 whether to use an 'x' or an 'o'.
	char requestChoice();

	// Declaring a method to ask a player which entry in the board to fill.
	void requestMove();

	// Declaring a method to update the values of arrays keeping track of the game state.
	void updateGameState(int* currPlayerRows, int* currPlayerCols, int* currPlayerDiag, int* p2Rows, int* p2Cols, int* p2Diag);

	// Declaring a method to fill an 'x' or 'o' in the board.
	void makeMove(int type, int* currPlayerRows, int* currPlayerCols, int* currPlayerDiag, int* p2Rows, int* p2Cols, int* p2Diag);

	// Declaring a method to check if a player has won the game or tied.
	int checkWin(int* currPlayerRows, int* currPlayerCols, int* currPlayerDiag);

	// Declaring a method to execute the Tic Tac Toe game.
	int run();

};