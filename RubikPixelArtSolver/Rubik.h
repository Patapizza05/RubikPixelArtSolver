
#ifndef RUBIK_HEADER

#define RUBIK_HEADER

#include "Face.h"
#include "CornerFace.h"
#include "EdgeFace.h"
#include <iostream>

class Rubik {
	public:
		Rubik(int[]);
		~Rubik();
		void printCube();
	private:
		CornerFace * corners[24];
		EdgeFace * edges[24];
		void addEdge(int, int);
		void addCorner(int, int);
		void initCornersAndEdges(int[]);
};

#endif