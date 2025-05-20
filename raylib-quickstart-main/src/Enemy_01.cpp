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
    direction = rand() % 4;
    collidersRef = colliders;
    EN_pos = position;
    EN_frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/enemics/globus.png");
    bomberman = player;
    isAlive = true;
    points = 200;

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
    bool colUp = false;
    bool colDown = false;
    bool colLeft = false;
    bool colRight = false;

    rectUp = { EN_pos.x + 2, EN_pos.y - 14, 10, 10 };
    rectDown = { EN_pos.x + 2, EN_pos.y + 14, 10, 10 };
    rectLeft = { EN_pos.x - 14, EN_pos.y + 2, 10, 10 };
    rectRight = { EN_pos.x + 14, EN_pos.y + 2, 10, 10 };
    bomberDie();
    bombDie();
    EN_hitbox = { EN_pos.x+1 ,EN_pos.y+1, 13, 13 };
    EN_col = { EN_pos.x - 1 ,EN_pos.y - 1, 17, 17 };

    int randomValue = 0;
    float interval = 5;
    srand(time(NULL));

    float deltaTime = GetFrameTime();
    timer += deltaTime;

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
        int i = rand() % 2;
        timer = 0.0f;

        if (i == 2) direction = 1;
    }
    if (!colDown && direction != 1 && direction != 2 && timer >= 1) {
        int i = rand() % 2;
        timer = 0.0f;
        if (i == 3) direction = 2;
    }
    if (!colLeft && direction != 3 && direction != 4 && timer >= 1) {
        int i = rand() % 2;
        timer = 0.0f;

        if (i == 3) direction = 3;
    }
    if (!colRight && direction != 3 && direction != 4 && timer >= 1) {
        int i = rand() % 2;
        timer = 0.0f;
        if (i == 3) direction = 4;
    }
    if (timer >= interval) {
        randomValue = GetRandomValue(1, 4);
        timer = 0.0f;
        interval = GetRandomValue(1, 10);
        direction = randomValue;
    }
    if (move) {
        if (direction == 1 && !Collide()) {
            EN_pos.y -= velocity.y;
        }
        else if (direction == 2 && !Collide()) {
            EN_pos.y += velocity.y;
        }
        else if (direction == 3 && !Collide()) {
            EN_pos.x -= velocity.x;
        }
        else if (direction == 4 && !Collide()) {
            EN_pos.x += velocity.x;
        }
    }
}

bool EN01::Collide() {
    bool col;
    if (direction == 1) {
        EN_col.y = EN_pos.y - velocity.y;
        EN_col.x = EN_pos.x;
    }
    else if (direction == 2) {
        EN_col.y = EN_pos.y + velocity.y;
        EN_col.x = EN_pos.x;
    }
    else if (direction == 3) {
        EN_col.x = EN_pos.x - velocity.x;
        EN_col.y = EN_pos.y;
    }
    else {
        EN_col.x = EN_pos.x + velocity.x;
        EN_col.y = EN_pos.y;
    }
    for (int i = 0; i < (*collidersRef).size(); i++) {
        col = CheckCollisionRecs(EN_col, (*collidersRef)[i].col);
        if (col) {
            int randomValue = GetRandomValue(1, 4);
            timer = 0.0f;
            direction = randomValue;
            return true;
        }
    }
    if (!col) return false;
}

void EN01::Dead() {
    move = false;
    EN_texture = LoadTexture("Sprites/enemics/mortG.png");
    currentFrameEN = 0;
    totalFramesEN = 5;
}