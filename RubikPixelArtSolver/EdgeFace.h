
#ifndef EDGEFACE_HEADER

#define EDGEFACE_HEADER

#include "Face.h"

class EdgeFace : public Face {
public:
	EdgeFace(int, RubikColor);
	int getEdge();
};

#endif