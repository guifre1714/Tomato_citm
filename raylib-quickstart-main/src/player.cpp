#include <player.h>


Player::Player() {

	bmanTXT = LoadTexture("Sprites/idle.png");
	bmanPos.x = 410;
	bmanPos.y = 312;
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}

void Player::Animation() {
	frameContadorB++;
	if (frameContadorB >= (60 / frameSpeedB))
	{
		frameContadorB = 0;
		currentFrameB++;

		if (currentFrameB > 5) currentFrameB = 0;

		frameRecB.x = (float)currentFrameB * (float)bmanTXT.width / 3; //MIDA DISPLAY FRAME
	}
}

void Player::Draw() {
	

	DrawTextureRec(bmanTXT, frameRecB, bmanPos, WHITE);
}

void Player::MoveUp() {
	bmanPos.y -= 1.3f;
	bmanTXT = LoadTexture("Sprites/walkBack.png");

	
}
void Player::MoveDown() {
	bmanPos.y += 1.3f;
}
void Player::MoveLeft() {
	bmanPos.x -= 1.3f;
}
void Player::MoveRight() {
	bmanPos.x += 1.3f;
}