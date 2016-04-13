#include "RobotState.h"

std::map<std::string, RobotState> RobotState::robotStates = initRobotStatesMap();

RobotState::RobotState() {
	reset();
}

RobotState::RobotState(int height, bool balancier, int rotator, std::string referential) {
	this->balancier = balancier;
	this->height = height;
	this->referential = referential;
	this->rotator = rotator;
}

void RobotState::reset() {
	this->balancier = false;
	this->height = 0;
	this->referential = "U";
	this->rotator = 1;
}

std::map<std::string, RobotState> RobotState::initRobotStatesMap() {
	std::map<std::string, RobotState> map;
	map["U"] = RobotState(1, false, 1, "U");
	map["Ui"] = RobotState(1, false, -1, "U");
	map["U2"] = RobotState(1, false, 2, "U");
	map["D"] = RobotState(2, false, 1, "U");
	map["Di"] = RobotState(1, false, -1, "U");
	map["D2"] = RobotState(1, false, 2, "U");
	map["F"] = RobotState(1, true, 1, "F");
	map["Fi"] = RobotState(1, true, -1, "F");
	map["F2"] = RobotState(1, true, 2, "F");
	map["B"] = RobotState(1, true, 1, "F");
	map["Bi"] = RobotState(1, true, -1, "F");
	map["B2"] = RobotState(1, true, 2, "F");
	map["R"] = RobotState(1, true, 1, "R"); //H3, U, D3, Ui, B, H1, U
	map["Ri"] = RobotState(1, true, -1, "R");
	map["R2"] = RobotState(1, true, 2, "R");
	map["L"] = RobotState(1, true, 1, "R");
	map["Li"] = RobotState(1, true, -1, "R");
	map["L2"] = RobotState(1, true, 2, "R");
	return map;
}

RobotState RobotState::getState(std::string rubikMove) {
	return RobotState::robotStates[rubikMove];
}
