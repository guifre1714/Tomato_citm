#pragma once
#include <raylib.h>
#include <iostream>
using namespace std;

class Bomba {
public:
	Bomba();
	~Bomba();

	Rectangle colVert, colHor;
	Vector2 bombPos;
	Texture bombTEXT;
};