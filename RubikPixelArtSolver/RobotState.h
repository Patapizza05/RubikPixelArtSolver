#ifndef ROBOTSTATE_H

#define ROBOTSTATE_H

#include <vector>
#include <string>
#include <map>

#define robot_U "U"
#define robot_Ui "Ui"
#define robot_H1 "H1"
#define robot_H2 "H2"
#define robot_H3 "H3"
#define robot_D1 "D1"
#define robot_D2 "D2"
#define robot_D3 "D3"
#define robot_Bi "Bi"
#define robot_B "B"

class RobotState {
public:
	int height; //0, 1, 2, 3
	bool balancier; //0, 1
	int rotator; //0, 1, 2 //default : 1
	std::string referential; //U, F, R
	void reset();
	RobotState();
	RobotState(int,bool,int,std::string);

	static RobotState getState(std::string rubikMove);
	static std::map<std::string, RobotState> RobotState::initRobotStatesMap();

private:
	static std::map<std::string, RobotState> RobotState::robotStates;
};

#endif ROBOTSTATE_H