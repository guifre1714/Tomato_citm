#include <door.h>

Door::Door() {
	blockTEXT = LoadTexture("Sprites/assets/door.png");
};
Door::~Door() {};

void Door::Draw() {
	pos.x = col.x - 7;
	pos.y = col.y - 7;
	if (breaking) {
		frameContador++;
		if (frameContador >= (60 / frameSpeed)) {
			frameContador = 0;
			currentFrame++;

			if (currentFrame > 5) {
				destroy = true;
			}
			frameRec.x = (float)currentFrame * 16;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
		}
	}
	DrawTextureRec(blockTEXT, frameRec, pos, WHITE);
};

bool Door::playerCol(Player* player) {//Return true if the player touches it.
	return CheckCollisionRecs(col, player->myCollider);
};