#include "Color.h"

//Parameters: Red, Green, Blue, Alpha
Color::Color(int r, int g, int b, int a) {
	R = r;
	G = g;
	B = b;
	A = a;
}

Color::Color() {
	R = 255;
	G = 255;
	B = 255;
	A = 0;
}