#ifndef ROBOT_H

#define ROBOT_H

#include "RobotState.h"
#include "RobotController.h"
#include "Rubik.h"
#include "Utils.h"
#include <string>
#include <vector>

#define NB_CAPTURE 6

class Robot {
public:
	Robot();
	Robot(int);
	Robot(cv::String, int);
	void addMove(std::string rubikMove);
	void endMove();
	std::vector<std::string> rmoves;
	RobotController getController();

	void launchCapture();
	void setCameraId(int);
	int getCameraId();
	void setSquareCount(int);
	int getSquareCount();
	void setWindowName(cv::String);
	cv::String getWindowName();
	bool setRobotPosition(int);
	void printSide(std::vector<SquareRubik>);
	std::vector<SquareRubik> sortResult(std::vector<SquareRubik>);
	static bool sortXAxis(SquareRubik r1, SquareRubik r2) { return r1.position.x < r2.position.x; };
	static bool sortYAxis(SquareRubik r1, SquareRubik r2) { return r1.position.y < r2.position.y; };
private:
	RobotState state;
	RobotController controller;
	bool U0();
	bool U1();
	bool U2();
	bool U();
	bool Ui();
	bool H1();
	bool H2();
	bool H3();
	bool D1();
	bool D2();
	bool D3();
	bool Bi();
	bool B();
	void resetHeight();
	void addHeight(int);
	void goDown(int);
	void goUp(int);
	void rotate(int);

	int camera_id;
	int square_count;
	bool filterRect(cv::Rect);
	cv::String window_name;
	cv::String defineColorText(int);
};

#endif