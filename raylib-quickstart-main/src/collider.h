#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

class Collider {
public:
	Collider();
	~Collider();
	void Draw();

	int currentFrame;
	int frameContador;
	int frameSpeed; //marca la velocitat dels FPS
	int totalFrames;
	bool destroy;

	bool breaking;

	Rectangle frameRec;
	Texture blockTEXT;
	Vector2 pos;

	bool breakable;
	Rectangle col;
};