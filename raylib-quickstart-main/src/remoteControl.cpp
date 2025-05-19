#include <remoteControl.h>

remoteControl::remoteControl() {
	type = "remoteControl";
	blockTEXT = LoadTexture("Sprites/powerUps/remoteControl.png");
};
remoteControl::~remoteControl() {};

bool remoteControl::playerCol(Player* player) {
	return CheckCollisionRecs(col, player->myCollider);
};