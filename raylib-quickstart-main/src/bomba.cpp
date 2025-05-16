#include <bomba.h>

Bomba::Bomba(Vector2 pos, bool potenciada, vector <Collider>* pBlocs,bool *playerBomb) {
	bombPos = pos;
	boom = false;
	plus = potenciada;
	blocs = pBlocs;
	bombActive = playerBomb;
	bombTEXT = LoadTexture("Sprites/bombAni.png");
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrame = 0;
	frameContador = 0;
	ampladaFrames = 16;
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

		if (currentFrame > totalFrames && totalFrames == 3) {
			currentFrame = 0;
		}
		else if (currentFrame > totalFrames && totalFrames > 3) {
			*bombActive = false;
		}
		frameRec.x = (float)currentFrame * ampladaFrames;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
	}
	KaboomCheck();
}

void Bomba::KaboomCheck() {
	if (!plus && boom) {
		//aqui has d canviar la textura de la bomba x la de la explosio. els rectangles son els dels colliders, no necessariament tenen la mateixa mida que les textures. per veure referencia del que he dit mira el breakable.h i breakable.cpp
		totalFrames = 4;
		frameSpeed = 8;
		expandUp = true;
		expandDown = true;
		expandLeft = true;
		expandRight = true;
		rectUp = { bombPos.x, bombPos.y - 16, 16, 16 };
		rectDown = { bombPos.x, bombPos.y + 16, 16, 16 };
		rectLeft = { bombPos.x - 16, bombPos.y, 16, 16 };
		rectRight = { bombPos.x + 16, bombPos.y, 16, 16 };
		DrawRectangle(rectUp.x, rectUp.y, rectUp.width, rectUp.height, RED);
		DrawRectangle(rectDown.x, rectDown.y, rectDown.width, rectDown.height, RED);
		DrawRectangle(rectLeft.x, rectLeft.y, rectLeft.width, rectLeft.height, RED);
		DrawRectangle(rectRight.x, rectRight.y, rectRight.width, rectRight.height, RED);
		for (int i = 0; i < blocs->size(); i++) {
			colUp = CheckCollisionRecs(rectUp, (*blocs)[i].col);
			colDown = CheckCollisionRecs(rectDown, (*blocs)[i].col);
			colLeft = CheckCollisionRecs(rectLeft, (*blocs)[i].col);
			colRight = CheckCollisionRecs(rectRight, (*blocs)[i].col);
			if (colUp) {
				if ((*blocs)[i].breakable) {
					(*blocs)[i].breaking = true;
				}
				expandUp = false;
			}
			if (colDown) {
				if ((*blocs)[i].breakable) {
					(*blocs)[i].breaking = true;
				}
				expandDown = false;
			}
			if (colLeft) {
				if ((*blocs)[i].breakable) {
					(*blocs)[i].breaking = true;
				}
				expandLeft = false;
			}
			if (colRight) {
				if ((*blocs)[i].breakable) {
					(*blocs)[i].breaking = true;
				}
				expandRight = false;
			}
		}
		/*if (expandUp) {
			DrawRectangle(rectUp.x, rectUp.y, rectUp.width, rectUp.height, RED);
		}
		if (expandDown) {
			DrawRectangle(rectDown.x, rectDown.y, rectDown.width, rectDown.height, RED);
		}
		if (expandLeft) {
			DrawRectangle(rectLeft.x, rectLeft.y, rectLeft.width, rectLeft.height, RED);
		}
		if (expandRight) {
			DrawRectangle(rectRight.x, rectRight.y, rectRight.width, rectRight.height, RED);
		}*/
	}
}