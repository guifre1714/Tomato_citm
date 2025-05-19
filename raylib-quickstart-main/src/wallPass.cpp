#include <wallPass.h>

wallPass::wallPass() {
	type = "wallPass";
	blockTEXT = LoadTexture("Sprites/powerUps/wallPass.png");
}

wallPass::~wallPass() {};

bool wallPass::playerCol(Player* player) {
	return CheckCollisionRecs(col, player->myCollider);
};