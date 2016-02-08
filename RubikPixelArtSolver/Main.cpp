#include <iostream>
#include "Rubik.h"

int main(int argc, char* argv[]) {
	Rubik* rubik = new Rubik();
	rubik->print();
	getchar();
	free(rubik);
	return 0;
}