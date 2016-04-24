#ifndef TEST_CAMPAIGN_H

#define TEST_CAMPAIGN_H

#include "RubikColor.h"
#include "Face.h"
#include "Rubik.h"
#include "ResolutionException.h"
#include <vector>

/// <summary>
/// Test campaigns to make sure the solvers can solve the cubes without error
/// </summary>
class TestCampaign {
private:
	int passed;
	int failed;
	int nbMoves;
	int nbRobotMoves;
	int pieces[54];
	std::vector<std::vector<int>> rubikColors;
	bool isRubikColors = false;
	std::vector<std::vector<int>> copyRubikColors();
	void resolveTests();
	void resolveOneCube(RubikColor colors[]);
	Rubik makeRubik();
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TestCampaign"/> class.
	/// </summary>
	/// <param name="pieces">The pieces of the rubiks cube</param>
	TestCampaign(int pieces[]);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="TestCampaign"/> class.
	/// </summary>
	/// <param name="rubikColors">The rubik colors.</param>
	TestCampaign(std::vector<std::vector<int>>& rubikColors);
	
	/// <summary>
	/// Runs the campaign : Solve all the possible colors of a given rubik's cube
	/// </summary>
	void run();
	
	/// <summary>
	/// Solves the rubik's cube with the given colors
	/// </summary>
	/// <param name="colors">The colors.</param>
	void solveOneCube(RubikColor colors[]);
};

#endif