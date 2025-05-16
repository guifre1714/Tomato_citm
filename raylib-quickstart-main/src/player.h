#pragma once
#include "raylib.h"
#include <bomba.h>
#include <collider.h>
using namespace std;

class Player {
public:
	Player();
	~Player();

	void Draw();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	bool Collide();

	void instantiateColliders();
	void createBomb();

	float vel;

	string dir;

	vector <Collider> colliders;

	Texture2D bmanTXT;
	Vector2 bmanPos;
	vector <Bomba> bombs;

	Rectangle bmanCol;

	int currentFrameB;
	int frameContadorB ;
	int frameSpeedB; //marca la velocitat dels FPS
	int totalFrames;

	bool bombExist;

	Rectangle frameRecB;

};