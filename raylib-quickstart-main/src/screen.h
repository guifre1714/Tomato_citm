#pragma once
#include "raylib.h"
#include "player.h"
#include <vector>
using namespace std;

class Screen {
public:
	Screen();
	~Screen();

	virtual void Draw();
	virtual void Update();
	virtual void HandleInput();
	virtual bool nextLevel();
	Music bgm;
	Player bomberman;
	Texture Fons;
	unsigned int mySeed;
	int duration;
	bool freeze;
	int timer;
};