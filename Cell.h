#pragma once

class Cell
{

// Declaring attributes for a cell object
private: 

	unsigned char positionX = 0; // Giving the cell an x coordinate.
	unsigned char positionY = 0; // Giving the cell a y coordinate.
	unsigned char type = 0; // Giving the cell a type (0 = empty, 1 = 'x', 2 = 'o')

public:
	
	// Default constructor
	Cell(); 

	// Parameterised constructor
	Cell(unsigned char posY, unsigned char posX, unsigned char newType);

	// Declaring the getter for type attribute
	int getType();

	// Declaring the setter for type attribute
	void setType(int newType);

};