
#include "Rubik.h"
#include "ResolutionException.h"


struct TestResults {
	int passed;
	int failed;
};



void resolveOneCube(int pieces[], RubikColor colors[], struct TestResults * pResults) {
	Rubik* rubik = new Rubik(pieces);
	rubik->resolve(colors);

	if (rubik->checkRubik(colors))
	{
		pResults->passed++;
	}
	else {
		pResults->failed++;
		std::cout << setcolor(RubikColor::RED) << "FAILED" << setcolor(RubikColor::WHITE) << "(passed " << pResults->passed << ", failed " << pResults->failed << ")" << std::endl;
		std::cout << "Expected colors :" << std::endl;
		for (int i = 0; i < 9; i++) {
			std::cout << setcolor(colors[i]) << "#";
			if (i % 3 == 2) {
				std::cout << std::endl;
			}
		}

		std::cout << setcolor(RubikColor::WHITE) << std::endl;
		std::cout << "Moves :";
		std::vector<std::string> moves = rubik->getMoves();
		int size = moves.size();
		for (int i = 0; i < size; i++) {
			std::cout << " " << moves[i];
		}
		std::cout << std::endl;

		std::cout << setcolor(RubikColor::WHITE) << "---------------------------------------------" << std::endl;
		rubik->printCube();
		//getchar();
		throw ResolutionException("Incorrect resolution", colors);
	}
	delete rubik;
}

void resolveTest(int pieces[]) {
	struct TestResults results;
	results.failed = 0;
	results.passed = 0;

	RubikColor rubikColors[6] = { RubikColor::WHITE, RubikColor::GREEN, RubikColor::RED, RubikColor::BLUE, RubikColor::ORANGE, RubikColor::YELLOW };
	RubikColor colors[9];

	for (int i1 = 0; i1 < 6; i1++) {
		colors[0] = rubikColors[i1];
		for (int i2 = 0; i2 < 6; i2++) {
			colors[1] = rubikColors[i2];
			for (int i3 = 0; i3 < 6; i3++) {
				colors[2] = rubikColors[i3];

				for (int i4 = 0; i4 < 6; i4++) {
					colors[3] = rubikColors[i4];
					

						std::cout << "RESULTS" << std::endl;
						std::cout << "Number of tests : " << results.passed + results.failed << std::endl;
						std::cout << "Passed : " << results.passed << std::endl;
						std::cout << "Failed : " << results.failed << std::endl;
						std::cout << std::endl;

						for (int i6 = 0; i6 < 6; i6++) {
							colors[5] = rubikColors[i6];
							for (int i7 = 0; i7 < 6; i7++) {
								colors[6] = rubikColors[i7];

								for (int i8 = 0; i8 < 6; i8++) {
									colors[7] = rubikColors[i8];
									for (int i9 = 0; i9 < 6; i9++) {
										colors[8] = rubikColors[i9];
										for (int i5 = 0; i5 < 6; i5++) {
											colors[4] = rubikColors[i5];

										resolveOneCube(pieces, colors, &results);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	std::cout << "RESULTS" << std::endl;
	std::cout << "Number of tests : " << results.passed + results.failed << std::endl;
	std::cout << "Passed : " << results.passed << std::endl;
	std::cout << "Failed : " << results.failed << std::endl;
	getchar();

}

void solveOneCube(int pieces[], RubikColor colors[]) {
	/* The numbers are specified this way

				01 02 03
				04 05 06
				07 08 09

	10 11 12	13 14 15   16 17 18   19 20 21
	22 23 24	25 26 27   28 29 30   31 32 33
	34 35 36	37 38 39   40 41 42   43 44 45

				46 47 48
				49 50 51
				52 53 54

	*/


	Rubik* rubik = new Rubik(pieces);

	/*The colors are specified this way :
	1 2 3
	4 5 6
	7 8 9
	*/

	rubik->resolve(colors);


	std::cout << "Expected colors :" << std::endl;
	for (int i = 0; i < 9; i++) {
		std::cout << setcolor(colors[i]) << "#";
		if (i % 3 == 2) {
			std::cout << std::endl;
		}
	}

	std::cout << setcolor(RubikColor::WHITE) << std::endl;
	std::cout << "Moves :";
	std::vector<std::string> moves = rubik->getMoves();
	int size = moves.size();
	for (int i = 0; i < size; i++) {
		std::cout << " " << moves[i];
	}
	std::cout << std::endl;

	std::cout << setcolor(RubikColor::WHITE) << "---------------------------------------------" << std::endl;
	rubik->printCube();
	getchar();

	delete rubik;
}

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


	Rubik::debug = false;

	/*try {
		resolveTest(pieces);
	}
	catch (ResolutionException ex)
	{
		Rubik::debug = true;
		solveOneCube(pieces, ex.getColors());
	}*/

	RubikColor colors[9] = {
		RubikColor::BLUE, RubikColor::BLUE, RubikColor::BLUE,
		RubikColor::YELLOW, RubikColor::BLUE, RubikColor::BLUE,
		RubikColor::BLUE, RubikColor::BLUE, RubikColor::BLUE
	};
	solveOneCube(pieces, colors);

	
	return 0;
}
