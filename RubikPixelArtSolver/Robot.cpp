#include "Robot.h"


/* Hue values of basic colors
Orange  0-22
Yellow 22- 38
Green 38-75
Blue 75-130
Violet 130-160
Red 160-179

http://opencv-srf.blogspot.fr/2010/09/object-detection-using-color-seperation.html */
/* White - Green - Red - Blue - Orange - Yellow */
std::vector<Scalar> minColor{ Scalar(70, 20, 130), Scalar(60, 110, 110), Scalar(120, 120, 140), Scalar(80, 180, 190), Scalar(5, 150, 150), Scalar(20, 100, 100) };
std::vector<Scalar> maxColor{ Scalar(180, 110, 255), Scalar(100, 220, 250), Scalar(180, 250, 200), Scalar(120, 255, 255), Scalar(15, 235, 250), Scalar(40, 255, 255) };

Robot::Robot(int camera_id, String window_name){
	this->state = RobotState(0, false, 1, _U);
	this->setCameraId(camera_id);
	this->setSquareCount(0);
	this->setWindowName(window_name);
}

void Robot::sendRubikMoves(std::vector<std::string> rubikMoves) {
	for (unsigned int i = 0; i < rubikMoves.size(); i++) {
		this->addMove(rubikMoves[i]);
	}
	this->endMove();
}

int Robot::getRubikMovesCost(std::vector<std::string> rubikMoves, std::string previousRubikMove) {

	RobotState previousState;
	if (previousRubikMove == "") {
		previousState = this->state;
	}
	else {
		previousState = RobotState::getState(previousRubikMove);
	}
	int cost = 0;
	int size = rubikMoves.size();
	for (int i = 0; i < size; i++) {
		RobotState state = RobotState::getState(rubikMoves[i]);
		//Check referential
		if (state.referential != previousState.referential) {
			if (state.referential == _R) {
				if (previousState.referential == _U) {
					if (previousState.height != 3) {
						cost++; //H
						previousState.height = 3;
					}
				}
				if (previousState.referential == _F) {
					cost+= 2; //H B
				}
				cost += 3; //U D B
				previousState.referential = _R;
			}
			else { //going to U or F
				if (previousState.height > 0) {
					cost++;
					previousState.height = 0;
				}
				if (previousState.referential == _R) //R --> U  or F
				{
					cost += 3;//Bi H Ui
					if (state.referential == _F)
					{
						cost++;
					}
				}
				else { //U --> F || F --> U
					cost++; //Bi or B
				}
			}
		}
		previousState.referential = state.referential;


		//Check height
		if (previousState.height != state.height) {
			cost++;
			previousState.height = state.height;
		}

		//Check rotation
		if (state.rotator != 0) {
			previousState.rotator += state.rotator;
			cost++;
		}
		
	}
	return cost;

}

bool Robot::sendMessageAndRead(std::string m) {
	this->controller.send(m[0]);

	if (this->controller.read() == m[0] || ROBOT_DEBUG) { //Blocks until the robot responds (if ROBOT_DEBUG == 0)
		rmoves.push_back(m);
		return true;
	}

	return false;
}

bool Robot::U0() {
	if (sendMessageAndRead(robot_U0)) {
		state.rotator = 0;
		return true;
	}
	return false;
}

bool Robot::U1() {
	if (sendMessageAndRead(robot_U1)) {
		state.rotator = 1;
		return true;
	}
	return false;
}

bool Robot::U2() {
	if (sendMessageAndRead(robot_U2)) {
		state.rotator = 2;
		return true;
	}
	return false;
}

bool Robot::U() {
	if (state.rotator == 0) {
		return U1();
	}
	else if (state.rotator == 1) {
		return U2();
	}
	return false;
}
bool Robot::Ui() {
	if (state.rotator == 1) {
		return U0();
	}
	else if (state.rotator == 2) {
		return U1();
	}
	return false;
}

bool Robot::H0_to_1() {
	if (sendMessageAndRead(robot_H0_to_1)) {
		state.height = 1;
		return true;
	}

	return false;
}
bool Robot::H0_to_2() {
	if (sendMessageAndRead(robot_H0_to_2)) {
		state.height = 2;
		return true;
	}

	return false;
}
bool Robot::H0_to_3() {
	if (sendMessageAndRead(robot_H0_to_3)) {
		state.height = 3;
		return true;
	}

	return false;
}
bool Robot::H1_to_2() {
	if (sendMessageAndRead(robot_H1_to_2)) {
		state.height = 2;
		return true;
	}

	return false;
}
bool Robot::H1_to_3() {
	if (sendMessageAndRead(robot_H1_to_3)) {
		state.height = 3;
		return true;
	}

	return false;
}
bool Robot::H2_to_3() {
	if (sendMessageAndRead(robot_H2_to_3)) {
		state.height = 3;
		return true;
	}
	return false;
}

bool Robot::D3_to_0() {
	if (sendMessageAndRead(robot_D3_to_0)) {
		state.height = 0;
		return true;
	}
	return false;
}
bool Robot::D2_to_0() {
	if (sendMessageAndRead(robot_D2_to_0)) {
		state.height = 0;
		return true;
	}
	return false;
}
bool Robot::D1_to_0() {
	if (sendMessageAndRead(robot_D1_to_0)) {
		state.height = 0;
		return true;
	}
	return false;
}
bool Robot::D2_to_1() {
	if (sendMessageAndRead(robot_D2_to_1)) {
		state.height = 1;
		return true;
	}
	return false;
}
bool Robot::D3_to_2() {
	if (sendMessageAndRead(robot_D3_to_2)) {
		state.height = 2;
		return true;
	}
	return false;
}
bool Robot::D3_to_1() {
	if (sendMessageAndRead(robot_D3_to_1)) {
		state.height = 1;
		return true;
	}
	return false;
}

bool Robot::H1() {
	switch (state.height) {
	case 0:
		return H0_to_1();
	case 1:
		return H1_to_2();
	case 2:
		return H2_to_3();
	default:
		return false;
	}
}
bool Robot::H2() {
	switch (state.height) {
	case 0:
		return H0_to_2();
	case 1:
		return H1_to_3();
	default:
		return false;
	}

}
bool Robot::H3() {
	if (state.height == 0) {
		return H0_to_3();
	}
	return false;

}
bool Robot::D1() {
	switch (state.height) {
	case 3:
		return D3_to_2();
	case 2:
		return D2_to_1();
	case 1:
		return D1_to_0();
	default:
		return false;
	}
}
bool Robot::D2() {
	switch (state.height) {
	case 3:
		return D3_to_1();
	case 2:
		return D2_to_0();
	default:
		return false;
	}
}
bool Robot::D3() {
	if (state.height == 3) {
		return D3_to_0();
	}
	return false;
}


bool Robot::Bi() {
	if (sendMessageAndRead(robot_Bi)) {
		state.balancer = true;
		return true;
	}
	return false;
}

bool Robot::B() {
	if (sendMessageAndRead(robot_B)) {
		state.balancer = false;
		return true;
	}
	return false;
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
	
	//Vérification du référentiel (Le balancier est donc géré)
		//Si changement : hauteur = 0
	if (state.referential != this->state.referential) {
		if (this->state.referential == _U) {
			if (state.referential == _F) {
				resetHeight();
				B();
			}
			else if (state.referential == _R) {
				if (state.rotator == 2) {
					resetHeight();
					Ui();
				}
				addHeight(3 - this->state.height);
				U(); D3(); B();
			}
		}
		else if (this->state.referential == _F) {
			resetHeight();
			if (state.referential == _U) {
				Bi();
			}
			else if (state.referential == _R) {
				if (state.rotator == 2) {
					Ui();
				}
				Bi(); H3(); U(); D3(); B();
			}
		}
		else if (this->state.referential == _R) {
			resetHeight();
			if (state.rotator == 0) {
				U();
			}
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
			resetHeight();
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

void Robot::endMove() {
	resetHeight();
	/*if (this->state.balancier) {
		Bi();
	}*/
}

RobotController& Robot::getController(){
	return this->controller;
}

void Robot::setCameraId(int camera_id){
	this->camera_id = camera_id;
}

int Robot::getCameraId(){
	return this->camera_id;
}

void Robot::setSquareCount(int square_count){
	this->square_count = square_count;
}

int Robot::getSquareCount(){
	return this->square_count;
}

void Robot::setWindowName(String window_name){
	this->window_name = window_name;
}

String Robot::getWindowName(){
	return this->window_name;
}

bool Robot::filterRect(Rect rec){
	/* Delimited a zone on the frame to analyze */
	if (rec.x < 100 || rec.x > 450){
		return false;
	}
	else if (rec.y < 30 || rec.y > 300){
		return false;
	}

	/* Size of the shape */
	if (rec.width == 78 && rec.height == 78){
		return true;
	}

	if (rec.width > 75 && rec.width < 85){
		if (rec.height > 75 && rec.height < 85){
			return true;
		}
	}

	return false;
}

String Robot::defineColorText(int color_id){
	switch (color_id){
		case 0:
			return "W";
		case 1:
			return "G";
		case 2:
			return "R";
		case 3:
			return "B";
		case 4:
			return "O";
		case 5:
			return "Y";
		default:
			return "";
	}
}

std::vector<std::vector<SquareRubik>> Robot::launchCapture(){
	VideoCapture cap(this->camera_id);

	cap.set(CV_CAP_PROP_SETTINGS, 1); // Show the properties window

	// Handle error when opening the camera
	if (!cap.isOpened()) 
	{
		std::cout << "Cannot open the video file" << std::endl;
		return {};
	}

	namedWindow(this->getWindowName(), CV_WINDOW_AUTOSIZE);

	// Variables's initialization
	std::vector<std::vector<cv::Point> > contours;
	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<SquareRubik>> results;
	std::vector<std::vector<std::vector<cv::Point>>> finalContours;

	Mat frame_RGB;
	Mat filter;
	Mat frame_HSV;
	Mat frame_threshed;
	Mat imgray;
	Mat result;

	int nb_capture = 0;

	// Detect frame while we have the all sides of the Rubik's Cube
	while (nb_capture < NB_CAPTURE)
	{
		std::vector<SquareRubik> points;

		this->setSquareCount(0); // Initialization : 0 squares found on the actual side
		cap.read(frame_RGB); // Read a new frame from video
		bilateralFilter(frame_RGB, filter, 9, 75, 75);
		cvtColor(filter, frame_HSV, cv::COLOR_BGR2HSV); // Change from RGB to HSV

		// For each color, detect if there is the color in the frame
		for (int i = 0; i < minColor.size(); i++){
			inRange(frame_HSV, minColor[i], maxColor[i], frame_threshed);
			imgray = frame_threshed;
			threshold(frame_threshed, result, 127, 255, 0);

			findContours(result, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
			finalContours.push_back(contours);
		}

		// For each shape found, we filter it and add it if it match
		for (unsigned int j = 0; j < finalContours.size(); j++){
			String text = defineColorText(j); // Letter to display on the camera Window

			for (unsigned int i = 0; i < finalContours[j].size(); i++){
				Rect rec = cv::boundingRect(finalContours[j][i]);

				if (filterRect(rec)){
					this->setSquareCount(this->getSquareCount() + 1);
					rectangle(frame_RGB, rec, Scalar(0, 255, 0), 2);
					putText(frame_RGB, text, cv::Point2f(rec.x + rec.width / 2, rec.y + rec.height / 2), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0, 0));
					points.push_back(SquareRubik(cv::Point2f(rec.x, rec.y), RubikColor(j)));
				}
			}
		}

		imshow(this->getWindowName(), frame_RGB); // Display the RGB frame with the found squares

		// If the camera doesn't detect the 9 squares, the user can press 's' to move to the next step
		if (cv::waitKey(20) == 's'){
			results.push_back(points);
			nb_capture++;
			// Change the position of the Rubik's cube to get the next side
			if (!this->setRobotPosition(nb_capture)){
				throw RobotPositionException("Failed when changing position of the Rubik's cube");
			}
		}
		else if (this->getSquareCount() == 9) { // Found all cube of a side!
			points = sortResult(points);

			// Convention in order to have the a ordered list which match with the algorithm part
			if (nb_capture == 5){
				std::reverse(points.begin(), points.end());
			}

			results.push_back(points);

			nb_capture++;
			// Change the position of the Rubik's cube to get the next side
			if (!this->setRobotPosition(nb_capture)){
				throw RobotPositionException("Failed when changing position of the Rubik's cube");
			}
		}

		finalContours.clear();
		hierarchy.clear();
	}

	cv::destroyWindow(this->window_name);

	// Convention in order to have the a ordered list which match with the algorithm part
	std::swap(results[0], results[5]);
	std::swap(results[1], results[3]);
	std::swap(results[2], results[4]);

	return results;
}

bool Robot::setRobotPosition(int id){
	switch (id){
		case 1:
			if(!this->H3()) return false;
			if(!this->U()) return false;
			if(!this->D3()) return false;
			return true;
		case 2:
			if(!this->Ui()) return false;
			if(!this->H3()) return false;
			if(!this->U()) return false;
			if(!this->D3()) return false;
			return true;
		case 3:
			if (!this->Ui()) return false;
			if (!this->H3()) return false;
			if (!this->U()) return false;
			if (!this->D3()) return false;
			return true;
		case 4:
			if (!this->Bi()) return false;
			if (!this->H3()) return false;
			if (!this->B()) return false;
			return true;
		case 5:
			if (!this->H3()) return false;
			if (!this->Ui()) return false;
			if (!this->Ui()) return false;
			if (!this->D3()) return false;
			return true;
		default:
			return false;
	}

}

std::vector<SquareRubik> Robot::sortResult(std::vector<SquareRubik> points){
	/*We sort the list with the Y axis to have the 3 lines not ordered yet. Then we sort each line to have the final result : 
			ADECFBIGH --> BCA - FED - GIH --> ABC - DEF - GHI with (xa < xb < xc and xd < xd < xe and ...)
												ABC			012
												DEF  ==>	345
												GHI			678
	*/
	std::sort(points.begin(), points.end(), Robot::sortYAxis);
	std::sort(points.begin(), points.begin() + 3, Robot::sortXAxis);
	std::sort(points.begin() + 3, points.begin() + 6, Robot::sortXAxis);
	std::sort(points.begin() + 6, points.end(), Robot::sortXAxis);

	return points;
}

