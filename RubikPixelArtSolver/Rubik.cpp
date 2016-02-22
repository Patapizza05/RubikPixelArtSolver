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

void Rubik::translate(CornerFace * array[], int i1, int i2, int i3, int i4) {
	this->translate((Face**)array, i1, i2, i3, i4);
}
void Rubik::translate(EdgeFace * array[], int i1, int i2, int i3, int i4) {
	this->translate((Face**)array, i1, i2, i3, i4);
}

void Rubik::Ri() {
	translate(this->corners, 9, 15, 5, 3);
	translate(this->corners, 7, 21, 19, 1);
	translate(this->corners, 17, 23, 13, 11);
	translate(this->edges, 7, 22, 9, 1);
	translate(this->edges, 19, 10, 21, 13);
}

void Rubik::R() {
	translate(this->corners, 3,5,15,9);
	translate(this->corners, 1,19,21,7);
	translate(this->corners,11,13,23,17);
	translate(this->edges, 1,9,22,7);
	translate(this->edges, 13,21,10,19);
}
//void R2();
void Rubik::Li() {
	translate(this->corners, 16, 2, 4, 22);
	translate(this->corners, 6, 0, 10, 12);
	translate(this->corners, 8, 18, 20, 14);
	translate(this->edges, 6, 3, 8, 11);
	translate(this->edges, 18, 15, 20, 23);
}
void Rubik::L() {
	translate(this->corners, 22, 4, 2, 16);
	translate(this->corners, 12, 10, 0, 6);
	translate(this->corners, 14, 20, 18, 8);
	translate(this->edges, 11, 8, 3, 6);
	translate(this->edges, 23, 20, 15, 18);
}
//void L2();
void Rubik::Ui() {
	translate(this->corners, 9, 16, 6, 7);
	translate(this->corners, 1, 8, 22, 23);
	translate(this->corners, 0, 14, 15, 17);
	translate(this->edges, 4, 7, 12, 6);
	translate(this->edges, 0, 18, 16, 19);
}
void Rubik::U() {
	translate(this->corners, 7, 6, 16, 9);
	translate(this->corners, 23, 22, 8, 1);
	translate(this->corners, 17, 15, 14, 0);
	translate(this->edges, 6, 12, 7, 4);
	translate(this->edges, 19, 16, 18, 0);
}
//void U2();
void Rubik::Bi() {
	translate(this->corners, 7, 14, 4, 13);
	translate(this->corners, 6, 20, 5, 23);
	translate(this->corners, 22, 12, 21, 15);
	translate(this->edges, 4, 23, 5, 10);
	translate(this->edges, 16, 11, 17, 22);
}
void Rubik::B() {
	translate(this->corners, 13, 4, 14, 7);
	translate(this->corners, 23, 5, 20, 6);
	translate(this->corners, 15, 21, 12, 22);
	translate(this->edges, 10, 5, 23, 4);
	translate(this->edges, 22, 17, 11, 16);
}
//void B2();
void Rubik::Fi() {
	translate(this->corners, 9, 11, 10, 8);
	translate(this->corners, 16, 17, 19, 18);
	translate(this->corners, 0, 1, 3, 2);
	translate(this->edges, 12, 13, 14, 15);
	translate(this->edges, 0, 1, 2, 3);
}
void Rubik::F() {
	translate(this->corners, 8, 10, 11, 9);
	translate(this->corners, 18, 19, 17, 16);
	translate(this->corners, 2, 3, 1, 0);
	translate(this->edges, 15, 14, 13, 12);
	translate(this->edges, 3, 2, 1, 0);
}
//void F2();
void Rubik::Di() {
	translate(this->corners, 3, 13, 12, 18);
	translate(this->corners, 2, 11, 21, 20);
	translate(this->corners, 19, 5, 4, 10);
	translate(this->edges, 2, 21, 17, 20);
	translate(this->edges, 14, 9, 5, 8);
}
void Rubik::D() {
	translate(this->corners, 18, 12, 13, 3);
	translate(this->corners, 20, 21, 11, 2);
	translate(this->corners, 10, 4, 5, 19);
	translate(this->edges, 20, 17, 21, 2);
	translate(this->edges, 8, 5, 9, 14);
}