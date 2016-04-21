#include "Robot.h"

/* White - Green - Red - Blue - Orange - Yellow */
std::vector<Scalar> minColor{ Scalar(70, 20, 130), Scalar(60, 110, 110), Scalar(120, 120, 140), Scalar(80, 180, 190), Scalar(5, 150, 150), Scalar(20, 100, 100) };
std::vector<Scalar> maxColor{ Scalar(180, 110, 255), Scalar(100, 220, 250), Scalar(180, 250, 200), Scalar(120, 255, 255), Scalar(15, 235, 250), Scalar(40, 255, 255) };

Robot::Robot(){
	this->state = RobotState(0, false, 1, _U);
	this->setCameraId(0);
	this->setSquareCount(0);
	this->setWindowName("Default Rubik Window");
}

Robot::Robot(int camera_id){
	this->setCameraId(camera_id);
	this->setSquareCount(0);
	this->setWindowName("Default Rubik Window");
}

Robot::Robot(String window_name, int camera_id){
	this->setCameraId(camera_id);
	this->setSquareCount(0);
	this->setWindowName(window_name);
}

void Robot::sendRobotMoves(std::vector<std::string> rubikMoves) {
	for (unsigned int i = 0; i < rubikMoves.size(); i++) {
		this->addMove(rubikMoves[i]);
	}
	this->endMove();
}

void Robot::U0() {
	this->controller.send(robot_U0[0]);

	if (this->controller.read() == robot_U0[0] || ROBOT_DEBUG){
		rmoves.push_back(robot_U0);
		state.rotator = 0;
	}
}

void Robot::U1() {
	this->controller.send(robot_U1[0]);

	if (this->controller.read() == robot_U1[0] || ROBOT_DEBUG){
		rmoves.push_back(robot_U1);
		state.rotator = 1;
	}
}

void Robot::U2() {
	this->controller.send(robot_U2[0]);

	if (this->controller.read() == robot_U2[0] || ROBOT_DEBUG){
		rmoves.push_back(robot_U2);
		state.rotator = 2;
	}
}

void Robot::U() {
	if (state.rotator == 0) {
		U1();
	}
	else if (state.rotator == 1) {
		U2();
	}
	
}
void Robot::Ui() {
	if (state.rotator == 1) {
		U0();
	}
	else if (state.rotator == 2) {
		U1();
	}
}
void Robot::H1() {
	this->controller.send(robot_H1[0]);

	if (this->controller.read() == robot_H1[0] || ROBOT_DEBUG) {
		state.height += 1;
		rmoves.push_back(robot_H1);
	}
}
void Robot::H2() {
	this->controller.send(robot_H2[0]);

	if (this->controller.read() == robot_H2[0] || ROBOT_DEBUG) {
		state.height += 2;
		rmoves.push_back(robot_H2);
	}
}
void Robot::H3() {
	this->controller.send(robot_H3[0]);

	if (this->controller.read() == robot_H3[0] || ROBOT_DEBUG) {
		state.height += 3;
		rmoves.push_back(robot_H3);
	}
}
void Robot::D1() {
	this->controller.send(robot_D1[0]);

	if (this->controller.read() == robot_D1[0] || ROBOT_DEBUG) {
		state.height -= 1;
		rmoves.push_back(robot_D1);
	}
}
void Robot::D2() {
	this->controller.send(robot_D2[0]);

	if (this->controller.read() == robot_D2[0] || ROBOT_DEBUG) {
		state.height -= 2;
		rmoves.push_back(robot_D2);
	}
}
void Robot::D3() {
	this->controller.send(robot_D3[0]);

	if (this->controller.read() == robot_D3[0] || ROBOT_DEBUG) {
		state.height -= 3;
		rmoves.push_back(robot_D3);
	}
}
void Robot::Bi() {
	this->controller.send(robot_Bi[0]);

	if (this->controller.read() == robot_Bi[0] || ROBOT_DEBUG) {
		state.balancier = true;
		rmoves.push_back(robot_Bi);
	}
}

void Robot::B() {
	this->controller.send(robot_B[0]);

	if (this->controller.read() == robot_B[0] || ROBOT_DEBUG) {
		state.balancier = false;
		rmoves.push_back(robot_B);
	}
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
				if (state.rotator == 2) {
					Ui();
				}
				H3(); U(); D3(); B();
			}
		}
		else if (this->state.referential == _F) {
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

RobotController Robot::getController(){
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

	if (rec.x < 100 || rec.x > 450){
		return false;
	}
	else if (rec.y < 30 || rec.y > 300){
		return false;
	}

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

void Robot::launchCapture(){

	VideoCapture cap(this->camera_id);

	cap.set(CV_CAP_PROP_SETTINGS, 1);

	if (!cap.isOpened())  // if not success, exit program
	{
		std::cout << "Cannot open the video file" << std::endl;
		return;
	}

	namedWindow(this->getWindowName(), CV_WINDOW_AUTOSIZE);

	std::vector<std::vector<cv::Point> > contours;
	std::vector<Vec4i> hierarchy;

	Mat frame_RGB;
	Mat filter;
	Mat frame_HSV;
	Mat frame_threshed;
	Mat imgray;
	Mat result;

	std::vector<std::vector<SquareRubik>> results;
	std::vector<std::vector<std::vector<cv::Point>>> finalContours;

	int nb_capture = 0;

	while (nb_capture < NB_CAPTURE)
	{
		std::vector<SquareRubik> points;

		this->setSquareCount(0);
		cap.read(frame_RGB); // read a new frame from video
		bilateralFilter(frame_RGB, filter, 9, 75, 75);
		cvtColor(filter, frame_HSV, cv::COLOR_BGR2HSV);

		for (int i = 0; i < minColor.size(); i++){
			inRange(frame_HSV, minColor[i], maxColor[i], frame_threshed);
			imgray = frame_threshed;

			threshold(frame_threshed, result, 127, 255, 0);

			findContours(result, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
			finalContours.push_back(contours);
		}

		for (unsigned int j = 0; j < finalContours.size(); j++){
			String text = defineColorText(j);

			for (unsigned int i = 0; i < finalContours[j].size(); i++){
				Rect rec = cv::boundingRect(finalContours[j][i]);

				if (filterRect(rec)){
					this->setSquareCount(this->getSquareCount() + 1);
					rectangle(frame_RGB, rec, Scalar(0, 255, 0), 2);
					putText(frame_RGB, text, cv::Point2f(rec.x + rec.width / 2, rec.y + rec.height / 2), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0, 0));
					points.push_back(SquareRubik(cv::Point2f(rec.x, rec.y), ColorRubik(j)));
				}
			}
		}

		imshow(this->getWindowName(), frame_RGB);

		if (cv::waitKey(20) == 's'){
			results.push_back(points);
			std::cout << "next" << std::endl;
			nb_capture++;
			this->setRobotPosition(nb_capture);
		}
		else if (this->getSquareCount() == 9) { // Found all cube of a side!
			points = sortResult(points);

			if (nb_capture == 5){
				std::reverse(points.begin(), points.end());
			}

			printSide(points);
			results.push_back(points);

			nb_capture++;
			this->setRobotPosition(nb_capture);
		}

		finalContours.clear();
		hierarchy.clear();
		if (cv::waitKey(20) == 'q') return;
	}

	cv::destroyWindow(this->window_name);

	std::swap(results[0], results[5]);
	std::swap(results[1], results[3]);
	std::swap(results[2], results[4]);

	return;

}

bool Robot::setRobotPosition(int id){
	switch (id){
		case 1:
			this->H3();
			this->U();
			this->D3();
			//H3 - U - D3
			return true;
		case 2:
			this->Ui();
			this->H3();
			this->U();
			this->D3();
			//Ui - H3 - U - D3
			return true;
		case 3:
			this->Ui();
			this->H3();
			this->U();
			this->D3();
			// Ui - H3 - U - D3
			return true;
		case 4:
			this->Bi();
			this->H3();
			this->B();
			// Bi - H3 - B
			return true;
		case 5:
			this->H3();
			this->Ui();
			this->Ui();
			this->D3();
			// H3 - Ui - Ui - D3
			return true;
		default:
			return false;
	}

}

void Robot::printSide(std::vector<SquareRubik> points){
	for (int i = 0; i < points.size(); i++){
		std::cout << points.at(i).color;
		if ((i + 1) % 3 == 0){
			std::cout << std::endl;
		}
	}
}

std::vector<SquareRubik> Robot::sortResult(std::vector<SquareRubik> points){
	std::sort(points.begin(), points.end(), Robot::sortYAxis);
	std::sort(points.begin(), points.begin() + 3, Robot::sortXAxis);
	std::sort(points.begin() + 3, points.begin() + 6, Robot::sortXAxis);
	std::sort(points.begin() + 6, points.end(), Robot::sortXAxis);

	return points;
}

