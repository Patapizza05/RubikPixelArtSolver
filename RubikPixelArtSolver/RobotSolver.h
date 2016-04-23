#ifndef ROBOTSOLVER_H

#define ROBOTSOLVER_H

#include "HumanStepSolver.h"
#include <vector>
#include "Robot.h"

class RobotSolver : public HumanStepSolver {
public:
	RobotSolver(Robot * pRobot);
protected:
	int searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges);
	int searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges);
private:
	Robot * pRobot;
	bool getMinCost(Rubik * pRubik, std::vector<std::string>& resultMoves, int& minCost);
};

#endif