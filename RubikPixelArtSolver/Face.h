#ifndef FACE_HEADER

#define FACE_HEADER

#include "RubikColor.h"

class Face {
	public:
		Face(int,RubikColor);
		/*
			Couleur
			Number				
		*/
		RubikColor color;
		int number;
	private:

};

#endif