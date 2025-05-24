#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
#include <bomba.h>
#include <cmath>
#include <limits>

Player::Player() {
	//Set up the player to its initial state
	isAlive = true;
	isWallPass = false;
	idle = true;
	bmanTXT = LoadTexture("Sprites/bomberman/idle.png");
	bombSound = LoadSound("SFX/bomb.wav");
	deathSound = LoadSound("SFX/mort.wav");
	vel = 0.8f;

	bmanPos.x = 409;
	bmanPos.y = 272;
	
	bmanCol = { bmanPos.x, bmanPos.y, 15, 15 };
	myCollider = { bmanPos.x, bmanPos.y, 11, 14 };

	frameRecB = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrameB = 0;
	frameContadorB = 0;
	frameSpeedB = 8; //marca la velocitat dels FPS
	
	totalFrames = 3;
	ampladaFrames = 16;
	p_guanyats = 0;
	!gainedBomb;
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}

void Player::Draw() {
	bombDie();//Check if a bomb killed you
	myCollider.x = bmanPos.x+1; myCollider.y = bmanPos.y+1;//Update collider to maintain it in your position.
	//Animation loop
	frameContadorB ++;
	if (frameContadorB >= (60 / frameSpeedB)) {
		frameContadorB = 0;
		currentFrameB ++;
		//If animation is completed and player is alive reset it, else reset all player stats that increased in this level.
		if (currentFrameB == totalFrames) {
			if (isAlive) {
				currentFrameB = 0;
			} else {
				if ((*maxBombs) > 1 && gainedBomb) {//Only decrease max bombs if the player earnt the power in that same level (this way you get to keep it if you beat the level in which the power up appears).
					--(*maxBombs);
				}
				if (p_guanyats > 0) {
					(*score) = (*score) - p_guanyats;
					p_guanyats = 0;
				}
				--(*pantalla);
				--(*vides);
			}
		}
		frameRecB.x = (float)currentFrameB * ampladaFrames;//ampladaFrames = (float)Texture.Width/num requadres a dividir
	}

	cleanBombs();//Check if bombs should be deleted.
	for (int i = 0; i < bombs.size(); i++) {//Make it so we collide with active bombs and draw them.
		if (!bombs[i].colliderAdded && CheckCollisionRecs(myCollider, bombs[i].hitBox) == false) {
			bombs[i].colliderAdded = true;
			colliders.push_back(bombs[i].myCollider);
		}
		DrawTextureRec(bombs[i].bombTEXT, bombs[i].frameRec, bombs[i].bombPos, WHITE);
	}
	DrawTextureRec(bmanTXT,frameRecB, bmanPos, WHITE);//Draw player.
}

void Player::Dead() {
	//Set isAlive to false and initialise death sequence.
	isAlive = false;
	totalFrames = 7;
	frameSpeedB = 4;
	PlaySound(deathSound);
	bmanTXT = LoadTexture("Sprites/bomberman/death.png");
}
//The following functions make the player move in the designated position if theres no block there and play the associated animation.
void Player::MoveUp() {
	idle = false;
	bmanTXT = LoadTexture("Sprites/bomberman/walkUp.png");
	dir = "up";
	if (!Collide()) {
		bmanPos.y -= vel;
	}

}
void Player::MoveDown() {
	idle = false;
	bmanTXT = LoadTexture("Sprites/bomberman/walkDown.png");
	dir = "down";
	if (!Collide()) {
		bmanPos.y += vel;
	}
}
void Player::MoveLeft() {
	idle = false;
	bmanTXT = LoadTexture("Sprites/bomberman/walkLeft.png");
	dir = "left";
	if (!Collide()) {
		bmanPos.x -= vel;
	}
}
void Player::MoveRight() {
	idle = false;
	bmanTXT = LoadTexture("Sprites/bomberman/walkRight.png");
	dir = "right";
	if (!Collide()) {
		bmanPos.x += vel;
	}
}
//End of movement functions
bool Player::Collide() {//Function that checks if the player should collide in the direction it is moving.
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
	for (int i = 0; i < colliders.size(); i++) {//For every collider check if the player should collide with it when moving in the selected direction.
		col = CheckCollisionRecs(bmanCol, colliders[i].col);
		//Only collide if the player does not have the wallPass power up or if the block isn't breakable.
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
	if (!col) return false;//If the player doesn't collide with anything return false.
}

void Player::createBomb() {//Function that creates a bomb in the player's position (snapped to a grid to avoid bugs or breaking more blocks than desired) if there isn't a bomb already there.
	bool can = false;
	if (!bombCheck()) {
		for (int i = 0; i < colliders.size(); i++) {//Check if the bomb can be created.
			if (!can) {
				can = CheckCollisionRecs(myCollider, colliders[i].col);
			}
		}
		if (!can) {//If can is false (meaning the bomb can be put there (yes, we didn't pick the best name for the var)), place the bomb in the neares position of the grid.
			Bomba bomb(snapPositions[getClosestSnapIndex(bmanPos, snapPositions)], &colliders);
			snapPositions.erase(snapPositions.begin() + getClosestSnapIndex(bmanPos, snapPositions));
			bombs.insert(bombs.end(), bomb);
			PlaySound(bombSound);
		}
	}
}

int Player::getClosestSnapIndex(const Vector2& point, const vector<Vector2>& snapPositions) {//Function that gets the index of the closest vector2 to the player's position from a vector.
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

float Player::distanceBetween(const Vector2& a, const Vector2& b) {//Aux function to calculate distance between two Vector2.
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool Player::bombCheck() {//Check if player is in contact with bomb.
	bool collided = false;
	for (int i = 0; i < bombs.size(); i++) {
		if (!collided) {
			collided = CheckCollisionRecs(bombs[i].hitBox, myCollider);
		}
	}
	if (collided)return true;
	else return false;
}

void Player::resetPlayer() {//Reset the player to its start values (use when resetting a level).
	isAlive = true;
	bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!
	bmanPos.y = 272;
	idle = true;
	bmanTXT = LoadTexture("Sprites/bomberman/idle.png");

	bmanCol = { bmanPos.x, bmanPos.y, 14, 15 };

	frameRecB = { 0.0f, 0.0f, 16.0f, 16.0f };

	currentFrameB = 0;

	totalFrames = 3;
	ampladaFrames = 16;
	frameSpeedB = 8; //marca la velocitat dels FPS
}

void Player::bombDie() {//Check if the player should die by a bomb.
	bool colUp = false;
	bool colDown = false;
	bool colLeft = false;
	bool colRight = false;
	for (int i = 0; i < bombs.size(); i++) {//For each bomb placed, check if it is exploding and if it is check if the player is touching the explosion.
		if (bombs[i].boom == true) {
			colUp = CheckCollisionRecs(myCollider, bombs[i].rectUp);
			colDown = CheckCollisionRecs(myCollider, bombs[i].rectDown);
			colLeft = CheckCollisionRecs(myCollider, bombs[i].rectLeft);
			colRight = CheckCollisionRecs(myCollider, bombs[i].rectRight);
		}
		if (colUp || colDown || colLeft || colRight) {//If the player is in contact with an explosion:
			if (isAlive) {
				Dead();//KILL THE PLAYER BOOM
				break;
			}
		}
	}
}

void Player::cleanBombs() {
	for (size_t i = 0; i < bombs.size();) {
		// If a bomb has exploded, erase collider
		if (bombs[i].boom && bombs[i].erased == false) {
			colliders.erase(colliders.end() - 1);
			bombs[i].erased = true;
		}

		// If bomb is not active remove from list
		if (!bombs[i].bombActive) {
			// Make it so we can place a bomb again in that possition
			snapPositions.insert(snapPositions.begin(), bombs[i].bombPos);

			// E R A S E bomb (epic)
			bombs.erase(bombs.begin() + i);
		}
		else {
			i++;
		}
	}
}
