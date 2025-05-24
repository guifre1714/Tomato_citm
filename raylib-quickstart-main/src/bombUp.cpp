#include <bombUp.h>

bombUp::bombUp(vector <Collider>* bColliders) {
	type = "bombUp";
	blockTEXT = LoadTexture("Sprites/powerUps/bombUp.png");
	blocs = bColliders;
};
bombUp::~bombUp() {};

bool bombUp::playerCol(Player* player) {//If it isn't behind a block and the player touches it, return true.
	for (int i = 0; i < blocs->size(); i++) {
		if (CheckCollisionRecs((*blocs)[i].col, col) == true) return false;
	}
	return CheckCollisionRecs(col, player->myCollider);
};