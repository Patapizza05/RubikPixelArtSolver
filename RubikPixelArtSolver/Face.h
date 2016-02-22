#ifndef FACE_HEADER

#define FACE_HEADER

#include "RubikColor.h"

class Face {
	public:
		Face(int,RubikColor);
		int getNumber() { return number; }
		int getLockedPosition() { return lockedPosition; }
		RubikColor getColor() { return color; }
	protected:
		int lockedPosition = -1;
		int number;
		RubikColor color;
};

#endif