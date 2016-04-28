
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
	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorIndex);
		}
		rubikColors.push_back(piecesColors);
	}

	TestCampaign testCampaign(rubikColors);
	testCampaign.run();
}

void testRobotMovesMain() {
	Robot robot(0, "COM3");
	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorIndex);
		}
		rubikColors.push_back(piecesColors);
	}

	Rubik r(rubikColors);
	r.F2();
	std::vector<std::string> moves = r.getMoves();
	for (int i = 0; i < moves.size(); i++) {
		std::cout << moves[i] << " ";
	}
	std::cout << std::endl;
	//r.resolve(colors);
	robot.sendRubikMoves(moves);
	std::vector<std::string> rmoves = robot.getRobotMoves();
	for (int i = 0; i < rmoves.size(); i++) {
		std::cout << rmoves[i] << " ";
	}
	std::cout << std::endl;
	robot.printSimplifiedSentRobotMoves();
	std::cout << std::endl;
	std::cout << "END" << std::endl;
}

void testOneCubeSolveMain() {
	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorIndex);
		}
		rubikColors.push_back(piecesColors);
	}

	RubikColor colors[9] = {
		RubikColor::WHITE, RubikColor::WHITE, RubikColor::WHITE,
		RubikColor::WHITE, RubikColor::WHITE, RubikColor::WHITE,
		RubikColor::YELLOW, RubikColor::YELLOW, RubikColor::YELLOW
	};

	TestCampaign testCampaign(rubikColors);
	testCampaign.solveOneCube(colors);
}

void runTimeTest() {
	std::vector<std::vector<int>> rubikColors;
	for (int colorIndex = 0; colorIndex < 6; colorIndex++) {
		std::vector<int> piecesColors;
		for (int i = 0; i < 9; i++) {
			piecesColors.push_back(colorIndex);
		}
		rubikColors.push_back(piecesColors);
	}

	TestCampaign testCampaign(rubikColors);
	testCampaign.time();
}

void testPrintCube() {
	//WHITE = 0, GREEN = 1, RED = 2, BLUE = 3, ORANGE = 4, YELLOW = 5
	std::vector<int> a0{5,3,1,4,1,4,4,0,4};
	std::vector<int> a1{2,0,0,1,0,0,0,5,1};
	std::vector<int> a2{1,2,3,1,2,1,3,3,1};
	std::vector<int> a3{5,5,3,3,3,1,2,5,5};
	std::vector<int> a4{4,4,3,2,4,4,4,5,5};
	std::vector<int> a5{2,2,0,3,5,0,2,2,0};

	std::vector<std::vector<int>> pieces{ a0, a1, a2, a3, a4, a5 };

	Rubik rubik(pieces);
	rubik.printCube();
}

int main(int argc, char* argv[]) {
	//testPrintCube();
	//runCampaignMain();
	//openCVMain();
	//runCampaignMain();
	//runTimeTest();
	/*Rubik::debug = true;
	testOneCubeSolveMain();*/
	//testRobotMovesMain();
	//Rubik::debug = true;
	//testOneCubeSolveMain();
	testRobotMovesMain();
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