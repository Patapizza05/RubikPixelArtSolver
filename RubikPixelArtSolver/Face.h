#ifndef FACE_HEADER

#define FACE_HEADER

#include "RubikColor.h"

class Face {
	public:
		Face(int,RubikColor);
		int getNumber() { return number; }
		bool getLockedPosition() { return lockedPosition; }
		void setLockedPosition(bool value);
		RubikColor getColor() { return color; }
	protected:
		bool lockedPosition = FALSE;
		int number;
		RubikColor color;
};

#endif