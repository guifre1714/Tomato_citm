#include <score.h>

Score::Score() { time = 0; }
Score::~Score() { UnloadTexture(sTXT); }
void Score::Update() {
	time++;
	DrawTexture(sTXT, pos.x, pos.y, WHITE);
}