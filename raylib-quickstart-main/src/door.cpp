#include <door.h>

Door::Door() {
	/*enemies = enemics;*/
	blockTEXT = LoadTexture("Sprites/door.png");
};
Door::~Door() {};

bool Door::playerCol(Player* player) {
	return CheckCollisionRecs(col, player->myCollider);
};