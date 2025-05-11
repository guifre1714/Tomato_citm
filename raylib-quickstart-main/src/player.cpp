#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
using namespace std;

Player::Player() {
	bmanTXT = LoadTexture("Sprites/base.png");
	bmanPos.x = 410.0f;
	bmanPos.y = 312.0f;
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

//bool Player::Collide() {
//	bool col;
//	Rectangle bmanCol = { bmanPos.x, bmanPos.y, 12, 16 };
//	/*for (int i = 0; i <= 1; i++) {
//		col = CheckCollisionRecs(bmanCol, );
//	}*/
//}