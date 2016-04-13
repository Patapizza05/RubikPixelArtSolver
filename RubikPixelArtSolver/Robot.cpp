#include "Robot.h"

Robot::Robot() {
	this->state = RobotState(0, false, 1, "U");
}

void Robot::U() {
	state.rotator += 1;
	rmoves.push_back(robot_U);
}
void Robot::Ui() {
	state.rotator -= 1;
	rmoves.push_back(robot_Ui);
}
void Robot::H1() {
	state.height += 1;
	rmoves.push_back(robot_H1);
}
void Robot::H2() {
	state.height += 2;
	rmoves.push_back(robot_H2);
}
void Robot::H3() {
	state.height += 3;
	rmoves.push_back(robot_H3);
}
void Robot::D1() {
	state.height -= 1;
	rmoves.push_back(robot_D1);
}
void Robot::D2() {
	state.height -= 2;
	rmoves.push_back(robot_D2);
}
void Robot::D3() {
	state.height -= 3;
	rmoves.push_back(robot_D3);
}
void Robot::Bi() {
	state.balancier = TRUE;
	rmoves.push_back(robot_Bi);
}
void Robot::B() {
	state.balancier = FALSE;
	rmoves.push_back(robot_B);
}

void Robot::resetHeight() {
	if (state.height == 3) {
		D3();
	}
	else if (state.height == 2) {
		D2();
	}
	else if (state.height == 1) {
		D1();
	}
	/*else if (state.height == 0) {
		//Nothing
	}*/
}

void Robot::goDown(int height) {
	switch (height) {
	case 3:
		D3();
		break;
	case 2:
		D2();
		break;
	case 1:
		D1();
		break;
	default:
		break;
	}
}

void Robot::goUp(int height) {
	switch (height) {
	case 3:
		H3();
		break;
	case 2:
		H2();
		break;
	case 1:
		H1();
		break;
	default:
		break;
	}
}

void Robot::rotate(int rotation) {
	if (rotation > 0) {
		while (rotation > 0) {
			U();
			rotation--;
		}
	}
	else {
		while (rotation < 0) {
			Ui();
			rotation++;
		}
	}
}

void Robot::addHeight(int height) {
	int result = height - this->state.height;
	if (result < 0) {
		goDown(-result);
	}
	else if (result > 0) {
		goUp(result);
	}
}

void Robot::addMove(std::string rubikMove) {
	RobotState state = RobotState::getState(rubikMove);
	/*int height; //Niveau de hauteur à atteindre (0, 1, 2, 3)
	bool balancier; //Etat du balancier après mouvement
	int rotator; //Rotation à ajouter (-1, 1, ou 2)
	std::string referential; //U, F ou R
	*/
	
	//Vérification du référentiel (Le balancier est donc géré)
		//Si changement : hauteur = 0
	if (state.referential != this->state.referential) {
		resetHeight();
		if (this->state.referential == _U) {
			if (state.referential == _F) {
				B();
			}
			else if (state.referential == _R) {
				H3(); U(); D3(); B();
			}
		}
		else if (this->state.referential == _F) {
			if (state.referential == _U) {
				Bi();
			}
			else if (state.referential == _R) {
				Bi(); H3(); U(); D3(); B();
			}
		}
		else if (this->state.referential == _R) {
			Bi(); H3(); Ui();
			if (state.referential == _U) {
				//Done
			}
			else if (state.referential == _F) {
				B();
			}
		}
		this->state.referential = state.referential;
	}

	//Vérification mouvement
	if (state.rotator == 1) {
		if (this->state.rotator == 2) {
			Ui();
		}
		//else : OK
	}
	else if (state.rotator == -1) {
		if (this->state.rotator == 0) {
			U();
		}
		//else : OK
	}
	else if (state.rotator == 2) {
		if (this->state.rotator == 2) {
			state.rotator = -2; //We can rotate backwards to perform U2
		}
		else if (this->state.rotator == 1) {
			Ui();
		}
	}

	//Changement de la hauteur
	addHeight(state.height);

	//Mouvement
	rotate(state.rotator);
}


/*#define _R "R"
#define _Ri "Ri"
#define _R2 "R2"
#define _L "L"
#define _Li "Li"
#define _L2 "L2"
#define _U "U"
#define _Ui "Ui"
#define _U2 "U2"
#define _B "B"
#define _Bi "Bi"
#define _B2 "B2"
#define _F "F"
#define _Fi "Fi"
#define _F2 "F2"
#define _D "D"
#define _Di "Di"
#define _D2 "D2"*/

