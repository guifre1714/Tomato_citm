#pragma once
#include<collider.h>
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

class Bomba {
public:
	Bomba(Vector2 pos, bool potenciada, vector <Collider> Pblocs);
	~Bomba();

	void Draw();
	void KaboomCheck();
	Rectangle rectUp, rectDown, rectRight, rectLeft;
	bool colUp, colDown, colLeft, colRight, expandUp, expandDown, expandLeft, expandRight;
	Vector2 bombPos;
	Texture bombTEXT;
	Rectangle frameRec;
	vector <Collider> blocs;

	bool boom;
	bool plus;
	int currentFrame;
	int frameContador;
	int frameSpeed;

	int totalFrames;
};