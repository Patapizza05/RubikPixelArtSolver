#include "EdgeFace.h"

EdgeFace::EdgeFace(int number, RubikColor color) : Face(number, color)
{

}

int EdgeFace::getEdge() {
	return this->number % 12;
}