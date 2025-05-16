#include <bomba.h>

Bomba::Bomba(Vector2 pos, bool potenciada, vector <Collider> Pblocs) {
	bombPos = pos;
	boom = false;
	plus = potenciada;
	blocs = Pblocs;
	bombTEXT = LoadTexture("Sprites/bombAni.png");
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 4; //marca la velocitat dels FPS

	totalFrames = 3;
	!colUp;
	!colDown;
	!colLeft;
	!colRight;
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
	KaboomCheck();
	DrawTextureRec(bombTEXT, frameRec, bombPos, WHITE);
}

void Bomba::KaboomCheck() {
	if (!plus && boom) {
		rectUp = { bombPos.x, bombPos.y - 16, 16, 16 };
		rectDown = { bombPos.x, bombPos.y + 16, 16, 16 };
		rectLeft = { bombPos.x - 16, bombPos.y, 16, 16 };
		rectRight = { bombPos.x + 16, bombPos.y, 16, 16 };
	}
	DrawRectangle(rectUp.x, rectUp.y, rectUp.width, rectUp.height, RED);
	DrawRectangle(rectDown.x, rectDown.y, rectDown.width, rectDown.height, RED);
	DrawRectangle(rectLeft.x, rectLeft.y, rectLeft.width, rectLeft.height, RED);
	DrawRectangle(rectRight.x, rectRight.y, rectRight.width, rectRight.height, RED);
	for (int i = 0; i < blocs.size(); i++) {
		colUp = CheckCollisionRecs(rectUp, blocs[i].col);
		colDown = CheckCollisionRecs(rectDown, blocs[i].col);
		colLeft = CheckCollisionRecs(rectLeft, blocs[i].col);
		colRight = CheckCollisionRecs(rectRight, blocs[i].col);
		if (colUp) {
			!expandUp;
			blocs[i].breaking;
		}
		else if (colDown) {
			!expandDown;
			blocs[i].breaking;
		} else if (colLeft) {
			!expandLeft;
			blocs[i].breaking;
		} else if (colRight) {
			!expandDown;
			blocs[i].breaking;
		}
	}
}