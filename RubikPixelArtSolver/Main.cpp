
#include "Rubik.h"
#include "TestCampaign.h"


int main(int argc, char* argv[]) {

	//int pieces[54] = { 6, 4, 7, 6, 1, 7, 16, 12, 9, 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22, 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11, 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12, 10, 14, 19, 8, 2, 9, 4, 5, 5 };
	/*int pieces[54] = { 8, 16, 22,
						18, 1, 19,
						1, 1, 23,
		16, 6, 17, 9, 13, 15, 7, 7, 14, 6, 4, 0,
		2, 0, 0, 12, 4, 5, 22, 5, 11, 20, 3, 14,
		5, 9, 19, 3, 10, 4, 12, 11, 10, 18, 15, 21,
						13, 21, 11,
						3, 2, 22,
						2, 23, 20
	};*/

	int pieces[54] = { 16, 6, 6,
						12, 1, 4,
						9, 7, 7,
		0, 0, 1,		17, 19, 23,		15, 16, 22,		14, 18, 8,
		23, 3, 15,		 3, 0,	1,		13, 4, 10,		22, 5, 11,
		21, 17, 12,		20, 20, 18,		2, 2, 3,		11, 21, 13,
						4, 8, 10,
						5, 2, 14,
						4, 5, 5
	};

	RubikColor colors[9] = {
		RubikColor::BLUE, RubikColor::BLUE, RubikColor::BLUE,
		RubikColor::YELLOW, RubikColor::BLUE, RubikColor::BLUE,
		RubikColor::BLUE, RubikColor::BLUE, RubikColor::BLUE
	};

	TestCampaign testCampaign(pieces);
	testCampaign.run();

	testCampaign.solveOneCube(colors);

	
	return 0;
}
