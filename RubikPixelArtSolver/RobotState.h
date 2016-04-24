#ifndef ROBOTSTATE_H

#define ROBOTSTATE_H

#include "Face.h"
#include <vector>
#include <string>
#include <map>

#define robot_U0 "c"			//Turn to the 180° angle
#define robot_U1 "b"			//Turn to the 90° angle
#define robot_U2 "a"			//Turn to the 0° angle
#define robot_H0_to_1 "d"		//Go up from height 0 to height 1
#define robot_H0_to_2 "e"		//Go up from height 0 to height 2
#define robot_H0_to_3 "f"		//Go up from height 0 to height 3
#define robot_D1_to_0 "j"		//Go down from height 1 to height 0
#define robot_D2_to_0 "k"		//Go down from height 2 to height 0
#define robot_D3_to_0 "l"		//Go down from height 3 to height 0
#define robot_Bi "h"			//Put the balancer in reversed position
#define robot_B "i"				//Put the balancer in standard position
#define robot_H1_to_3 "z"		//Go up from height 1 to height 3
#define robot_D3_to_1 "y"		//Go down from height 3 to height 1
#define robot_D3_to_2 "u"		//Go down from height 3 to height 2
#define robot_H2_to_3 "v"		//Go up from height 2 to height 3
#define robot_D2_to_1 "w"		//Go down from height 2 to height 1
#define robot_H1_to_2 "x"		//Go up from height 1 to height 2

/// <summary>
/// Represents the state of the robot
/// </summary>
class RobotState {
public:
	int height; //0, 1, 2, 3
	bool balancer; //0, 1
	int rotator; //In robot class : 0, 1 or 2 : Gives the current state (0°, 90°, 180°)
				//For the state returned by getState : The rotations to perform (-1, 0, 1 or 2)
	std::string referential; //U, F, R
	void reset();
	RobotState(int=0,bool=false,int=1,std::string=_U);
	
	/// <summary>
	/// Gives the actions to do to perform the given rubik move.
	/// </summary>
	/// <param name="rubikMove">The rubik move.</param>
	/// <returns>The robot state giving what to perform</returns>
	static RobotState getState(std::string rubikMove);
	
	/// <summary>
	/// Initializes the robot states map. Dictionary of all the state rubik moves.
	/// </summary>
	/// <returns>The state to perform this rubik move</returns>
	static std::map<std::string, RobotState> RobotState::initRobotStatesMap();

private:
	static std::map<std::string, RobotState> RobotState::robotStates;
};

#endif ROBOTSTATE_H