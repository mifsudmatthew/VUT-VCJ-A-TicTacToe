#include "Board.h"
#include <stdio.h>
#include <stdlib.h>
	
	// Default constructor initialising a board of size 3x3 (using a an array of pointers to an array)
	Board::Board() {

		this->size = 3; // Setting default board size to 3

		this->entries = new Cell *[size](); // Allocating an array of cell pointers

		// Looping through the array
		for (int i = 0; i < size; i++) {
			this->entries[i] = new Cell[size]();  // Allocating memory for an array of cells
		}

		for (int i = 0; i < size; i++) { // Looping through each column
			for (int j = 0; j < size; j++) { // Looping through each row
				this->entries[j][i] = Cell(j, i, 0);  // Initialising each cell object
			}
		}
	}

	// Parameterised constructor initialising a board of custom size (using a an array of pointers to an array)
	Board::Board(int size) {

		this->size = size;

		this->entries = new Cell * [size](); // Allocating an array of cell pointers

		// Looping through the array
		for (int i = 0; i < size; i++) {
			this->entries[i] = new Cell[size]();  // Allocating memory for an array of cells
		}

		for (int i = 0; i < size; i++) { // Looping through each column
			for (int j = 0; j < size; j++) { // Looping through each row
				this->entries[j][i] = Cell(j, i, 0);  // Initialising each cell object
			}
		}
	}

	Board::~Board() {
		// Deallocating memory for each array of cells
		for (int i = 0; i < size; i++) {
			delete[] entries[i];
		}
		// Deallocating memory for the array of cell pointers
		delete[] entries;
	}

	// Getter for the size of the board
	int Board::getSize() {
		return this->size;
	}

	// Getter for a specific entry of the board
	Cell Board::getEntry(char posY, char posX) {
		return this->entries[posY][posX];
	}

	// Setter to update a specific entry in the boasrd
	void Board::setEntry(char posY, int posX, int type) {
		this->entries[posY][posX].setType(type);
	};

	// A method to display the board to the user
	void Board::display() {

		system("CLS"); // Clearing the console

		for (int i = -1; i < this->getSize(); i++) { // Looping through each row

			for (int j = -1; j < this->getSize(); j++) { // Looping through each column

				// Using -1 to define the border of the board

				if (i == -1){

					if (j == -1) { // In the top left corner
						printf("\t");
					}else{ 
						printf(" %d\t", j); // Display the column numbers
					}

				}else if (j == -1){ // In the border column
					printf("%c\t", 'A' + i);

				}else{

					Cell tempCell = this->getEntry(i, j); // Obtain the current entry in the board

					// Displaying the cell according to its type

					if (tempCell.getType() == 0) {

						printf("| |\t");

					}else if (tempCell.getType() == 1) {

						printf("|X|\t");

					}else if (tempCell.getType() == 2) {

						printf("|O|\t");

					}
				}

			}
			printf("\n");

			// Displaying 3 lines between the cells
			for (int k = 0; k < this->getSize(); k++) {
				printf("\t---");
			}

			printf("\n");
		}
	}
