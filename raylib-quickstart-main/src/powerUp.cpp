#include <powerUp.h>

powerUp::powerUp() {
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 16; //marca la velocitat dels FPS

	totalFrames = 3;
	col.x;
	col.y;
	col.height = 13;
	col.width = 13;
}

powerUp::~powerUp(){}

bool powerUp::playerCol(Player* player) {
	return CheckCollisionRecs(col, player->myCollider);
};