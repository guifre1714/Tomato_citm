#pragma once
#include "raylib.h"
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

	string dir;

	vector <Collider> colliders;

	Collider col1;
	Collider col2;

	Texture2D bmanTXT;
	Vector2 bmanPos;

	Rectangle bmanCol;

};