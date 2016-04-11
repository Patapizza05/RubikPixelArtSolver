#ifndef TEST_CAMPAIGN_H

#define TEST_CAMPAIGN_H

#include "RubikColor.h"
#include "Rubik.h"
#include "ResolutionException.h"

class TestCampaign {
private:
	int passed;
	int failed;
	int nbMoves;
	int pieces[54];
	void resolveTests();
	void resolveOneCube(RubikColor colors[]);
public:
	TestCampaign(int pieces[]);
	void run();
	void solveOneCube(RubikColor colors[]);
};

#endif