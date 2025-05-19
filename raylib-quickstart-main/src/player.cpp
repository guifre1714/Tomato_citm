#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
#include <bomba.h>
#include <cmath>
#include <limits>

Player::Player() {
	isAlive = true;
	bombPlus = false;
	isWallPass = false;
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
	bombDie();
	myCollider.x = bmanPos.x+1; myCollider.y = bmanPos.y+1;
	frameContadorB ++;
	if (frameContadorB >= (60 / frameSpeedB)) {
		frameContadorB = 0;
		currentFrameB ++;

		if (currentFrameB > totalFrames -1) {
			if (isAlive) {
				currentFrameB = 0;
			} else {
				if ((*maxBombs) > 1) {
					--(*maxBombs);
				}
				--(*pantalla);
				--(*vides);
			}
		}
		frameRecB.x = (float)currentFrameB * ampladaFrames;//ampladaFrames = (float)Texture.Width/num requadres a dividir
	}
	for (int i = 0; i < bombs.size(); i++) {
		if (bombs[i].bombActive == false) {
			snapPositions.insert(snapPositions.begin(), bombs[i].bombPos);
			bombs.erase(bombs.begin() + i);
		} else {
			DrawTextureRec(bombs[i].bombTEXT, bombs[i].frameRec, bombs[i].bombPos, WHITE);
		}
	}

	DrawTextureRec(bmanTXT,frameRecB, bmanPos, WHITE);
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
		if (col && !isWallPass) {
			return true;
		}
		else if (col && colliders[i].breakable == true && isWallPass==true) {
			return false;
		}
		else if (col && isWallPass == true && colliders[i].breakable == false) {
			return true;
		}

	}
	if (!col) return false;
}

void Player::createBomb() {
	if (!bombCheck()) {
		Bomba bomb(snapPositions[getClosestSnapIndex(bmanPos, snapPositions)], bombPlus, &colliders);
		snapPositions.erase(snapPositions.begin() + getClosestSnapIndex(bmanPos, snapPositions));
		bombs.insert(bombs.end(), bomb);
		PlaySound(bombSound);
	}
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
	return sqrt(dx * dx + dy * dy);
}

bool Player::bombCheck() {
	for (int i = 0; i < bombs.size(); i++) {
		return CheckCollisionRecs(bombs[i].hitBox, myCollider);
	}
}

void Player::resetPlayer() {
	isAlive = true;
	bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!
	bmanPos.y = 272;
	bmanTXT = LoadTexture("Sprites/idle.png");

	bmanCol = { bmanPos.x, bmanPos.y, 12, 15 };

	frameRecB = { 0.0f, 0.0f, 12.0f, 16.0f };

	currentFrameB = 0;

	totalFrames = 3;
	ampladaFrames = 12;
	frameSpeedB = 8; //marca la velocitat dels FPS
}

void Player::bombDie() {
	bool colUp = false;
	bool colDown = false;
	bool colLeft = false;
	bool colRight = false;
	for (int i = 0; i < bombs.size(); i++) {
		if (bombs[i].boom == true) {
			colUp = CheckCollisionRecs(myCollider, bombs[i].rectUp);
			colDown = CheckCollisionRecs(myCollider, bombs[i].rectDown);
			colLeft = CheckCollisionRecs(myCollider, bombs[i].rectLeft);
			colRight = CheckCollisionRecs(myCollider, bombs[i].rectRight);
		}
		if (colUp || colDown || colLeft || colRight) {
			if (isAlive) {
				Dead();
				break;
			}
		}
	}
}