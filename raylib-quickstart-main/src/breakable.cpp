#include <breakable.h>

Breakable::Breakable() {
	breakable = true;
	breaking = false;
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 8; //marca la velocitat dels FPS

	totalFrames = 3;
	blockTEXT = LoadTexture("Sprites/blocsDestruibles.png");
};
Breakable::~Breakable() {};
void Breakable::Draw() {
	pos.x = col.x;
	pos.y = col.y;
	if (breaking) {
		frameContador++;
		if (frameContador >= (60 / frameSpeed)) {
			frameContador = 0;
			currentFrame++;

			if (currentFrame > 3) {
				currentFrame = 0;
			}
			frameRec.x = (float)currentFrame * 12;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
		}
	}
	DrawTextureRec(blockTEXT, frameRec, pos, WHITE);
};