#include "Face.h"

Face::Face(int number, RubikColor color) {
	this->number = number;
	this->color = color;
}

void Face::setLockedPosition(bool value)  
{ 
	lockedPosition = value; 
}