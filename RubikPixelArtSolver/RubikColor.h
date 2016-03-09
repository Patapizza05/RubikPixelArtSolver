#ifndef RUBIKCOLOR_HEADER

#define RUBIKCOLOR_HEADER

#include <iostream>
#include <windows.h>
#include <iomanip>

enum RubikColor { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE, ORANGE };

struct setcolor
{
	RubikColor _c;
	HANDLE _console_handle;
	//TODO : Ajouter la couleur orange
	setcolor(RubikColor c, HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE))
		: _c(c), _console_handle(0)
	{
		_console_handle = console_handle;
	}
};

// We could use a template here, making it more generic. Wide streams won't
// work with this version.
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &s, const setcolor &ref);

#endif