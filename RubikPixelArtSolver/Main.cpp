
#include "Rubik.h"

int main(int argc, char* argv[]) {

	int pieces[54] = { 6, 4, 7, 6, 1, 7, 16, 12, 9, 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22, 23, 3, 15, 3, 0, 1, 13, 4, 10, 22, 5, 11, 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12, 10, 14, 19, 8, 2, 9, 4, 5, 5 };

	/* The numbers are specified this way

			       01 02 03
				   04 05 06
				   07 08 09

		10 11 12   13 14 15   16 17 18   19 20 21
		22 23 24   25 26 27	  28 29 30   31 32 33
		34 35 36   37 38 39   40 41 42   43 44 45

		           46 47 48
				   49 50 51
				   52 53 54

	*/


	Rubik* rubik = new Rubik(pieces);
	RubikColor colors[9] = { RubikColor::BLUE, RubikColor::RED, RubikColor::BLUE, RubikColor::RED, RubikColor::BLUE, RubikColor::RED, RubikColor::BLUE, RubikColor::RED, RubikColor::BLUE };

	/* The colors are specified this way :
		1 2 3
		4 5 6
		7 8 9
	*/

	//rubik->resolve(colors);
	rubik->printCube();
	getchar();
	free(rubik);
	return 0;
}