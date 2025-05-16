#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
#include <bomba.h>

Player::Player() {
	bombExist = false;
	bmanTXT = LoadTexture("Sprites/idle.png");
	vel = 0.8f;

	bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!
	bmanPos.y = 272;
	
	bmanCol = { bmanPos.x, bmanPos.y, 12, 15 };

	frameRecB = { 0.0f, 0.0f, 12.0f, 16.0f };

	currentFrameB = 0;
	frameContadorB = 0;
	frameSpeedB = 8; //marca la velocitat dels FPS
	
	totalFrames=3;
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}


void Player::Draw() {
	frameContadorB ++;
	if (frameContadorB >= (60 / frameSpeedB)) {
		frameContadorB = 0;
		currentFrameB ++;

		if (currentFrameB > 3) {
			currentFrameB = 0;
		}
		frameRecB.x = (float)currentFrameB * 12;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
	}
	if (bombExist) {
		bombs[0].Draw();
	}
	DrawTextureRec(bmanTXT,frameRecB, bmanPos, WHITE);
}

void Player::MoveUp() {
	bmanTXT = LoadTexture("Sprites/walkBack.png");
	dir = "up";
	if (!Collide()) {
		bmanPos.y -= vel;
	}

}
void Player::MoveDown() {
	bmanTXT = LoadTexture("Sprites/walkFront.png");
	dir = "down";
	if (!Collide()) {
		bmanPos.y += vel;
	}
}
void Player::MoveLeft() {
	bmanTXT = LoadTexture("Sprites/walkLeft.png");
	dir = "left";
	if (!Collide()) {
		bmanPos.x -= vel;
	}
}
void Player::MoveRight() {
	
	bmanTXT = LoadTexture("Sprites/walkRight.png");
	dir = "right";
	if (!Collide()) {
		bmanPos.x += vel;
	}
}

bool Player::Collide() {
	bool col;
	if (dir == "up") {
		bmanCol.y = bmanPos.y - vel;
		bmanCol.x = bmanPos.x;
	}
	else if (dir == "down") {
		bmanCol.y = bmanPos.y + vel;
		bmanCol.x = bmanPos.x;
	}
	else if (dir == "left") {
		bmanCol.x = bmanPos.x - vel;
		bmanCol.y = bmanPos.y;
	}
	else {
		bmanCol.x = bmanPos.x + vel;
		bmanCol.y = bmanPos.y;
	}
	for (int i = 0; i < colliders.size(); i++) {
		col = CheckCollisionRecs(bmanCol, colliders[i].col);
		if (col) return true;
	}
	if (!col) return false;
}

void Player::createBomb() {
	Bomba bomb(bmanPos);
	bombs.insert(bombs.end(), bomb);
	bombExist = true;
}