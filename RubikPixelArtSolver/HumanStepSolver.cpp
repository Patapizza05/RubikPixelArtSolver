#include "HumanStepSolver.h"
#include "Rubik.h"

void HumanStepSolver::resolve(Rubik * pRubik, RubikColor colors[]) {
	resolveMiddle(pRubik, colors[4]);
	RubikColor edgesColors[4] = { colors[7], colors[5], colors[1], colors[3] };
	RubikColor cornersColors[4] = { colors[6], colors[8], colors[2], colors[0] };
	resolveEdges(pRubik, edgesColors);
	resolveCorners(pRubik, cornersColors);
}

void HumanStepSolver::resolveMiddle(Rubik * pRubik, RubikColor color) {
	int index = this->searchMiddleColorIndex(pRubik, color);
	pRubik->middle[index]->setLockedPosition(true);
	if (Rubik::debug) pRubik->printCube();
}

void HumanStepSolver::resolveEdges(Rubik * pRubik, RubikColor colors[]) {

	int solvedEdges = 0;

	for (int i = 0; i < 4; i++) {
		RubikColor color = colors[i]; //12 7 4 6
		int index = this->searchEdgeColorIndex(pRubik, color, solvedEdges);
		if (index == -1) {
			std::cout << "did not find edge" << std::endl;
			return;
		}
		if (Rubik::debug) std::cout << "Edge : Number " << pRubik->edges[index]->getNumber() << " at position " << index << std::endl;

		pRubik->setLockedEdge(12, TRUE);
		solvedEdges++;
		pRubik->U();

		if (Rubik::debug) {
			std::cout << std::endl;
			std::vector<std::string> moves = pRubik->getMoves();
			int size = moves.size();
			for (unsigned int i = 0; i < size; i++) {
				std::cout << moves[i] << " ";
			}
			pRubik->printCube();
			std::cout << "--------------------------------------------------------" << std::endl;
		}

	}
}

void HumanStepSolver::resolveCorners(Rubik * pRubik, RubikColor colors[]) {
	int solvedCorners = 0;

	for (int i = 0; i < 4; i++) {
		RubikColor color = colors[i]; //16 9 7 6
		int index = this->searchCornerColorIndex(pRubik, color, solvedCorners);
		if (index == -1) {
			std::cout << "Did not find corner" << std::endl;
		}
		if (Rubik::debug) std::cout << "Corner : Number " << pRubik->corners[index]->getNumber() << " at position " << index << std::endl;

		pRubik->setLockedCorner(16, true);

		solvedCorners++;
		pRubik->U();

		if (Rubik::debug) {
			std::cout << std::endl;
			std::vector<std::string> moves = pRubik->getMoves();
			int size = moves.size();
			for (unsigned int i = 0; i < size; i++) {
				std::cout << moves[i] << " ";
			}
			pRubik->printCube();
			std::cout << "--------------------------------------------------------" << std::endl;
		}
	}

}

bool HumanStepSolver::checkEdgeColor(Rubik * pRubik, int index, RubikColor color) { //locked
	if (pRubik->edges[index]->getLockedPosition() == false && pRubik->edges[index]->getColor() == color)
	{
		return true;
	}
	return false;
}

bool HumanStepSolver::checkCornerColor(Rubik * pRubik, int index, RubikColor color) { //locked
	if (pRubik->corners[index]->getLockedPosition() == false && pRubik->corners[index]->getColor() == color)
	{
		return true;
	}
	return false;
}



int HumanStepSolver::searchMiddleColorIndex(Rubik * pRubik, RubikColor color) {
	if (checkMiddleColor(pRubik, 1, color)) {
		//No moves
		return 1;
	}

	if (checkMiddleColor(pRubik, 0, color)) {
		//Moves
		pRubik->middle_TurnCubeDown();
		if (Rubik::debug)
			std::cout << "Down" << std::endl;
		return 0;
	}

	if (checkMiddleColor(pRubik, 3, color)) {
		//Moves
		pRubik->middle_TurnCubeLeft();
		if (Rubik::debug)
			std::cout << "Left" << std::endl;
		return 3;
	}

	if (checkMiddleColor(pRubik, 4, color)) {
		//Moves
		pRubik->middle_TurnCubeRight();
		if (Rubik::debug)
			std::cout << "Right" << std::endl;
		return 4;
	}

	if (checkMiddleColor(pRubik, 5, color)) {
		//Moves
		pRubik->middle_TurnCubeUp();
		if (Rubik::debug)
			std::cout << "Up" << std::endl;
		return 5;
	}

	if (checkMiddleColor(pRubik, 2, color)) {
		//Moves
		pRubik->middle_TurnCubeDown();
		pRubik->middle_TurnCubeDown();
		if (Rubik::debug)
			std::cout << "Down^2" << std::endl;
		return 2;
	}

	return 1;
}

bool HumanStepSolver::checkMiddleColor(Rubik * pRubik, int i, RubikColor color) {
	if (pRubik->middle[i]->getColor() == color)
		return true;
	return false;
}