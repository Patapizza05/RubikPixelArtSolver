#include "Face.h"

#ifndef EDGEFACE_HEADER

#define EDGEFACE_HEADER

class EdgeFace : public Face {
public:
	EdgeFace(int, RubikColor);
	int getEdge();
};

#endif