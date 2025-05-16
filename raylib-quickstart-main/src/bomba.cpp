#include <bomba.h>

Bomba::Bomba(Vector2 pos) {
	bombPos = pos;
	bombTEXT = LoadTexture("Sprites/bombAni.png");
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 4; //marca la velocitat dels FPS

	totalFrames = 3;
}

Bomba::~Bomba() {
}

void Bomba::Draw() {
	frameContador++;
	if (frameContador >= (60 / frameSpeed)) {
		frameContador = 0;
		currentFrame++;

		if (currentFrame > 3) {
			currentFrame = 0;
		}
		frameRec.x = (float)currentFrame * 16;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
	}
	DrawTextureRec(bombTEXT, frameRec,bombPos, WHITE);
}