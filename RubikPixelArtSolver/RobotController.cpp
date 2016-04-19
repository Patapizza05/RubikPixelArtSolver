#include "RobotController.h"

RobotController::RobotController(){ }

RobotController::RobotController(std::string port){
	this->port = port;
}

bool RobotController::send(unsigned char msg){
	this->sendSByte(msg);
	if (this->read() == msg){
		return true;
	}
	else {
		return false;
	}
}

unsigned char RobotController::read(){
	return this->readSByte();
}

bool RobotController::initPort(){
	if (openPort() && setupPort()) {
		std::cout << "Port open and configure" << std::endl;
		return true;
	}
	else {
		std::cout << "Error when opening and setting port" << std::endl;
		return false;
	}
}

void RobotController::setPort(std::string port){
	this->port = port;
}

std::string RobotController::getPort(){
	return this->port;
}

bool RobotController::sendSByte(unsigned char msg){
	DWORD dwWritten;
	if (WriteFile(hComm, &msg, sizeof(msg), &dwWritten, 0)) {
		std::cout << "wrote byte " << msg << " to serial port" << std::endl;
		return true;
	}
	else {
		std::cout << "serial port write failed" << std::endl;
		return false;
	}
}

unsigned char RobotController::readSByte(){
	DWORD dwRead;
	unsigned char lpBuf;

	ReadFile(hComm,				// handle of file to read
		&lpBuf,					// address of buffer that receives data
		sizeof(lpBuf),			// number of bytes to read
		&dwRead,					// address of number of bytes read
		0);						// address of structure for data
	std::cout << "Read byte " << lpBuf << " from serial port" << std::endl;
	return lpBuf;
}

bool RobotController::openPort(){
	std::cout << "-- Opening Port " << this->port << " --" << std::endl;

	hComm = CreateFile(this->port.c_str(),					// pointer to name of the file 
		GENERIC_READ | GENERIC_WRITE,	// access (read-write) mode 
		0,								// share mode 
		0,								// pointer to security attributes 
		OPEN_EXISTING,					// how to create
		0,								// file attributes
		0);							// handle to file with attributes to copy 


	if (hComm == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open serial port " << this->port << std::endl;
		return false;
	}
	else {
		std::cout << "Serial port " << this->port << " opened" << std::endl;
		return true;
	}
}

bool RobotController::closePort(){
	if (CloseHandle(hComm)) {
		std::cout << "Port closed" << std::endl;
		return true;
	}
	else {
		std::cout << "Port closed failed" << std::endl;
		return false;
	}
}

bool RobotController::setupPort(){
	DCB dcb;

	std::cout << "-- Getting DCB --" << std::endl;

	if (!GetCommState(hComm, &dcb)) {
		std::cout << "GetDCB failed" << std::endl;
		return false;
	}

	dcb.BaudRate = 9600;
	dcb.fParity = FALSE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;

	std::cout << "DCB ready for use" << std::endl;
	if (!SetCommState(hComm, &dcb)) {
		std::cout << "Failed to set port state (" << GetLastError() << ")" << std::endl;
		return false;
	}
	else {
		std::cout << "Port setup complete" << std::endl;
		return true;
	}
}