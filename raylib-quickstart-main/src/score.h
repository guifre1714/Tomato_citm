#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>

using namespace std;

class Score {
public:
	Score(Vector2 position, Texture2D TXT);
	~Score();
	
	int time;
	void Draw();
	Texture2D sTXT;
	Vector2 pos;
};