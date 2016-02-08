#ifndef RUBIK_HEADER
#define RUBIK_HEADER

#include "Face.h"
#include "CornerFace.h"
#include <iostream>

class Rubik {
	public:
		Rubik();
		void printCube();
	private:
		CornerFace corners[24];
		Face edges[24];
};

#endif