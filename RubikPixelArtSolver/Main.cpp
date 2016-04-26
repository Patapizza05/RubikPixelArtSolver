
#include "TestCampaign.h"

void openCVMain()
{
	Robot robot(1, "COM3");

	/*if (robot.initPort()){
		std::cout << "Communication is ready" << std::endl;

		if (robot.send('d')) {
			std::cout << "Movement done" << std::endl;
		}

		if (robot.send('c')) {
			std::cout << "Movement done" << std::endl;
		}
	}
	else {
		std::cerr << "Communication is not ready" << std::endl;
	}*/

	//getchar();

	try{
		robot.launchCapture();
	}
	catch (RobotPositionException ex){
		std::cerr << "Error when getting the initial state" << std::endl;
	}
	 
	getchar();
}

void runCampaignMain() {
	int colorOrder[] = { 2, 3, 4, 1, 5, 0 };

	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorOrder[colorIndex]);
		}
		rubikColors.push_back(piecesColors);
	}

	TestCampaign testCampaign(rubikColors);
	testCampaign.run();
}

void testRobotMovesMain() {
	Robot robot(0, "COM3");

	int colorOrder[] = { 2, 3, 4, 1, 5, 0 };

	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorOrder[colorIndex]);
		}
		rubikColors.push_back(piecesColors);
	}

	Rubik r(rubikColors);
	r.R(); //r.applyMove("R");
	//r.resolve(colors);
	robot.sendRubikMoves(r.getMoves());
	std::vector<std::string> moves = robot.getRobotMoves();
	for (int i = 0; i < moves.size(); i++) {
		std::cout << moves[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "END" << std::endl;
}

void testOneCubeSolveMain() {
	int colorOrder[] = { 2, 3, 4, 1, 5, 0 };

	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorOrder[colorIndex]);
		}
		rubikColors.push_back(piecesColors);
	}

	RubikColor colors[9] = {
		RubikColor::RED, RubikColor::RED, RubikColor::RED,
		RubikColor::RED, RubikColor::RED, RubikColor::RED,
		RubikColor::RED, RubikColor::GREEN, RubikColor::GREEN
	};

	TestCampaign testCampaign(rubikColors);
	testCampaign.solveOneCube(colors);
}

void runTimeTest() {
	int colorOrder[] = { 2, 3, 4, 1, 5, 0 };

	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorOrder[colorIndex]);
		}
		rubikColors.push_back(piecesColors);
	}

	TestCampaign testCampaign(rubikColors);
	testCampaign.time();
}

std::vector<int> swap(std::vector<int> oldIndexes, std::vector<int> newIndexes) {
	std::vector<int> temp = oldIndexes;
	int size = newIndexes.size();
	for (int i = 0; i < size; i++) {
		oldIndexes[i] = temp[newIndexes[i]];
	}

	return oldIndexes;
}

int main(int argc, char* argv[]) {
	std::vector<int> test;
	
	for (int i = 0; i < 9; i++){
		test.push_back(i);
	}

	/*std::vector<std::vector<int>> results;
	results.push_back(test);

	for (int i = 0; i < results[0].size(); i++){
		std::cout << results[0].at(i);
	}*/

	std::cout << std::endl;

	/*std::reverse(results[0].begin(), results[0].begin() + 3);
	std::reverse(results[0].begin() + 3, results[0].begin() + 6);
	std::reverse(results[0].begin() + 6, results[0].end());
	std::reverse(results[0].begin(), results[0].end());

	for (int i = 0; i < results[0].size(); i++){
		std::cout << results[0].at(i);
	}*/

	std::cout << std::endl;

	//runCampaignMain();
	//openCVMain();
	//runCampaignMain();
	//runTimeTest();
	/*Rubik::debug = true;
	testOneCubeSolveMain();
	testRobotMovesMain();*/
	getchar();
	return 0;
}


//int pieces[54] = { 6, 4, 7, 6, 1, 7, 16, 12, 9, 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22, 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11, 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12, 10, 14, 19, 8, 2, 9, 4, 5, 5 };

/*int pieces[54] = { 16, 6, 6,
12, 1, 4,
9, 7, 7,
0, 0, 1,		17, 19, 23,		15, 16, 22,		14, 18, 8,
23, 3, 15,		 3, 0,	1,		13, 4, 10,		22, 5, 11,
21, 17, 12,		20, 20, 18,		2, 2, 3,		11, 21, 13,
4, 8, 10,
5, 2, 14,
4, 5, 5
};*/