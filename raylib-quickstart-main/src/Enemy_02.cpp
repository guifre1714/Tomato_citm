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
    velocity.x = 1.2;
    velocity.y = 1.2;
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
EN02:: ~EN02()
{

}

void EN02::Update()
{
    bomberDie();
    bombDie();
    EN_hitbox = { EN_pos.x + 1 ,EN_pos.y + 1, 13, 13 };
    EN_col = { EN_pos.x - 1 ,EN_pos.y - 1, 17, 17 };

    int randomValue = 0;
    float interval = GetRandomValue(1, 5);

    float deltaTime = GetFrameTime();
    timer += deltaTime;

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

bool EN02::Collide() {
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
        if (col && (*collidersRef)[i].breakable == false) {
            int randomValue = GetRandomValue(1, 4);
            timer = 0.0f;
            direction = randomValue;
            return true;
        }
    }
    if (!col) return false;
}

void EN02::Dead() {
    move = false;
    EN_texture = LoadTexture("Sprites/enemics/mortM.png");
    currentFrameEN = 0;
    totalFramesEN = 5;
}