#include <door.h>

Door::Door() {
	/*enemies = enemics;*/
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 16; //marca la velocitat dels FPS

	totalFrames = 3;
	blockTEXT = LoadTexture("Sprites/door.png");
	col.x;
	col.y;
	col.height = 13;
	col.width = 13;
};
Door::~Door() {};