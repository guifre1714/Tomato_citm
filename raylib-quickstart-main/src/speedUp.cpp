#include <speedUp.h>

speedUp::speedUp(vector <Collider>* bColliders) {
	type = "speedUp";
	blockTEXT = LoadTexture("Sprites/powerUps/speedUp.png");
	blocs = bColliders;
};
speedUp::~speedUp() {};

bool speedUp::playerCol(Player* player) {//If it isn't behind a block and the player touches it, return true.
	for (int i = 0; i < blocs->size(); i++) {
		if (CheckCollisionRecs((*blocs)[i].col, col) == true) return false;
	}
	return CheckCollisionRecs(col, player->myCollider);
};