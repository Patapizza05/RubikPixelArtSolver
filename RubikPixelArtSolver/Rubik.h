#include "Face.h"
#include <iostream>

#ifndef RUBIK_HEADER

#define RUBIK_HEADER

class Rubik {
	public:
		Rubik();
		void print();
	private:
		Face corners[24];
		Face edges[24];
};

#endif