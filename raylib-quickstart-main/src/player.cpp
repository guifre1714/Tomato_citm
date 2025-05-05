#include <player.hpp>

Player::Player() {

	bmanTXT = LoadTexture("Sprites/base.png");
	bmanPos.x = 100;
	bmanPos.y = 100;
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}

void Player::Draw() {
	DrawTextureV(bmanTXT, bmanPos, WHITE);
}
