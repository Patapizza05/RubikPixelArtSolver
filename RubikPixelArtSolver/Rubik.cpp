#include "Rubik.h"
#include "RubikColor.h"

Rubik::Rubik(int pieces[]) 	
{
	initCornersAndEdges(pieces);
}

void Rubik::initCornersAndEdges(int pieces[]) {
	int lines[9][12] = {
		{ -1, -1, -1, 6, 4, 7, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 6, 1, 7, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 16, 12, 9, -1, -1, -1, -1, -1, -1 },
		{ 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22 },
		{ 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11 },
		{ 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12 },
		{ -1, -1, -1, 10, 14, 19, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 8, 2, 9, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 4, 5, 5, -1, -1, -1, -1, -1, -1 }
	};

	int index;
	int i = 0;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 12; x++) {
			index = lines[y][x];

			if (index != -1)
			{
				if (y % 3 == 0 || y % 3 == 2)
				{
					if (x % 3 == 0 || x % 3 == 2)
					{
						addCorner(index, pieces[i]);
						i++;
					}
					else
					{
						addEdge(index, pieces[i]);
						i++;
					}

				}
				else
				{
					if (x % 3 == 0 || x % 3 == 2)
					{
						addEdge(index, pieces[i]);
						i++;
					}
				}
			}
		}
	}
}

void Rubik::addCorner(int i, int number)
{
	this->corners[i] = new CornerFace(number, RubikColor::RED);
}

void Rubik::addEdge(int i, int number)
{
	this->edges[i] = new EdgeFace(number, RubikColor::RED);
}

Rubik::~Rubik() {
	for (int i = 0; i < 24; i++) {
		free(this->corners[i]);
		free(this->edges[i]);
	}
}


void Rubik::printCube() {
	int number;
	int lines[9][12] = {
		{ -1, -1, -1, 6, 4, 7, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 6, 1, 7, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 16, 12, 9, -1, -1, -1, -1, -1, -1 },
		{ 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22 },
		{ 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11 },
		{ 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12 },
		{ -1, -1, -1, 10, 14, 19, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 8, 2, 9, -1, -1, -1, -1, -1, -1 },
		{ -1, -1, -1, 4, 5, 5, -1, -1, -1, -1, -1, -1 }
	};
	int index;

	for (int y = 0; y < 9; y++) {

		std::cout << std::endl;


		for (int x = 0; x < 12; x++) {

			index = lines[y][x];

			if (index == -1) {
				std::cout << "  ";
			}
			else
			{
				if (y % 3 == 0 || y % 3 == 2)
				{
					if (x % 3 == 0 || x % 3 == 2)
					{
						number = this->corners[lines[y][x]]->getNumber();
						if (number < 10) {
							std::cout << " ";
						}
						std::cout << number;
					}
					else
					{
						number = this->edges[lines[y][x]]->getNumber();
						if (number < 10) {
							std::cout << " ";
						}
						std::cout << number;
					}

				}
				else
				{
					if (x % 3 == 0 || x % 3 == 2)
					{
						number = this->edges[lines[y][x]]->getNumber();
						if (number < 10) {
							std::cout << " ";
						}
						std::cout << number;
					}
					else
					{
						std::cout << " m";
					}
				}
			}

			std::cout << " ";

		}
	}
}

void Rubik::translate(Face * array[], int i1, int i2, int i3, int i4) {
	Face * temp = array[i1];
	array[i1] = array[i2];
	array[i2] = array[i3];
	array[i3] = array[i4];
	array[i4] = temp;
}

void Rubik::R() {

}

void Rubik::Ri() {

}
//void R2();
void Rubik::L() {

}
void Rubik::Li() {

}
//void L2();
void Rubik::U() {

}
void Rubik::Ui() {

}
//void U2();
void Rubik::B() {

}
void Rubik::Bi() {

}
//void B2();
void Rubik::F() {

}
void Rubik::Fi() {

}
//void F2();
void Rubik::D() {

}
void Rubik::Di() {

}