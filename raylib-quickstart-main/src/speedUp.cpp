#include <speedUp.h>

speedUp::speedUp() {
	type = "speedUp";
	blockTEXT = LoadTexture("Sprites/powerUps/speedUp.png");
};
speedUp::~speedUp() {};

bool speedUp::playerCol(Player* player) {
	return CheckCollisionRecs(col, player->myCollider);
};