
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

		void R();
		void Ri();
		//void R2();
		void L();
		void Li();
		//void L2();
		void U();
		void Ui();
		//void U2();
		void B();
		void Bi();
		//void B2();
		void F();
		void Fi();
		//void F2();
		void D();
		void Di();
		//void D2();
		CornerFace * corners[24];
		void translate(Face * array[], int i1, int i2, int i3, int i4);
	private:
		
		EdgeFace * edges[24];
		void addEdge(int, int);
		void addCorner(int, int);
		void initCornersAndEdges(int[]);
		
};

#endif