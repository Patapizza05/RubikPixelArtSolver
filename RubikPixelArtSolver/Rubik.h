
#ifndef RUBIK_HEADER

#define RUBIK_HEADER

#include "Face.h"
#include "CornerFace.h"
#include "EdgeFace.h"
#include "MiddleFace.h"
#include "Robot.h"
#include "RobotState.h"
#include "RubikColor.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "HumanSolver.h"
#include "RobotSolver.h"

typedef void(Rubik::*pfunc)(bool);

struct Offset {
	int x;
	int y;
};

class Rubik {
	public:
		Rubik(std::vector<std::vector<int>>&);
		Rubik(int[]);
		~Rubik();
		void printCube();
		static bool Rubik::debug;
		bool checkRubik(RubikColor colors[]);

		void R(bool = true);
		void Ri(bool = true);
		void R2(bool = true);
		void L(bool = true);
		void Li(bool = true);
		void L2(bool = true);
		void U(bool = true);
		void Ui(bool = true);
		void U2(bool = true);
		void B(bool = true);
		void Bi(bool = true);
		void B2(bool = true);
		void F(bool = true);
		void Fi(bool = true);
		void F2(bool = true);
		void D(bool = true);
		void Di(bool = true);
		void D2(bool = true);

		void changeReferential(RubikColor color);

		void resolve(RubikColor colors[]);
		void resolve(RubikColor colors[], Robot * pRobot);

		void error(std::string);

		void optimise();
		
		void applyMoves(std::vector<std::string>&);
		void applyMove(std::string);
		
		std::vector<std::string> getMoves() { return moves; }

		void middle_TurnCubeUp();
		void middle_TurnCubeRight();
		void middle_TurnCubeDown();
		void middle_TurnCubeLeft();
		
		CornerFace * corners[24];
		EdgeFace * edges[24];
		MiddleFace * middle[8];

		void setLockedEdge(int index, bool value);
		void setLockedCorner(int index, bool value);

		std::vector<std::string> moves;

	private:
		static int lines[9][12];
		std::map<std::string, std::string> movesDictionary;
		std::map<std::string, pfunc> movesFunctions;

		void initMovesDictionary();
		struct Offset getOffset(int);
		void addMove(std::string);
		void addEdge(int, int);
		void addCorner(int, int);
		void addMiddle(int, int);
		void addCornerColor(int, RubikColor);
		void addEdgeColor(int, RubikColor);
		void addMiddleColor(int, RubikColor);
		void computeFaceLabels();
		void computeAllEdgeFaceLabels();
		void computeEdgeFaceLabels(int);
		std::vector<int> getPossibleEdgeNumbersFromColor(RubikColor);

		void computeAllCornerFaceLabels();
		void computeCornerFaceLabels(int);
		std::vector<int> getPossibleCornerNumbersFromColor(RubikColor);

		void initCornersAndEdges(int[]);
		void initCornersAndEdges(std::vector<std::vector<int>>&);
		void translate(Face * array[], int i1, int i2, int i3, int i4);
		void translate(CornerFace * array[], int i1, int i2, int i3, int i4);
		void translate(EdgeFace * array[], int i1, int i2, int i3, int i4);
		void translate(MiddleFace * array[], int i1, int i2, int i3, int i4);
		void swap(Face * array[], int i1, int i2);

		int shortenMoves(int);
};

#endif