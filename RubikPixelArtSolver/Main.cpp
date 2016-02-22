
#include "Rubik.h"

int main(int argc, char* argv[]) {

	int pieces[48] = { 6, 4, 7, 6, 7, 16, 12, 9, 14, 18, 8, 0, 0, 1, 17, 19, 23, 15, 16, 22, 23, 15, 3, 1, 13, 10, 22, 11, 20, 20, 18, 2, 2, 3, 11, 21, 13, 21, 17, 12, 10, 14, 19, 8, 9, 4, 5, 5 };

	Rubik* rubik = new Rubik(pieces);
	rubik->B();
	rubik->printCube();
	getchar();
	free(rubik);
	return 0;
}

/*using namespace std;
#include "RubikColor.h"

int main(int argc, char *argv[])
{
	cout << "standard text" << setcolor(RED) << " red text" << setcolor(GREEN) << "green text" << setcolor(YELLOW) << "yellow text" << endl;

	cin.get();
}*/