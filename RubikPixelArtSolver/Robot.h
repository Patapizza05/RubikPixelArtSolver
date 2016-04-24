#ifndef ROBOT_H

#define ROBOT_H

#include "RobotState.h"
#include "RobotController.h"
#include "Face.h"
#include "Utils.h"
#include <string>
#include <vector>

#define NB_CAPTURE 6
#define ROBOT_DEBUG 1

/// <summary>
/// Class representing the robot
/// </summary>
class Robot {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Robot"/> class.
	/// </summary>
	Robot(int=0, cv::String = "Default Window Name");
	/// <summary>
	/// Converts and sends the rubik moves to the robot. Fills the robotMoves array
	/// </summary>
	/// <param name="rubikMoves">The rubik moves.</param>
	void sendRubikMoves(std::vector<std::string> rubikMoves);
	
	/// <summary>
	/// Gets the robot moves filled by the "sendRubikMoves" function
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> getRobotMoves() { return rmoves; };
	
	/// <summary>
	/// Computes the cost of a rubik move.
	/// </summary>
	/// <param name="rubikMoves">The rubik moves: New moves to send to the robot</param>
	/// <param name="previousRubikMove">The previous rubik move: Permits to determine the state of the robot before performing the new moves</param>
	/// <returns></returns>
	int getRubikMovesCost(std::vector<std::string> rubikMoves, std::string previousRubikMove);
	
	/// <summary>
	/// Gets the controller.
	/// </summary>
	/// <returns>The Robot Controller</returns>
	RobotController& getController();
	
	/// <summary>
	/// Launches the capture with OpenCV and the camera
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<SquareRubik>> launchCapture();
	
	/// <summary>
	/// Sets the camera identifier.
	/// </summary>
	/// <param name="camera_id">The camera id</param>
	void setCameraId(int);
	
	/// <summary>
	/// Gets the camera identifier.
	/// </summary>
	/// <returns>The camera id</returns>
	int getCameraId();
	
	/// <summary>
	/// Sets the square count.
	/// </summary>
	/// <param name="">The .</param>
	void setSquareCount(int);
	
	/// <summary>
	/// Gets the square count.
	/// </summary>
	/// <returns></returns>
	int getSquareCount();
	
	/// <summary>
	/// Sets the name of the window.
	/// </summary>
	/// <param name="">The .</param>
	void setWindowName(cv::String);
	
	/// <summary>
	/// Gets the name of the window.
	/// </summary>
	/// <returns></returns>
	cv::String getWindowName();
	
	/// <summary>
	/// Sets the robot position.
	/// </summary>
	/// <param name="">The .</param>
	/// <returns></returns>
	bool setRobotPosition(int);
	
	/// <summary>
	/// Prints the side.
	/// </summary>
	/// <param name="">Array of SquareRubik</param>
	void printSide(std::vector<SquareRubik>);
	std::vector<SquareRubik> sortResult(std::vector<SquareRubik>);
	
	/// <summary>
	/// Sorts the x axis.
	/// </summary>
	/// <param name="r1">The first SquareRubik</param>
	/// <param name="r2">The second SquareRubik</param>
	/// <returns></returns>
	static bool sortXAxis(SquareRubik r1, SquareRubik r2) { return r1.position.x < r2.position.x; };
	
	/// <summary>
	/// Sorts the y axis.
	/// </summary>
	/// <param name="r1">The r1.</param>
	/// <param name="r2">The r2.</param>
	/// <returns></returns>
	static bool sortYAxis(SquareRubik r1, SquareRubik r2) { return r1.position.y < r2.position.y; };

private:
	RobotState state;
	RobotController controller;

	/// <summary>
	/// Converts rubik move and sends the associated robot moves
	/// </summary>
	/// <param name="rubikMove">The rubik move.</param>
	void addMove(std::string rubikMove);
	
	/// <summary>
	/// Put the rubik's cube down
	/// </summary>
	void endMove();
	
	/// <summary>
	/// The robot moves
	/// </summary>
	std::vector<std::string> rmoves;
	
	/// <summary>
	/// Turns the top motor to 180°
	/// </summary>
	/// <returns></returns>
	bool U0();
	
	/// <summary>
	/// Turns the top motor to 90°
	/// </summary>
	/// <returns></returns>
	bool U1();
	
	/// <summary>
	/// Turns the top motor to 0°
	/// </summary>
	/// <returns></returns>
	bool U2();
	
	/// <summary>
	/// Adds 90° to the motor position
	/// </summary>
	/// <returns></returns>
	bool U();
	
	/// <summary>
	/// Removes 90° from the motor position
	/// </summary>
	/// <returns></returns>
	bool Ui();
	
	/// <summary>
	/// Goes up from height 0 to height 1
	/// </summary>
	/// <returns></returns>
	bool H0_to_1();
	
	/// <summary>
	/// Goes up from height 0 to height 2
	/// </summary>
	/// <returns></returns>
	bool H0_to_2();
	
	/// <summary>
	/// Goes up from height 0 to height 3
	/// </summary>
	/// <returns></returns>
	bool H0_to_3();
	
	/// <summary>
	/// Goes up from height 1 to height 2
	/// </summary>
	/// <returns></returns>
	bool H1_to_2();
	
	/// <summary>
	/// Goes up from height 1 to height 3
	/// </summary>
	/// <returns></returns>
	bool H1_to_3();
	
	/// <summary>
	/// Goes up from height 2 to height 3
	/// </summary>
	/// <returns></returns>
	bool H2_to_3();
	
	/// <summary>
	/// Goes down from height 3 to height 0
	/// </summary>
	/// <returns></returns>
	bool D3_to_0();
	
	/// <summary>
	/// Goes down from height 2 to height 0
	/// </summary>
	/// <returns></returns>
	bool D2_to_0();
	
	/// <summary>
	/// Goes down from height 1 to height 0
	/// </summary>
	/// <returns></returns>
	bool D1_to_0();
	
	/// <summary>
	/// Goes down from height 2 to height 1
	/// </summary>
	/// <returns></returns>
	bool D2_to_1();
	
	/// <summary>
	/// Goes down from height 3 to height 2
	/// </summary>
	/// <returns></returns>
	bool D3_to_2();
	
	/// <summary>
	/// Goes down from height 3 to height 1
	/// </summary>
	/// <returns></returns>
	bool D3_to_1();
	
	/// <summary>
	/// Goes up one level
	/// </summary>
	/// <returns></returns>
	bool H1();
	
	/// <summary> Goes up two levels
	/// </summary>
	/// <returns></returns>
	bool H2();
	
	/// <summary> Goes up three levels
	/// </summary>
	/// <returns></returns>
	bool H3();
	
	/// <summary> Goes down one level
	/// </summary>
	/// <returns></returns>
	bool D1();
	
	/// <summary> Goes down two levels
	/// </summary>
	/// <returns></returns>
	bool D2();
	
	/// <summary> Goes down three levels
	/// </summary>
	/// <returns></returns>
	bool D3();


	bool Bi();
	bool B();
	void resetHeight();
	void addHeight(int);
	void goDown(int);
	void goUp(int);
	void rotate(int);

	bool sendMessageAndRead(std::string);

	int camera_id;
	int square_count;
	bool filterRect(cv::Rect);
	cv::String window_name;
	cv::String defineColorText(int);
};

#endif