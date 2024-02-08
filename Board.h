#pragma once

#include "Cell.h"

class Board
{

// Declaring attributes for a board object
private:

    int size; // Giving the board a size
    Cell** entries; // Giving the board a 2D structure of cells.

public:

    // Default constructor
    Board();

    // Parameterised constructor
    Board(int size); 

    // Destructor
    ~Board();

    // Declaring the getters for required attributes
    int getSize();
    Cell getEntry(char posY, char posX);

	// Declaring the setter for a specific entry in entries attribute
    void setEntry(char posY, int posX, int type);

    // Declaring a method to display the board
    void display();
};