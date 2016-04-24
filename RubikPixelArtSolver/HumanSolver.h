#ifndef HUMANSOLVER_H

#define HUMANSOLVER_H

#include "HumanStepSolver.h"

/// <summary>
/// Solves the cube considering human moves cost
/// </summary>
/// <seealso cref="AbstractHumanStepSolver" />
class HumanSolver : public AbstractHumanStepSolver {
protected:
	int searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges);
	int searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges);
	
};

#endif