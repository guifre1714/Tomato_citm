#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
using namespace std;

Player::Player() {

	bmanTXT = LoadTexture("Sprites/base.png");

	
	bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!

	bmanPos.y = 272;
	bmanCol = { bmanPos.x, bmanPos.y, 12, 16 };

	instantiateColliders();

	colliders.insert(colliders.end(), col1);
	colliders.insert(colliders.end(), col2);
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}


void Player::Draw() {
	DrawTextureV(bmanTXT, bmanPos, WHITE);
}

void Player::MoveUp() {
	dir = "up";
	if (!Collide()) {
		bmanPos.y -= 1.3f;
	}

}
void Player::MoveDown() {
	dir = "down";
	if (!Collide()) {
		bmanPos.y += 1.3f;
	}
}
void Player::MoveLeft() {
	dir = "left";
	if (!Collide()) {
		bmanPos.x -= 1.3f;
	}
}
void Player::MoveRight() {
	dir = "right";
	if (!Collide()) {
		bmanPos.x += 1.3f;
	}
}

bool Player::Collide() {
	bool col;
	if (dir == "up") {
		bmanCol.y = bmanPos.y - 1.3f;
		bmanCol.x = bmanPos.x;
	}
	else if (dir == "down") {
		bmanCol.y = bmanPos.y + 1.3f;
		bmanCol.x = bmanPos.x;
	}
	else if (dir == "left") {
		bmanCol.x = bmanPos.x - 1.3f;
		bmanCol.y = bmanPos.y;
	}
	else {
		bmanCol.x = bmanPos.x + 1.3f;
		bmanCol.y = bmanPos.y;
	}
	for (int i = 0; i < colliders.size(); i++) {
		col = CheckCollisionRecs(bmanCol, colliders[i].col);
		if (col) return true;
	}
	if (!col) return false;
}

void Player::instantiateColliders() {
	col1.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col1);
	col2.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col2);
	col3.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col3);
	col4.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col4);
}