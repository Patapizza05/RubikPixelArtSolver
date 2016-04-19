
#include "Rubik.h"
#include "TestCampaign.h"
#include "Robot.h"

void openCVMain()
{
	Robot robot("COM3", 0);

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

	robot.launchCapture(); 

	getchar();
}

int main(int argc, char* argv[]) {
	
	openCVMain();
	//int pieces[54] = { 6, 4, 7, 6, 1, 7, 16, 12, 9, 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22, 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11, 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12, 10, 14, 19, 8, 2, 9, 4, 5, 5 };

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

	Rubik::debug = false;

	RubikColor colors[9] = {
		RubikColor::YELLOW, RubikColor::WHITE, RubikColor::YELLOW,
		RubikColor::WHITE, RubikColor::YELLOW, RubikColor::WHITE,
		RubikColor::YELLOW, RubikColor::WHITE, RubikColor::YELLOW
	};

	TestCampaign testCampaign(pieces);
	testCampaign.run();

	//testCampaign.solveOneCube(colors);

	/*Rubik r(pieces);
	r.R();
	r.U();
	//r.resolve(colors);
	std::vector<std::string> moves = r.translateToRobotMoves();
	for (int i = 0; i < moves.size(); i++) {
		std::cout << moves[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "END" << std::endl;*/
	getchar();
	
	return 0;
}


