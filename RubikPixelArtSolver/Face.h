#ifndef FACE_HEADER

#define FACE_HEADER

#include "RubikColor.h"

#define _R "R"
#define _Ri "Ri"
#define _R2 "R2"
#define _L "L"
#define _Li "Li"
#define _L2 "L2"
#define _U "U"
#define _Ui "Ui"
#define _U2 "U2"
#define _B "B"
#define _Bi "Bi"
#define _B2 "B2"
#define _F "F"
#define _Fi "Fi"
#define _F2 "F2"
#define _D "D"
#define _Di "Di"
#define _D2 "D2"

class Face {
	public:
		Face(int,RubikColor);
		int getNumber() { return number; }
		void setNumber(int);
		bool getLockedPosition() { return lockedPosition; }
		void setLockedPosition(bool value);
		RubikColor getColor() { return color; }
	protected:
		bool lockedPosition = FALSE;
		int number;
		RubikColor color;
};

#endif