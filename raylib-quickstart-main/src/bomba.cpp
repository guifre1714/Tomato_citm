#include <bomba.h>

Bomba::Bomba(Vector2 pos, bool potenciada, vector <Collider>* pBlocs) {
	bombPos = pos;
	boom = false;
	plus = potenciada;
	blocs = pBlocs;
	bombActive = true;
	boomTime = 120;
	time = 0;
	bombTEXT = LoadTexture("Sprites/bomb/bombAni.png");
	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
	hitBox = { bombPos.x + 1, bombPos.y - 1, 16, 16 };
	myCollider.col = { bombPos.x + 2, bombPos.y - 1, 13, 13 };
	expUp = LoadTexture("Sprites/bomb/expDalt.png");
	expDown = LoadTexture("Sprites/bomb/expDown.png");
	expLeft = LoadTexture("Sprites/bomb/expLeft.png");
	expRight = LoadTexture("Sprites/bomb/expRight.png");

	currentFrame = 0;
	frameContador = 0;
	ampladaFrames = 16;
	frameSpeed = 4; //marca la velocitat dels FPS

	totalFrames = 3;
	!colUp;
	!colDown;
	!colLeft;
	!colRight;
	expandUp = true;
	expandDown = true;
	expandLeft = true;
	expandRight = true;
	colliderAdded = false;
	erased = false;
}

Bomba::~Bomba() {
}

void Bomba::Draw() {
	if (time >= boomTime && remoCon==false) {
		boom = true;
		myCollider.col = { 0,0,0,0 };
	}
	DrawRectangle(myCollider.col.x, myCollider.col.y, myCollider.col.width, myCollider.col.height, RED);
	frameContador++;
	if (frameContador >= (60 / frameSpeed)) {
		frameContador = 0;
		currentFrame++;

		if (currentFrame > totalFrames && totalFrames == 3) {
			currentFrame = 0;
		}
		else if (currentFrame > totalFrames && totalFrames > 3) {

			bombActive = false;
		}
		frameRec.x = (float)currentFrame * ampladaFrames;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
	}
	KaboomCheck();
	if (expandUp) {
		DrawTextureRec(expUp, frameRec, { rectUp.x,rectUp.y }, WHITE);
	}
	if (expandDown) {
		DrawTextureRec(expDown, frameRec, { rectDown.x,rectDown.y }, WHITE);
	}
	if (expandLeft) {
		DrawTextureRec(expLeft, frameRec, { rectLeft.x,rectLeft.y }, WHITE);
	}
	if (expandRight) {
		DrawTextureRec(expRight, frameRec, { rectRight.x,rectRight.y }, WHITE);
	}
	time++;
}

void Bomba::KaboomCheck() {
	if (!plus && boom) {
		totalFrames = 4;
		frameSpeed = 8;
		bombTEXT = LoadTexture("Sprites/bomb/expCentre.png");
		rectUp = { bombPos.x + 1, bombPos.y - 15, 13, 13 };
		rectDown = { bombPos.x + 1, bombPos.y + 15, 13, 13 };
		rectLeft = { bombPos.x - 15, bombPos.y + 1, 13, 13 };
		rectRight = { bombPos.x + 15, bombPos.y + 1, 13, 13 };
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
	}
}