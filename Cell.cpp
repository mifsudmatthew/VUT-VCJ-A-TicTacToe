#include "Cell.h"

	// Default constructor setting default values of attributes 
	Cell::Cell() {

	};

	// Default constructor setting values of attributes according to parameters
	Cell::Cell(unsigned char posY, unsigned char posX, unsigned char newType) {

		this->positionX = posX;
		this->positionY = posY;
		this->type = newType;

	}

	// Getter for a cell's type
	int Cell::getType() {
		return this->type;
	};

	// Setter for a cell's type
	void Cell::setType(int newType) {
		this->type = newType;
	};
