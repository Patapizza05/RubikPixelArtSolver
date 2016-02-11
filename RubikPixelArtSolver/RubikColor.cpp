#include "RubikColor.h"

// We could use a template here, making it more generic. Wide streams won't
// work with this version.
std::basic_ostream<char> &operator<<(std::basic_ostream<char> &s, const setcolor &ref)
{
	SetConsoleTextAttribute(ref._console_handle, ref._c);
	return s;
}