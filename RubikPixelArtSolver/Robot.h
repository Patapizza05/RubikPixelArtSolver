#ifndef ROBOT_H

#define ROBOT_H

#include "RobotState.h"
#include "Rubik.h"
#include <string>
#include <vector>

class Robot {
public:
	Robot();
	void addMove(std::string rubikMove);
	void endMove();
	std::vector<std::string> rmoves;
private:
	RobotState state;
	void U();
	void Ui();
	void H1();
	void H2();
	void H3();
	void D1();
	void D2();
	void D3();
	void Bi();
	void B();
	void resetHeight();
	void addHeight(int);
	void goDown(int);
	void goUp(int);
	void rotate(int);
};

#endif