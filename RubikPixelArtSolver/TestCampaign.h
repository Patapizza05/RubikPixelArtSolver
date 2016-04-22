#ifndef TEST_CAMPAIGN_H

#define TEST_CAMPAIGN_H

#include "RubikColor.h"
#include "Face.h"
#include "Rubik.h"
#include "ResolutionException.h"
#include <vector>

class TestCampaign {
private:
	int passed;
	int failed;
	int nbMoves;
	int pieces[54];
	std::vector<std::vector<int>> rubikColors;
	bool isRubikColors = false;
	std::vector<std::vector<int>> copyRubikColors();
	void resolveTests();
	void resolveOneCube(RubikColor colors[]);
	Rubik makeRubik();
public:
	TestCampaign(int pieces[]);
	TestCampaign(std::vector<std::vector<int>>& rubikColors);
	void run();
	void solveOneCube(RubikColor colors[]);
};

#endif