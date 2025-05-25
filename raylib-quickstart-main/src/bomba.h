#pragma once
#include<collider.h>
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

class Bomba {
public:
	Bomba(Vector2 pos, vector <Collider>* pBlocs);
	~Bomba();

	void Draw();
	void KaboomCheck();
	Rectangle rectUp, rectDown, rectRight, rectLeft;
	Rectangle hitBox;
	bool colUp, colDown, colLeft, colRight, expandUp, expandDown, expandLeft, expandRight;
	Vector2 bombPos;
	Texture bombTEXT;
	Rectangle frameRec;
	vector<Collider>* blocs;
	Texture expUp;
	Texture expDown;
	Texture expLeft;
	Texture expRight;
	Collider myCollider;
	bool bombActive;
	bool boom;
	bool plus;
	int currentFrame;
	int frameContador;
	int frameSpeed;
	int totalFrames;
	int ampladaFrames;
	int boomTime;
	int time;
	bool remoCon;
	bool colliderAdded;
	bool erased;

	Sound kaboom;
};