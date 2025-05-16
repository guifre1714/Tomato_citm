#include <collider.h>
using namespace std;

Collider::Collider() {
	breakable = false;
}

Collider::~Collider()
{
}

void Collider::Draw() {
	pos.x = col.x;
	pos.y = col.y;
	if (breaking) {
		frameContador++;
		if (frameContador >= (60 / frameSpeed)) {
			frameContador = 0;
			currentFrame++;

			if (currentFrame > 7) {
				currentFrame = 0;
			}
			frameRec.x = (float)currentFrame * 16;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
		}
	}
	DrawTextureRec(blockTEXT, frameRec, pos, WHITE);
};