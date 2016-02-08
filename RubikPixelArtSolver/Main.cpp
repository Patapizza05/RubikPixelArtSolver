#include "Rubik.h"

int main(int argc, char* argv[]) {
	Rubik* rubik = new Rubik();
	rubik->printCube();
	getchar();
	free(rubik);
	return 0;
}