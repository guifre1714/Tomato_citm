#include <collider.h>
using namespace std;

Collider::Collider() {
	breakable = false;
	destroy = false;
}

Collider::~Collider()
{
}

void Collider::Draw() {
	pos.x = col.x - 1;
	pos.y = col.y - 1;
	if (breaking) {
		frameContador++;
		if (frameContador >= (60 / frameSpeed)) {
			frameContador = 0;
			currentFrame++;

			if (currentFrame > 7) {
				destroy = true;
			}
			frameRec.x = (float)currentFrame * 16;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
		}
	}
	DrawTextureRec(blockTEXT, frameRec, pos, WHITE);
};