#ifndef ROBOTSOLVER_H

#define ROBOTSOLVER_H

#include "HumanStepSolver.h"
#include <vector>
#include "Robot.h"

/// <summary>
/// Rubik's cube solver that considering the cost of the robot moves (and not the cost of human moves)
/// </summary>
/// <seealso cref="AbstractHumanStepSolver" />
class RobotSolver : public AbstractHumanStepSolver {
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