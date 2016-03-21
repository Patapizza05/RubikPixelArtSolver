
#ifndef RUBIK_HEADER

#define RUBIK_HEADER

#include "Face.h"
#include "CornerFace.h"
#include "EdgeFace.h"
#include "MiddleFace.h"
#include <iostream>

class Rubik {
	public:
		Rubik(int[]);
		~Rubik();
		void printCube();

		void R();
		void Ri();
		void R2();
		void L();
		void Li();
		void L2();
		void U();
		void Ui();
		void U2();
		void B();
		void Bi();
		void B2();
		void F();
		void Fi();
		void F2();
		void D();
		void Di();
		void D2();
		void resolve(RubikColor colors[]);
		void resolveMiddle(RubikColor color);
		void resolveEdges(RubikColor colors[]);
		void resolveCorners(RubikColor colors[]);
		void error();
		void changeReferentialWhiteToGreen();

		void changeReferentialWhiteToRed();
		void changeReferentialWhiteToBlue();
		void changeReferentialWhiteToOrange();
		void changeReferentialWhiteToYellow();
		
	private:
		CornerFace * corners[24];
		EdgeFace * edges[24];
		MiddleFace * middle[8];
		void addEdge(int, int);
		void addCorner(int, int);
		void addMiddle(int, int);
		void initCornersAndEdges(int[]);
		void translate(Face * array[], int i1, int i2, int i3, int i4);
		void translate(CornerFace * array[], int i1, int i2, int i3, int i4);
		void translate(EdgeFace * array[], int i1, int i2, int i3, int i4);
		void translate(MiddleFace * array[], int i1, int i2, int i3, int i4);
		void swap(Face * array[], int i1, int i2);
		void changeReferential(RubikColor color);
		void changeReferential(MiddleFace * m);
		int searchEdgeColorIndex(RubikColor color, int solvedEdges);
		bool checkEdgeColor(int, RubikColor);
		void setLockedEdge(int index, bool value);
		int searchCornerColorIndex(RubikColor color, int solvedEdges);
		bool checkCornerColor(int, RubikColor);
		void setLockedCorner(int index, bool value);
};

#endif