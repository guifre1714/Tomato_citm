#pragma once
#include "raylib.h"




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

	Texture2D bmanTXT;
	Vector2 bmanPos;

	
};