#include <breakable.h>

Breakable::Breakable(Vector2 position) {
	breakable = true;
	breaking = false;
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 8; //marca la velocitat dels FPS

	totalFrames = 3;
	blockTEXT = LoadTexture("Sprites/blocsDestruibles.png");
	col.x = position.x + 1;
	col.y = position.y + 1;
	col.height = 13;
	col.width = 13;
};
Breakable::~Breakable() {};