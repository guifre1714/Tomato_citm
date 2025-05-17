#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
#include <bomba.h>
#include <cmath>
#include <limits>

Player::Player() {
	bombExist = false;
	isAlive = true;
	bombPlus = false;
	bmanTXT = LoadTexture("Sprites/idle.png");
	bombSound = LoadSound("SFX/bomb.wav");
	vel = 0.8f;

	bmanPos.x = 409; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!
	bmanPos.y = 272;
	
	bmanCol = { bmanPos.x, bmanPos.y, 12, 15 };
	myCollider = { bmanPos.x, bmanPos.y, 11, 14 };

	frameRecB = { 0.0f, 0.0f, 12.0f, 16.0f };

	currentFrameB = 0;
	frameContadorB = 0;
	frameSpeedB = 8; //marca la velocitat dels FPS
	
	totalFrames = 3;
	ampladaFrames = 12;
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}


void Player::Draw() {
	myCollider.x = bmanPos.x+1; myCollider.y = bmanPos.y+1;
	frameContadorB ++;
	if (frameContadorB >= (60 / frameSpeedB)) {
		frameContadorB = 0;
		currentFrameB ++;

		if (currentFrameB > totalFrames) {
			currentFrameB = 0;
		}
		frameRecB.x = (float)currentFrameB * ampladaFrames;//ampladaFrames = (float)Texture.Width/num requadres a dividir
	}
	if (bombs.size() > 0 && !bombExist) {
		bombs.erase(bombs.begin());
	}
	else if (bombExist) {
		DrawTextureRec(bombs[0].bombTEXT, bombs[0].frameRec, bombs[0].bombPos, WHITE);
	}
	DrawTextureRec(bmanTXT,frameRecB, bmanPos, WHITE);
	DrawRectangle(myCollider.x, myCollider.y, myCollider.width, myCollider.height, GOLD);
}

void Player::Dead() {
	isAlive = false;
	totalFrames = 7;
	ampladaFrames = 16;
	frameRecB = { 0.0f,0.0f,16.0f,16.0f };
	frameSpeedB = 4;
	bmanTXT = LoadTexture("Sprites/death.png");
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
	Bomba bomb(snapPositions[getClosestSnapIndex(bmanPos,snapPositions)], bombPlus, &colliders, &bombExist);
	bombs.insert(bombs.end(), bomb);
	bombExist = true;
	PlaySound(bombSound);
}

int Player::getClosestSnapIndex(const Vector2& point, const vector<Vector2>& snapPositions) {
	int closestIndex = -1;
	float minDistance = numeric_limits<float>::max();

	for (size_t i = 0; i < snapPositions.size(); i++) {
		float distance = distanceBetween(point, snapPositions[i]);
		if (distance < minDistance) {
			minDistance = distance;
			closestIndex = static_cast<int>(i);
		}
	}
	return closestIndex;
}

float Player::distanceBetween(const Vector2& a, const Vector2& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return std::sqrt(dx * dx + dy * dy);
}