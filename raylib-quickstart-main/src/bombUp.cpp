#include <bombUp.h>

bombUp::bombUp() {
	type = "bombUp";
	blockTEXT = LoadTexture("Sprites/powerUps/bombUp.png");
};
bombUp::~bombUp() {};

bool bombUp::playerCol(Player* player) {
	return CheckCollisionRecs(col, player->myCollider);
};