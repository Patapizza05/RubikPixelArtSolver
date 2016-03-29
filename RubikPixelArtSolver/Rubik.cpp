#include "Rubik.h"
#include "RubikColor.h"

bool Rubik::debug = false;

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
					else
					{
						addMiddle(index, pieces[i]);
						i++;
					}
				}
			}
		}
	}
}

void Rubik::addCorner(int i, int number)
{
	RubikColor color;
	switch (i) {
	case 0:
	case 1:
	case 2:
	case 3:
		color = RubikColor::RED;
		break;
	case 6:
	case 7:
	case 9:
	case 16:
		color = RubikColor::WHITE;
		break;
	case 10:
	case 19:
	case 4:
	case 5:
		color = RubikColor::YELLOW;
		break;
	case 14:
	case 8:
	case 18:
	case 20:
		color = RubikColor::GREEN;
		break;
	case 17:
	case 23:
	case 13:
	case 11:
		color = RubikColor::BLUE;
		break;
	case 15:
	case 22:
	case 12:
	case 21:
		color = RubikColor::ORANGE;
		break;
	default:
		error();
		break;
	}
	this->corners[i] = new CornerFace(number, color);
}

void Rubik::addEdge(int i, int number)
{
	RubikColor color;
	switch (i) {
	case 0:
	case 1:
	case 2:
	case 3:
		color = RubikColor::RED;
		break;
	case 4:
	case 7:
	case 12:
	case 6:
		color = RubikColor::WHITE;
		break;
	case 14:
	case 9:
	case 5:
	case 8:
		color = RubikColor::YELLOW;
		break;
	case 18:
	case 20:
	case 23:
	case 15:
		color = RubikColor::GREEN;
		break;
	case 10:
	case 13:
	case 19:
	case 21:
		color = RubikColor::BLUE;
		break;
	case 11:
	case 16:
	case 17:
	case 22:
		color = RubikColor::ORANGE;
		break;
	default:
		error();
		break;
	}
	this->edges[i] = new EdgeFace(number, color);
}

void Rubik::addMiddle(int i, int number)
{
	RubikColor color;
	switch (i) {
	case 0:
		color = RubikColor::RED;
		break;
	case 1:
		color = RubikColor::WHITE;
		break;
	case 2:
		color = RubikColor::YELLOW;
		break;
	case 3:
		color = RubikColor::GREEN;
		break;
	case 4:
		color = RubikColor::BLUE;
		break;
	case 5:
		color = RubikColor::ORANGE;
		break;
	default:
		error();
		break;
	}
	this->middle[i] = new MiddleFace(number, color);
}

void Rubik::error() {
	//exception
}

Rubik::~Rubik() {
	for (int i = 0; i < 24; i++) {
		delete this->corners[i];
		delete this->edges[i];
	}
	for (int i = 0; i < 6; i++) {
		delete this->middle[i];
	}
	this->moves.clear();
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
						std::cout << setcolor(this->corners[lines[y][x]]->getColor()) << number;
					}
					else
					{
						number = this->edges[lines[y][x]]->getNumber();
						if (number < 10) {
							std::cout << " ";
						}
						std::cout << setcolor(this->edges[lines[y][x]]->getColor()) << number;
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
						std::cout << setcolor(this->edges[lines[y][x]]->getColor()) << number;
					}
					else
					{
						number = this->middle[lines[y][x]]->getNumber();
						std::cout << " " << setcolor(this->middle[lines[y][x]]->getColor()) << number;
					}
				}
			}

			std::cout << " ";

		}
	}
	std::cout << setcolor(RubikColor::WHITE) << std::endl;
}

bool Rubik::checkRubik(RubikColor colors[]) {
	int rotate = 0;
	bool result = false;
	int i = 0;
	while (!result && rotate < 4) {
		if (this->corners[6]->getColor() == colors[i++] 
				&& this->edges[4]->getColor() == colors[i++] 
					&& this->corners[7]->getColor() == colors[i++]
			&& this->edges[6]->getColor() == colors[i++] 
				&& this->middle[1]->getColor() == colors[i++] 
					&& this->edges[7]->getColor() == colors[i++]
			&& this->corners[16]->getColor() == colors[i++] 
				&& this->edges[12]->getColor() == colors[i++]
					&& this->corners[9]->getColor() == colors[i++])
		{
			result = true;
		}
		rotate++;
		U();
	}

	/*while (rotate < 0)
	{
		Ui();
		rotate--;
	}*/


	return result;
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

void Rubik::translate(MiddleFace * array[], int i1, int i2, int i3, int i4) {
	this->translate((Face**)array, i1, i2, i3, i4);
}

void Rubik::swap(Face * array[], int i1, int i2) {
	Face * temp = array[i1];
	array[i1] = array[i2];
	array[i2] = temp;
}

void Rubik::Ri() {
	translate(this->corners, 9, 15, 5, 3);
	translate(this->corners, 7, 21, 19, 1);
	translate(this->corners, 17, 23, 13, 11);
	translate(this->edges, 7, 22, 9, 1);
	translate(this->edges, 19, 10, 21, 13);
	this->moves.push_back("Ri");
}

void Rubik::R() {
	translate(this->corners, 3,5,15,9);
	translate(this->corners, 1,19,21,7);
	translate(this->corners,11,13,23,17);
	translate(this->edges, 1,9,22,7);
	translate(this->edges, 13,21,10,19);
	this->moves.push_back("R");
}
void Rubik::R2() {
	swap((Face**)this->corners, 3, 15);
	swap((Face**)this->corners, 5, 9);
	swap((Face**)this->corners, 1, 21);
	swap((Face**)this->corners, 19, 7);
	swap((Face**)this->corners, 11, 23);
	swap((Face**)this->corners, 13, 17);

	swap((Face**)this->edges, 1, 22);
	swap((Face**)this->edges, 9, 7);
	swap((Face**)this->edges, 13, 10);
	swap((Face**)this->edges, 21, 19);

	this->moves.push_back("R2");
}
void Rubik::Li() {
	translate(this->corners, 16, 2, 4, 22);
	translate(this->corners, 6, 0, 10, 12);
	translate(this->corners, 8, 18, 20, 14);
	translate(this->edges, 6, 3, 8, 11);
	translate(this->edges, 18, 15, 20, 23);

	this->moves.push_back("Li");
}
void Rubik::L() {
	translate(this->corners, 22, 4, 2, 16);
	translate(this->corners, 12, 10, 0, 6);
	translate(this->corners, 14, 20, 18, 8);
	translate(this->edges, 11, 8, 3, 6);
	translate(this->edges, 23, 20, 15, 18);

	this->moves.push_back("L");
}
void Rubik::L2() {
	swap((Face**)this->corners, 22, 2);
	swap((Face**)this->corners, 4,16);
	swap((Face**)this->corners, 12,0);
	swap((Face**)this->corners, 10,6);
	swap((Face**)this->corners, 14,18);
	swap((Face**)this->corners, 20,8);

	swap((Face**)this->edges, 11,3);
	swap((Face**)this->edges, 8,6);
	swap((Face**)this->edges, 23,15);
	swap((Face**)this->edges, 20,18);

	this->moves.push_back("L2");
}
void Rubik::Ui() {
	translate(this->corners, 9, 16, 6, 7);
	translate(this->corners, 1, 8, 22, 23);
	translate(this->corners, 0, 14, 15, 17);
	translate(this->edges, 4, 7, 12, 6);
	translate(this->edges, 0, 18, 16, 19);

	this->moves.push_back("Ui");
}
void Rubik::U() {
	translate(this->corners, 7, 6, 16, 9);
	translate(this->corners, 23, 22, 8, 1);
	translate(this->corners, 17, 15, 14, 0);
	translate(this->edges, 6, 12, 7, 4);
	translate(this->edges, 19, 16, 18, 0);
	this->moves.push_back("U");
}
void Rubik::U2() {
	swap((Face**)this->corners, 7,16);
	swap((Face**)this->corners, 6,9);
	swap((Face**)this->corners, 17, 14);
	swap((Face**)this->corners, 15,0);
	swap((Face**)this->corners, 23,8);
	swap((Face**)this->corners, 22,1);

	swap((Face**)this->edges,6,7);
	swap((Face**)this->edges, 12,4);
	swap((Face**)this->edges, 19, 18);
	swap((Face**)this->edges, 16,0);

	this->moves.push_back("U2");
}
void Rubik::Bi() {
	translate(this->corners, 7, 14, 4, 13);
	translate(this->corners, 6, 20, 5, 23);
	translate(this->corners, 22, 12, 21, 15);
	translate(this->edges, 4, 23, 5, 10);
	translate(this->edges, 16, 11, 17, 22);

	this->moves.push_back("Bi");
}
void Rubik::B() {
	translate(this->corners, 13, 4, 14, 7);
	translate(this->corners, 23, 5, 20, 6);
	translate(this->corners, 15, 21, 12, 22);
	translate(this->edges, 10, 5, 23, 4);
	translate(this->edges, 22, 17, 11, 16);

	this->moves.push_back("B");
}
void Rubik::B2() {
	swap((Face**)this->corners,13,14);
	swap((Face**)this->corners, 4,7);
	swap((Face**)this->corners, 23,20);
	swap((Face**)this->corners, 5,6);
	swap((Face**)this->corners, 15,12);
	swap((Face**)this->corners, 21,22);

	swap((Face**)this->edges, 10,23);
	swap((Face**)this->edges, 5,4);
	swap((Face**)this->edges, 22,11);
	swap((Face**)this->edges, 17,16);

	this->moves.push_back("B2");
}
void Rubik::Fi() {
	translate(this->corners, 9, 11, 10, 8);
	translate(this->corners, 16, 17, 19, 18);
	translate(this->corners, 0, 1, 3, 2);
	translate(this->edges, 12, 13, 14, 15);
	translate(this->edges, 0, 1, 2, 3);

	this->moves.push_back("Fi");
}
void Rubik::F() {
	translate(this->corners, 8, 10, 11, 9);
	translate(this->corners, 18, 19, 17, 16);
	translate(this->corners, 2, 3, 1, 0);
	translate(this->edges, 15, 14, 13, 12);
	translate(this->edges, 3, 2, 1, 0);

	this->moves.push_back("F");
}
void Rubik::F2() {
	//FIXME ?
	swap((Face**)this->corners, 3, 0);
	swap((Face**)this->corners, 2,1);
	swap((Face**)this->corners, 8,11);
	swap((Face**)this->corners, 10,9);
	swap((Face**)this->corners, 18,17);
	swap((Face**)this->corners, 19,16);

	swap((Face**)this->edges, 2,0);
	swap((Face**)this->edges, 3,1);
	swap((Face**)this->edges, 15,13);
	swap((Face**)this->edges, 14, 12);

	this->moves.push_back("F2");
}
void Rubik::Di() {
	translate(this->corners, 3, 13, 12, 18);
	translate(this->corners, 2, 11, 21, 20);
	translate(this->corners, 19, 5, 4, 10);
	translate(this->edges, 2, 21, 17, 20);
	translate(this->edges, 14, 9, 5, 8);

	this->moves.push_back("Di");
}
void Rubik::D() {
	translate(this->corners, 18, 12, 13, 3);
	translate(this->corners, 20, 21, 11, 2);
	translate(this->corners, 10, 4, 5, 19);
	translate(this->edges, 20, 17, 21, 2);
	translate(this->edges, 8, 5, 9, 14);

	this->moves.push_back("D");
}

void Rubik::D2(){
	
	swap((Face**)this->corners, 3, 12);
	swap((Face**)this->corners, 11, 20);
	swap((Face**)this->corners, 19, 4);
	swap((Face**)this->corners, 2, 21);
	swap((Face**)this->corners, 18, 13);
	swap((Face**)this->corners, 10, 5);

	swap((Face**)this->edges, 2, 17);
	swap((Face**)this->edges, 21, 20);
	swap((Face**)this->edges, 14, 5);
	swap((Face**)this->edges, 9, 8);

	this->moves.push_back("D2");
}

void Rubik::resolve(RubikColor colors[]) {
	resolveMiddle(colors[4]);
	//RubikColor edgesColors[4] = { colors[1], colors[3], colors[5], colors[7] };

	RubikColor edgesColors[4] = { colors[7], colors[5], colors[1], colors[3] };
	RubikColor cornersColors[4] = { colors[6], colors[8], colors[2], colors[0] };
	resolveEdges(edgesColors);
	resolveCorners(cornersColors);
}
void Rubik::resolveMiddle(RubikColor color) {

	switch (color) {
	case RubikColor::RED:
		this->changeReferentialWhiteToRed();
		break;
	case RubikColor::BLUE:
		this->changeReferentialWhiteToBlue();
		break;
	case RubikColor::ORANGE:
		this->changeReferentialWhiteToOrange();
		break;
	case RubikColor::GREEN:
		this->changeReferentialWhiteToGreen();
		break;
	case RubikColor::YELLOW:
		this->changeReferentialWhiteToYellow();
		break;
	default:
		break;
	}

	if (Rubik::debug) this->printCube();
}

void Rubik::setLockedEdge(int index, bool value) {
	int edgeIndex = index % 12;
	this->edges[edgeIndex]->setLockedPosition(value);
	this->edges[edgeIndex + 12]->setLockedPosition(value);
}

void Rubik::resolveEdges(RubikColor colors[]) {

	int solvedEdges = 0;

	for (int i = 0; i < 4; i++) {
		RubikColor color = colors[i]; //12 7 4 6
		int index = this->searchEdgeColorIndex(color,solvedEdges);
		if (Rubik::debug) std::cout << "Edge : Number " << this->edges[index]->getNumber() << " at position " << index << std::endl;

		this->setLockedEdge(12, TRUE);
		solvedEdges++;
		this->U();

		if (Rubik::debug) {
			std::cout << std::endl;
			for (unsigned int i = 0; i < this->moves.size(); i++) {
				std::cout << moves[i] << " ";
			}
			this->printCube();
			std::cout << "--------------------------------------------------------" << std::endl;
		}

	}
}

int Rubik::searchEdgeColorIndex(RubikColor color, int solvedEdges) {

	// 0

	if (checkEdgeColor(12, color)) {
		//No moves
		return 12;
	}

	//1

	if (checkEdgeColor(13, color)) {
		this->Fi();
		return 13;
	}

	if (checkEdgeColor(15, color)) {
		this->F();
		return 15;
	}

	if (checkEdgeColor(6, color) && solvedEdges == 0) {
		this->Ui();
		return 6;
	}
	
	if (checkEdgeColor(7, color) && solvedEdges == 0) {
		this->U();
		return 7;
	}

	//2

	if (checkEdgeColor(21, color)) {
		R(); Fi(); Ri();
		return 21;
	}
	
	if (checkEdgeColor(20, color)) {
		Li(); F(); L();
		return 20;
	}

	if (checkEdgeColor(3, color)) {
		this->U();
		this->Li();
		this->Ui();
		return 3;
	}
	
	if (checkEdgeColor(11, color)) {
		this->U();
		this->L();
		Ui();
		return 11;
	}

	if (checkEdgeColor(14, color)) {
		this->F2();
		return 14;
	}
	
	if (checkEdgeColor(1, color)) {
		Ui();
		R();
		U();
		return 1;
	}

	if (checkEdgeColor(22, color)) {
		Ui();
		Ri();
		U();
		return 22;
	}

	if (checkEdgeColor(4, color) && solvedEdges == 0) {
		U2();
		return 4;
	}

	if (checkEdgeColor(18, color)) {
		L(); F();
		return 18;
	}if (checkEdgeColor(19, color)) {
		Ri(); Fi();
		return 19;
	}
	
	//3
	
	if (checkEdgeColor(9, color)) {
		Di();
		F2();
		return 9;
	}if (checkEdgeColor(10, color)) {
		R2();
		Fi();
		R2();
		return 10;
	}if (checkEdgeColor(23, color)) {
		L2();
		F();
		L2();
		return 23;
	}if (checkEdgeColor(8, color)) {
		D();
		F2();
		return 8;
	}if (checkEdgeColor(2, color)) {
		D(); R(); Fi(); Ri();
		return 2;
	}if (checkEdgeColor(17, color)) {
		D(); Li(); F(); L();
		return 17;
	}
	
	//4
	
	if (checkEdgeColor(5, color)) {
		D2();
		F2();
		return 5;
	}

	//5

	if (checkEdgeColor(0, color)) {
		F2(); D(); R(); Fi(); Ri();
		return 0;
	}if (checkEdgeColor(16, color)) {
		B2(); Di(); R(); Fi(); Ri();
		return 16;
	}

	// 6

	if (checkEdgeColor(4, color)) {
		//Don't move top !
	}if (checkEdgeColor(6, color)) {
		//Don't move top !
	}if (checkEdgeColor(7, color)) {
		//Don't move top !
	}
	
}

bool Rubik::checkEdgeColor(int index, RubikColor color) { //locked
	if (this->edges[index]->getLockedPosition() == FALSE && this->edges[index]->getColor() == color)
	{
		return TRUE;
	}
	return FALSE;
}

void Rubik::setLockedCorner(int index, bool value) {
	int cornerIndex = index % 8;
	this->corners[cornerIndex]->setLockedPosition(value);
	this->corners[cornerIndex + 8]->setLockedPosition(value);
	this->corners[cornerIndex + 16]->setLockedPosition(value);
}

void Rubik::resolveCorners(RubikColor colors[]) {
	int solvedCorners = 0;

	for (int i = 0; i < 4; i++) {
		RubikColor color = colors[i]; //16 9 7 6
		int index = this->searchCornerColorIndex(color, solvedCorners);
		if (Rubik::debug) std::cout << "Corner : Number " << this->corners[index]->getNumber() << " at position " << index << std::endl;

		this->setLockedCorner(16, TRUE);

		solvedCorners++;
		this->U();

		if (Rubik::debug) {
			std::cout << std::endl;
			for (unsigned int i = 0; i < this->moves.size(); i++) {
				std::cout << moves[i] << " ";
			}
			this->printCube();
			std::cout << "--------------------------------------------------------" << std::endl;
		}
	}

}
int Rubik::searchCornerColorIndex(RubikColor color, int solvedEdges) {

	if (checkCornerColor(16, color)) {
		//No moves
		return 16;
	}
	
	if (checkCornerColor(0, color)) {
		Fi(); Di(); F(); D2(); L(); Di(); Li();
		return 0;
	}

	

	if (checkCornerColor(1, color)) {
		//F D2 Fi Fi D F
		F(); D2(); F2(); D(); F();

		return 1;
	}

	if (checkCornerColor(2, color)) {
		D(); L(); Di(); Li();
		return 2;
	}

	if (checkCornerColor(3, color))  {
		D2(); Fi(); D(); F();
		return 3;
	}

	if (checkCornerColor(11, color)) {
		L(); Di(); Li();
		return 11;
	}


	if (checkCornerColor(12, color)) {
		Fi(); D(); F();
		return 12;
	}

	if (checkCornerColor(13, color)) {
		D(); Fi(); D(); F();
		return 13;

	}

	if (checkCornerColor(18, color)) {
		Di(); Fi(); D(); F();
		return 18;
	}

	if (checkCornerColor(20, color)) {
		D2(); L(); Di();  Li();
		return 20;
	}

	if (checkCornerColor(21, color)) {
		Di(); L(); Di(); Li();
		return 21;
	}

	if (checkCornerColor(4, color)) { //mm combinaison pour 5, 10, 19
		Fi(); D(); F(); L(); D(); Li(); D2(); Fi(); D(); F();
		return 4;
	}

	if (checkCornerColor(5, color)) {
		D(); Fi(); D(); F(); L(); D(); Li(); D2(); Fi(); D(); F();
		return 5;
	}

	if (checkCornerColor(10, color)) {
		Di(); Fi(); D(); F(); L(); D(); Li(); D2(); Fi(); D(); F();
		return 10;
	}

	if (checkCornerColor(6, color)) {
		B(); D2(); Bi(); L(); Di(); Li(); 
		return 6;

	}if (checkCornerColor(7, color)) {
		Bi(); D(); Fi(); D(); F(); B();
		return 7;
	}

	if (checkCornerColor(8, color)) {
		L(); D(); Li(); D2(); Fi(); D(); F();
		return 8;

	}if (checkCornerColor(9, color)) {
		Ri(); Di(); R(); Di(); Fi(); D(); F();
		return 9;

	}if (checkCornerColor(11, color)) {
		L(); Di(); Li();
		return 11;

	}if (checkCornerColor(12, color)) {
		Fi(); D(); F();
		return 12;

	}if (checkCornerColor(14, color)) {
		//Li(); Di(); L(); D(); Fi(); D(); F();
		Li(); D2(); L2(); Di(); Li();
		return 14;
	}

	if (checkCornerColor(15, color)) {
		Bi(); Di(); B(); L(); Di(); Li();
		return 15;
	}

	if (checkCornerColor(17, color)) {
		Ri(); L(); Di(); Li(); R();
		return 17;

	}

	if (checkCornerColor(22, color)) {
		B(); Fi(); D(); Bi(); F();
		return 22;

	}if (checkCornerColor(23, color)) {
		R(); D(); Fi(); D(); F(); Ri();
		return 23;

	}if (checkCornerColor(19, color)) {
		D2(); Fi(); D(); F(); L(); D(); Li(); D2(); Fi(); D(); F();
		return 19;
	}

}
bool Rubik::checkCornerColor(int index, RubikColor color) { //locked
	if (this->corners[index]->getLockedPosition() == FALSE && this->corners[index]->getColor() == color)
	{
		return TRUE;
	}
	return FALSE;
}


void Rubik::changeReferential(RubikColor color) {

}

void Rubik::changeReferential(MiddleFace * m) {

}

void Rubik::changeReferentialWhiteToGreen() {
	F();
	Bi();
	this->translate(this->middle, 3,2,4,1);
	this->translate(this->edges, 6,20,9,19);
	this->translate(this->edges, 7,18,8,21);

}
void Rubik::changeReferentialWhiteToRed() {
	R();
	Li();
	this->translate(this->middle, 0,2,5,1);
	this->translate(this->edges, 4,0,14,17);
	this->translate(this->edges, 12,2,5,16);

}
void Rubik::changeReferentialWhiteToBlue() {
	Fi();
	B();
	this->translate(this->middle, 3,1,4,2);
	this->translate(this->edges, 6,19,9,20);
	this->translate(this->edges, 7,21,8,18);
}
void Rubik::changeReferentialWhiteToOrange() {
	Ri();
	L();
	this->translate(this->middle, 0,1,5,2);
	this->translate(this->edges, 4,17,14,0);
	this->translate(this->edges, 12,16,5,2);
}
void Rubik::changeReferentialWhiteToYellow() {
	R2();
	L2();
	this->swap((Face**)this->edges, 12, 5);
	this->swap((Face**)this->edges, 4, 14);
	this->swap((Face**)this->edges, 0, 17);
	this->swap((Face**)this->edges, 2, 16);

	this->swap((Face**)this->middle, 1, 2);
	this->swap((Face**)this->middle, 0, 5);
	//test
}

