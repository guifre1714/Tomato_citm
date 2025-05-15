#include <bomba.h>

Bomba::Bomba() {
	bombTEXT = LoadTexture("Sprites/bomb.png");
}

Bomba::~Bomba() {
	UnloadTexture(bombTEXT);
}