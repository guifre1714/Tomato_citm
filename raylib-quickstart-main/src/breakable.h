#pragma once
#include <collider.h>

class Breakable : public Collider {
	Breakable();
	~Breakable();
	void Draw();

	int currentFrame;
	int frameContador;
	int frameSpeed; //marca la velocitat dels FPS
	int totalFrames;

	bool breaking;

	Rectangle frameRec;
	Texture blockTEXT;
	Vector2 pos;
};