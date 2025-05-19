#include <remoteControl.h>

remoteControl::remoteControl(vector <Collider>* bColliders) {
	type = "remoteControl";
	blockTEXT = LoadTexture("Sprites/powerUps/remoteControl.png");
	blocs = bColliders;
};
remoteControl::~remoteControl() {};

bool remoteControl::playerCol(Player* player) {
	for (int i = 0; i < blocs->size(); i++) {
		if (CheckCollisionRecs((*blocs)[i].col, col) == true) return false;
	}
	return CheckCollisionRecs(col, player->myCollider);
};