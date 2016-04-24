#ifndef HUMANSTEPSOLVER_H

#define HUMANSTEPSOLVER_H

#include "AbstractSolver.h"

class AbstractHumanStepSolver : public AbstractSolver {
public:
	virtual void resolve(Rubik * pRubik, RubikColor colors[]);
	virtual void resolveMiddle(Rubik * pRubik, RubikColor colors);
	virtual void resolveEdges(Rubik * pRubik, RubikColor colors[]);
	virtual void resolveCorners(Rubik * pRubik, RubikColor colors[]);
protected:
	bool checkCornerColor(Rubik * pRubik, int, RubikColor);
	bool checkEdgeColor(Rubik * pRubik, int, RubikColor);
	virtual int searchEdgeColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges) = 0;
	virtual int searchCornerColorIndex(Rubik * pRubik, RubikColor color, int solvedEdges) = 0;
private:
	virtual int searchMiddleColorIndex(Rubik * pRubik, RubikColor color);
	virtual bool checkMiddleColor(Rubik*, int, RubikColor);
};

#endif