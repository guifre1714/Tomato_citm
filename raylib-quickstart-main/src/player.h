#pragma once

#include "raylib.h"



class Player {
public:
	Player();
	~Player();

	void Animation();
	void Draw();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	//void placeBomb();

private:
	Texture2D bmanTXT;
	Vector2 bmanPos;
	Rectangle frameRecB = { 0.0f, 0.0f, (float)bmanTXT.width / 3, (float)bmanTXT.height };//rectangle q marca la mida de display dels frames

	int currentFrameB = 0;
	int frameContadorB = 0;
	int frameSpeedB = 4; //marca la velocitat dels FPS
};