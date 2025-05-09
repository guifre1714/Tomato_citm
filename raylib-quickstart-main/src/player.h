#pragma once
#include "raylib.h"
#include <game.h>



class Player {
public:
	Player();
	~Player();

	void Draw();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	//bool Collide();

private:
	Texture2D bmanTXT;
	Vector2 bmanPos;
};