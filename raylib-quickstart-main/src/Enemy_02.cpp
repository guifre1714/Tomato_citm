#include <Enemy_02.h>
#include <game.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <player.h>
#include <ctime>
#include <collider.h>
#include <ctime>  


using namespace std;

EN02::EN02(Vector2 position, vector<Collider>* colliders, Player* player, vector <Bomba>* bombes)
{
    //Set all variables
    velocity.x = 0.8;
    velocity.y = 0.8;
    direction = rand() % 4;
    collidersRef = colliders;
    EN_pos = position;
    EN_frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/enemics/moneda.png");
    bomberman = player;
    isAlive = true;
    points = 8000;

    currentFrameEN = 0;
    frameContadorEN = 0;
    frameSpeedEN = 8; //marca la velocitat dels FPS
    totalFramesEN = 6;
    ampladaFramesEN = 16;
    timer = 0.0f;
    bombs = bombes;
    move = true;
}

void EN02::Update()
{
    //Set the rectangles that check the directions the enemy can move on to their needed positions.
    rectUp = { EN_pos.x + 2, EN_pos.y - 2, 10, 1 };
    rectDown = { EN_pos.x + 2, EN_pos.y + 18, 10, 1 };
    rectLeft = { EN_pos.x - 2, EN_pos.y + 2, 1, 10 };
    rectRight = { EN_pos.x + 18, EN_pos.y + 2, 1, 10 };
    bomberDie();//Check if the enemy kills the player
    bombDie();//Check if the enemy has to die.
    EN_hitbox = { EN_pos.x + 1 ,EN_pos.y + 1, 13, 13 };//Set the new position of the hitbox.
    EN_col = { EN_pos.x - 1 ,EN_pos.y - 1, 17, 17 };//Set the new position of the collider.

    //Set the window of time in which the enemy may change direction.
    int randomValue = 0;
    interval = GetRandomValue(3, 4);
    //Set the timer
    float deltaTime = GetFrameTime();
    timer += deltaTime;

    if (timer >= interval) {//If enough time has passed, change movement direction.
        randomValue = GetRandomValue(1, 4);
        timer = 0.0f;
        interval = GetRandomValue(3, 4);
        direction = randomValue;
    }
    Direction();//Check if the direction may be changed because of circumstances other than the timer.
    if (move) {
        //Check if the direction in which the enemy is moving has no obstacles and move if it doesn't.
        if (direction == 1 && !colUp) {
            EN_pos.y -= velocity.y;
        }
        else if (direction == 2 && !colDown) {
            EN_pos.y += velocity.y;
        }
        else if (direction == 3 && !colLeft) {
            EN_pos.x -= velocity.x;
        }
        else if (direction == 4 && !colRight) {
            EN_pos.x += velocity.x;
        }
        else { timer = interval; Direction(); }
    }
}


void EN02::Dead() {//Function that immobilizes the enemy and loads the death animation.
    move = false;
    EN_col = { 0, 0, 0, 0 };
    UnloadTexture(EN_texture);
    EN_texture = LoadTexture("Sprites/enemics/mortM.png");
    currentFrameEN = 0;
    totalFramesEN = 5;
}

void EN02::Direction() {//Function that changes the direction of movement depending on parameters others than the timer.
    colUp = false;
    colDown = false;
    colLeft = false;
    colRight = false;
    for (int i = 0; i < collidersRef->size(); i++) {//Check if the enemy is colliding with any of the colliders in the map (passed by reference as a vector previously in the constructor).
        if (!colUp) {
            if ((*collidersRef)[i].breakable == false) {//In the case of this specific enemy, it can pass through breakable blocks, so it ignores collisions if the block is breakable.
                colUp = CheckCollisionRecs(rectUp, (*collidersRef)[i].col);
            }
        }
        if (!colDown) {
            if ((*collidersRef)[i].breakable == false) {
                colDown = CheckCollisionRecs(rectDown, (*collidersRef)[i].col);
            }
        }
        if (!colLeft) {
            if ((*collidersRef)[i].breakable == false) {
                colLeft = CheckCollisionRecs(rectLeft, (*collidersRef)[i].col);
            }
        }
        if (!colRight) {
            if ((*collidersRef)[i].breakable == false) {
                colRight = CheckCollisionRecs(rectRight, (*collidersRef)[i].col);
            }
        }
    }
    //If the enemy has free space to a side and it isn't already moving in that direction or the opposite, it has a 1/2 chance of changing its direction to that one.
    if (!colUp && direction != 1 && direction != 2 && timer >= 1) {
        int i = GetRandomValue(1, 10);
        timer = 0.0f;

        if (i > 3) direction = 1;
    }
    if (!colDown && direction != 1 && direction != 2 && timer >= 1) {
        int i = GetRandomValue(1, 10);
        timer = 0.0f;
        if (i > 3) direction = 2;
    }
    if (!colLeft && direction != 3 && direction != 4 && timer >= 1) {
        int i = GetRandomValue(1, 10);
        timer = 0.0f;

        if (i > 3) direction = 3;
    }
    if (!colRight && direction != 3 && direction != 4 && timer >= 1) {
        int i = GetRandomValue(1, 10);
        timer = 0.0f;
        if (i > 3) direction = 4;
    }
    //Stops the enemy from bouncing left and right/up and down in narrow paths.
    if (colUp && colDown && !colLeft && !colRight && direction != 3 && direction != 4 && timer >= 0.5) {
        int i = GetRandomValue(1, 2);
        timer = 0.0f;
        if (i == 3) {
            direction = 4;
        }
        else {
            direction = 3;
        }
    }
    else if (!colUp && !colDown && colLeft && colRight && direction != 1 && direction != 2 && timer >= 0.5) {
        int i = GetRandomValue(1, 2);
        timer = 0.0f;
        if (i == 1) {
            direction = 1;
        }
        else {
            direction = 2;
        }
    }
}