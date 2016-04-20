#ifndef ROBOTSTATE_H

#define ROBOTSTATE_H

#include <vector>
#include <string>
#include <map>


#define robot_U0 "U0" //Tourner jusqu'à la position 180°
#define robot_U1 "U1" //Tourner jusqu'à la position 90°
#define robot_U2 "U2" //Tourner jusqu'à la position 0°
#define robot_H1 "H1" //Monter de 1
#define robot_H2 "H2" //Monter de 2
#define robot_H3 "H3" //Monter de 3
#define robot_D1 "D1" //Descendre de 1
#define robot_D2 "D2" //Descendre de 2
#define robot_D3 "D3" //Descendre de 3
#define robot_Bi "Bi" //Basculer le balancier
#define robot_B "B" //Remettre le balancier à l'état initial

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