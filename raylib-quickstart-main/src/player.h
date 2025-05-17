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

	void Dead();

	bool Collide();

	void createBomb();

	void resetPlayer();

	float distanceBetween(const Vector2& a, const Vector2& b);
	int getClosestSnapIndex(const Vector2& point, const vector<Vector2>& snapPositions);

	float vel;

	string dir;

	vector <Collider> colliders;

	Texture2D bmanTXT;
	Vector2 bmanPos;
	vector <Bomba> bombs;
	vector <Vector2> snapPositions;

	Rectangle bmanCol;
	Rectangle myCollider;

	int currentFrameB;
	int frameContadorB;
	int frameSpeedB; //marca la velocitat dels FPS
	int totalFrames;
	int ampladaFrames;

	int maxBombs;

	bool bombPlus;

	bool isAlive;
	int* vides;
	int* pantalla;
	bool bombCheck();

	Rectangle frameRecB;

	Sound bombSound;
};