
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

/// <summary>
/// Class representing a Rubik's cube
/// </summary>
class Rubik {
	public:

		/// <summary>
		/// Initializes a new instance of the <see cref="Rubik"/> class from an array representing the colors of the cube
		/// This constructor can be used after scanning the Rubik's cube with OpenCV and the robot
		/// </summary>
		/// <param name="">an array representing the colors of the cube in this order (the scanning order of the cube with the robot) :
		///					[		Cell 5		]
		/// [	Cell 2		][		Cell 3		][		Cell 0		][		Cell 1		]
		///					[		Cell 4		]	
		/// In each cell is a vector of size 9 giving the colors of the pieces in this order :
		///	[0	1	2
		///  3	4	5
		///	 6	7	8]
		/// (first row, second row, third row)</param>
		Rubik(std::vector<std::vector<int>>&);


		/// <summary>
		/// Initializes a new instance of the <see cref="Rubik"/> class from an array giving the # of each piece
		/// </summary>
		/// <param name="">The array representing the # of each piece in the following order :
		/// [Top Layer, Row 1] 0, 1, 2 
		///[Top Layer, Row 2] 3, 4, 5 
		///[Top Layer, Row 3] 6, 7, 8 
		///[Left Layer, Row 1] 9, 10, 11 [Front Layer, Row 1] 12, 13, 14 [Right Layer, Row 1] 15, 16, 17 [Back Layer, Row 1] 18, 19, 20
		///[Left Layer, Row 2] 21, 22, 23 [Front Layer, Row 2] 24, 25, 26 [Right Layer, Row 2] 27, 28, 29 [Back Layer, Row 2] 30, 31, 32
		///[Left Layer, Row 3] 33, 34, 35 [Front Layer, Row 3] 36, 37, 38 [Right Layer, Row 3] 39, 40, 41 [Back Layer, Row 3] 42, 43, 44
		///[Bottom Layer, Row 1] 45, 46, 47
		///[Bottom Layer, Row 2] 48, 49, 50
		///[Bottom Layer, Row 3]51, 52, 53
		///</param>
		Rubik(int[]);

		/// <summary>
		/// Finalizes an instance of the <see cref="Rubik"/> class.
		/// </summary>
		~Rubik();

		/// <summary>
		/// Prints the cube in the console with colors and the # of each piece
		/// However, orange is represented as a different color (pink= because it is not a standard color in a terminal
		/// </summary>
		void printCube();

		static bool Rubik::debug;
		/// <summary>
		/// Enables or disables the console prints when resolving the cube
		/// </summary>
		/// <param name="">if set to <c>true</c> [].</param>
		static void setVerbose(bool);

		/// <summary>
		/// Verifies the rubik colors.
		/// </summary>
		/// <param name="colors">The expected colors in the following order :
		/// [Top Layer, Row 1] 0, 1, 2
		/// [Top Layer, Row 2] 3, 4, 5
		/// [Top Layer, Row 3] 6, 7, 8
		///</param>
		/// <returns></returns>
		bool verifyRubikColors(RubikColor colors[]);

		/// <summary>
		/// Turns the right layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void R(bool isAddToMoves = true);

		/// <summary>
		/// Turns the right layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Ri(bool isAddToMoves = true);

		/// <summary>
		/// Turns the right layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void R2(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the left layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void L(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the left layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Li(bool isAddToMoves = true);

		/// <summary>
		///Turns the left layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void L2(bool isAddToMoves = true);

		/// <summary>
		/// Turns the top layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void U(bool isAddToMoves = true);

		/// <summary>
		/// Turns the top layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Ui(bool isAddToMoves = true);

		/// <summary>
		/// Turns the top layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void U2(bool isAddToMoves = true);

		/// <summary>
		/// Turns the back layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void B(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the back layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Bi(bool isAddToMoves = true);

		/// <summary>
		/// Turns the back layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void B2(bool isAddToMoves = true);
		
		/// <summary>
		/// Turns the front layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void F(bool isAddToMoves = true);

		/// <summary>
		/// Turns the front layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Fi(bool isAddToMoves = true);

		/// <summary>
		/// Turns the front layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void F2(bool isAddToMoves = true);

		/// <summary>
		/// Turns the bottom layer of the cube clockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void D(bool isAddToMoves = true);

		/// <summary>
		/// Turns the bottom layer of the cube counterclockwise
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void Di(bool isAddToMoves = true);

		/// <summary>
		/// Turns the bottom layer of the cube twice
		/// </summary>
		/// <param name="isAddToMoves">if set to <c>true</c>, add the move to the <c>moves</c> array</param>
		void D2(bool isAddToMoves = true);
		
		/// <summary>
		/// Changes the referential of the cube
		/// </summary>
		/// <param name="color">The middle piece color which will be placed on top layer</param>
		void changeReferential(RubikColor color);	

		/// <summary>
		/// Changes the refential of the cube: 
		/// Top layer becomes front layer,
		/// Front layer becomes bottom layer,
		/// Bottom Layer becomes back layer,
		/// Back layer becomes top layer,
		/// Right layer and Left layer remain the same.
		/// </summary>
		void turnCubeUp();

		/// <summary>
		/// Changes the referential of the cube: 
		/// Top layer becomes left layer,
		/// Left layer becomes bottom layer,
		/// Bottom layer becomes right layer,
		/// Right layer becomes top layer, 
		/// Front and back layers remain the same.
		/// </summary>
		void turnCubeRight();

		/// <summary>
		/// Changes the refential of the cube: 
		/// Top layer becomes back layer,
		/// Front layer becomes top layer,
		/// Bottom Layer becomes front layer,
		/// Back layer becomes bottom layer,
		/// Right layer and Left layer remain the same.
		/// </summary>
		void turnCubeDown();


		/// <summary>
		/// Changes the refential of the cube: 
		/// Top layer becomes right layer,
		/// Right layer becomes bottom layer,
		/// Bottom layer becomes left layer,
		/// Left layer becomes top layer,
		/// Front and back layers remain the same
		/// </summary>
		void turnCubeLeft();

		/// <summary>
		/// Resolves the cube to have a layer with the specified colors, using HumanSolver class method
		/// </summary>
		/// <param name="colors">The colors.</param>
		void resolve(RubikColor colors[]);

		/// <summary>
		/// Resolves the cube to have a layer with the specified colors, using RobotSolver class method
		/// </summary>
		/// <param name="colors">The expected colors</param>
		/// <param name="pRobot">The robot used to compute the cost of each move</param>
		void resolve(RubikColor colors[], Robot * pRobot);

		/// <summary>
		/// Prints the error to the console
		/// </summary>
		/// <param name="">The text to print</param>
		void error(std::string);	

		/// <summary>
		/// Checks each move to find moves that can be simplified. Normally, this method is not needed since the addMove method optimises before adding the move to the list
		/// </summary>
		void optimise();	

		/// <summary>
		/// Translates the "string" moves to actual corresponding functions (eg. "R" calls the function this->R())
		/// </summary>
		/// <param name="">The array of string representing moves</param>
		void applyMoves(std::vector<std::string>&);		

		/// <summary>
		/// Translates the "string" move to actual corresponding function (eg. "R" calls the function this->R())
		/// </summary>
		/// <param name="">The string representing the move</param>
		void applyMove(std::string);

		/// <summary>
		/// Gets the moves applied to this cube
		/// </summary>
		/// <returns></returns>
		std::vector<std::string> getMoves() { return moves; }		

		/// <summary>
		/// Sets the edge as locked, meaning it's in the correct position on the cube and should not be moved anymore
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="value">if set to <c>true</c> [value].</param>
		void setLockedEdge(int index, bool value);

		/// <summary>
		/// Sets the corner as locked, meaning it's in the correct position on the cube and should not be moved anymore
		/// </summary>
		/// <param name="index">The index.</param>
		/// <param name="value">if set to <c>true</c> [value].</param>
		void setLockedCorner(int index, bool value);
		
		/// <summary>
		/// Gets the corner at corresponding index
		/// </summary>
		/// <param name="">The index</param>
		/// <returns></returns>
		CornerFace * getCorner(int);
		
		/// <summary>
		/// Gets the edge at corresponding index
		/// </summary>
		/// <param name="">The index</param>
		/// <returns></returns>
		EdgeFace * getEdge(int);
		
		/// <summary>
		/// Gets the middle face at corresponding index
		/// </summary>
		/// <param name="">The index</param>
		/// <returns></returns>
		MiddleFace * getMiddle(int);

		std::string getMoveAtIndex(int);
		int getNbMoves();

	private:
		static int lines[9][12];
		std::map<std::string, std::string> movesDictionary;
		std::map<std::string, pfunc> movesFunctions;

		CornerFace * corners[24];
		EdgeFace * edges[24];
		MiddleFace * middle[8];

		std::vector<std::string> moves;

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