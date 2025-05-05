#include <player.hpp>

Player::Player() {

	bmanTXT = LoadTexture("Sprites/base.png");
	bmanPos.x = 50;
	bmanPos.y = 50;
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}

void Player::Draw() {
	DrawTextureV(bmanTXT, bmanPos, WHITE);
}

void Player::MoveUp() {
	bmanPos.y -= 1.3f;
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