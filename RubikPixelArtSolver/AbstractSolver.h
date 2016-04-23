#ifndef ABSTRACTSOLVER_H

#define ABSTRACTSOLVER_H

#include "RubikColor.h"
#include "Face.h"

class Rubik;

class AbstractSolver {
public:
	virtual void resolve(Rubik * pRubik, RubikColor colors[]) = 0;
};

#endif