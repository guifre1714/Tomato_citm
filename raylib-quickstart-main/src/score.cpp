#include <score.h>

Score::Score(Vector2 position, Texture2D TXT) { 
	//Initialize
	time = 0;
	pos = position;
	sTXT = TXT;
}
Score::~Score() { UnloadTexture(sTXT); }
void Score::Draw() {//Count time and draw the score texture
	time++;
	DrawTexture(sTXT, pos.x, pos.y, WHITE);
}