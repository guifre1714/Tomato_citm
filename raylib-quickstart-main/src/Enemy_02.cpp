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
    rectUp = { EN_pos.x + 2, EN_pos.y - 2, 13, 1 };
    rectDown = { EN_pos.x + 2, EN_pos.y + 18, 13, 1 };
    rectLeft = { EN_pos.x - 2, EN_pos.y + 3, 1, 12 };
    rectRight = { EN_pos.x + 18, EN_pos.y + 3, 1, 12 };
    bomberDie();
    bombDie();
    EN_hitbox = { EN_pos.x + 1 ,EN_pos.y + 1, 13, 13 };
    EN_col = { EN_pos.x - 1 ,EN_pos.y - 1, 17, 17 };

    int randomValue = 0;
    interval = GetRandomValue(3, 4);

    float deltaTime = GetFrameTime();
    timer += deltaTime;

    if (timer >= interval) {
        randomValue = GetRandomValue(1, 4);
        timer = 0.0f;
        interval = GetRandomValue(3, 4);
        direction = randomValue;
    }
    Direction();
    if (move) {
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


void EN02::Dead() {
    move = false;
    EN_col = { 0, 0, 0, 0 };
    EN_texture = LoadTexture("Sprites/enemics/mortM.png");
    currentFrameEN = 0;
    totalFramesEN = 5;
}

void EN02::Direction() {
    colUp = false;
    colDown = false;
    colLeft = false;
    colRight = false;
    for (int i = 0; i < collidersRef->size(); i++) {
        if (!colUp) {
            if ((*collidersRef)[i].breakable == false) {
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