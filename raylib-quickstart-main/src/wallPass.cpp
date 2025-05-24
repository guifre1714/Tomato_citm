#include <wallPass.h>

wallPass::wallPass(vector <Collider>* bColliders) {
	type = "wallPass";
	blockTEXT = LoadTexture("Sprites/powerUps/wallPass.png");
	blocs = bColliders;
}

wallPass::~wallPass() {};

bool wallPass::playerCol(Player* player) {//If it isn't behind a block and the player touches it, return true.
	for (int i = 0; i < blocs->size(); i++) {
		if (CheckCollisionRecs((*blocs)[i].col, col) == true) return false;
	}
	return CheckCollisionRecs(col, player->myCollider);
};