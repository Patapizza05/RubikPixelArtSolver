#include "Rubik.h"

Rubik::Rubik() {
	for (int i = 0; i < 24; i++) {
		this->corners[i].number = i;
		this->edges[i].number = i;
	}
}

void Rubik::printCube() {
	std::cout << "Rubik Test" << std::endl;
	std::cout << "Edges :" << std::endl;
	for (int i = 0; i < 24; i++) {
		std::cout << this->edges[i].number << "\t";
	}
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Corners :" << std::endl;
	for (int i = 0; i < 24; i++) {
		std::cout << this->corners[i].number << "\t";
	}
	std::cout << std::endl;
}