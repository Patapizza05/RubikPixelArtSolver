#ifndef ROBOTSTATE_H

#define ROBOTSTATE_H

#include <vector>
#include <string>
#include <map>


#define robot_U0 "c" //Tourner jusqu'à la position 180°
#define robot_U1 "b" //Tourner jusqu'à la position 90°
#define robot_U2 "a" //Tourner jusqu'à la position 0°
#define robot_H1 "d" //Monter de 1
#define robot_H2 "e" //Monter de 2
#define robot_H3 "f" //Monter de 3
#define robot_D1 "j" //Descendre de 1
#define robot_D2 "k" //Descendre de 2
#define robot_D3 "l" //Descendre de 3
#define robot_Bi "h" //Basculer le balancier
#define robot_B "i" //Remettre le balancier à l'état initial

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