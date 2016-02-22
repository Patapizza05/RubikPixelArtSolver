#ifndef CORNERFACE_HEADER

#define CORNERFACE_HEADER

#include "Face.h"

class CornerFace : public Face {
public:
	CornerFace(int, RubikColor);
	int getCorner();
};

#endif