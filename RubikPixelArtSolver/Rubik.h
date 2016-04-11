
#ifndef RUBIK_HEADER

#define RUBIK_HEADER

#include "Face.h"
#include "CornerFace.h"
#include "EdgeFace.h"
#include "MiddleFace.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

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


class Rubik {
	public:
		Rubik(int[]);
		~Rubik();
		void printCube();
		static bool Rubik::debug;
		bool checkRubik(RubikColor colors[]);

		void R(bool = TRUE);
		void Ri(bool = TRUE);
		void R2(bool = TRUE);
		void L(bool = TRUE);
		void Li(bool = TRUE);
		void L2(bool = TRUE);
		void U(bool = TRUE);
		void Ui(bool = TRUE);
		void U2(bool = TRUE);
		void B(bool = TRUE);
		void Bi(bool = TRUE);
		void B2(bool = TRUE);
		void F(bool = TRUE);
		void Fi(bool = TRUE);
		void F2(bool = TRUE);
		void D(bool = TRUE);
		void Di(bool = TRUE);
		void D2(bool = TRUE);
		void resolve(RubikColor colors[]);
		void resolveMiddle(RubikColor color);
		void resolveEdges(RubikColor colors[]);
		void resolveCorners(RubikColor colors[]);
		void error(std::string);
		void changeReferentialWhiteToGreen();

		void changeReferentialWhiteToRed();
		void changeReferentialWhiteToBlue();
		void changeReferentialWhiteToOrange();
		void changeReferentialWhiteToYellow();

		void optimise();

		std::vector<std::string> getMoves() { return moves; }
		
	private:
		CornerFace * corners[24];
		EdgeFace * edges[24];
		MiddleFace * middle[8];
		std::vector<std::string> moves;
		std::map<std::string, std::string> movesDictionary;
		void addMove(std::string);
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
		void middle_TurnCubeUp();
		void middle_TurnCubeRight();
		void middle_TurnCubeDown();
		void middle_TurnCubeLeft();
		int searchMiddleColorIndex(RubikColor color);
		bool checkMiddleColor(int, RubikColor);
		int shortenMoves(int);
};

#endif