#include <Enemy_01.h>
#include <game.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <player.h>
#include <ctime>
#include <collider.h>
#include <ctime>  


using namespace std;

EN01::EN01(Vector2 position, vector<Collider>* colliders, Player* player, vector <Bomba>* bombes)
{
    velocity.x = 0.5;
    velocity.y = 0.5;
    direction = GetRandomValue(1, 4);
    collidersRef = colliders;
    EN_pos = position;
    EN_frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/enemics/globus.png");
    bomberman = player;
    isAlive = true;
    points = 100;

    currentFrameEN = 0;
    frameContadorEN = 0;
    frameSpeedEN = 4; //marca la velocitat dels FPS
    totalFramesEN = 6;
    ampladaFramesEN = 16;
    timer = 0.0f;
    bombs = bombes;
    move = true;
}
EN01:: ~EN01() 
{

}
    
void EN01::Update()
{
    rectUp = { EN_pos.x + 2, EN_pos.y - 2, 13, 1 };
    rectDown = { EN_pos.x + 2, EN_pos.y + 18, 13, 1 };
    rectLeft = { EN_pos.x - 2, EN_pos.y + 2, 1, 13 };
    rectRight = { EN_pos.x + 18, EN_pos.y + 2, 1, 13 };
    bomberDie();
    bombDie();
    EN_hitbox = { EN_pos.x+1 ,EN_pos.y+1, 13, 13 };
    EN_col = { EN_pos.x - 1 ,EN_pos.y - 1, 17, 17 };

    int randomValue = 0;
    interval = GetRandomValue(3, 5);

    float deltaTime = GetFrameTime();
    timer += deltaTime;

    if (timer >= interval) {
        randomValue = GetRandomValue(1, 4);
        timer = 0.0f;
        interval = GetRandomValue(3, 5);
        direction = randomValue;
    }
    Direction();
    if (move) {
        if (direction == 1 && !colUp) {
            EN_texture = LoadTexture("Sprites/enemics/globusDreta.png");
            EN_pos.y -= velocity.y;
        }
        else if (direction == 2 && !colDown) {
            EN_texture = LoadTexture("Sprites/enemics/globusEsquerra.png");
            EN_pos.y += velocity.y;
        }
        else if (direction == 3 && !colLeft) {
            EN_texture = LoadTexture("Sprites/enemics/globusEsquerra.png");
            EN_pos.x -= velocity.x;
        }
        else if (direction == 4 && !colRight) {
            EN_texture = LoadTexture("Sprites/enemics/globusDreta.png");
            EN_pos.x += velocity.x;
        }
        else { timer = interval; Direction(); }
    }
}

void EN01::Dead() {
    move = false;
    EN_texture = LoadTexture("Sprites/enemics/mortG.png");
    currentFrameEN = 0;
    totalFramesEN = 5;
}

void EN01::Direction() {
    colUp = false;
    colDown = false;
    colLeft = false;
    colRight = false;
    for (int i = 0; i < collidersRef->size(); i++) {
        if (!colUp) {
            colUp = CheckCollisionRecs(rectUp, (*collidersRef)[i].col);
        }
        if (!colDown) {
            colDown = CheckCollisionRecs(rectDown, (*collidersRef)[i].col);
        }
        if (!colLeft) {
            colLeft = CheckCollisionRecs(rectLeft, (*collidersRef)[i].col);
        }
        if (!colRight) {
            colRight = CheckCollisionRecs(rectRight, (*collidersRef)[i].col);
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

    if (colUp && colDown && colLeft && colRight) {
        !move;
    }
    else { move; }
}