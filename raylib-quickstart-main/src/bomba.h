#pragma once
#include <raylib.h>
#include <iostream>
using namespace std;

class Bomba {
public:
	Bomba(Vector2 pos);
	~Bomba();

	void Draw();
	Vector2 bombPos;
	Texture bombTEXT;
	Rectangle frameRec;

	int currentFrame;
	int frameContador;
	int frameSpeed;

	int totalFrames;
};