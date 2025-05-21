#include <score.h>

Score::Score(Vector2 position, Texture2D TXT) { 
	time = 0;
	pos = position;
	sTXT = TXT;
}
Score::~Score() { UnloadTexture(sTXT); }
void Score::Draw() {
	time++;
	DrawTexture(sTXT, pos.x, pos.y, WHITE);
}