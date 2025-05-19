#include <Enemy_01.h>
#include<game.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <player.h>
#include <ctime>
#include <collider.h>
#include <ctime>  


using namespace std;

EN01::EN01(Vector2 position, vector<Collider>* colliders, Player* player)
{
    velocity.x = 0.8;
    velocity.y = 0.8;
    direction = rand() % 4;
    collidersRef = colliders;
    EN_pos = position;
    EN_frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/enemics/globus.png");
    bomberman = player;

    currentFrameEN = 0;
    frameContadorEN = 0;
    frameSpeedEN = 4; //marca la velocitat dels FPS
    totalFramesEN = 6;
    ampladaFramesEN = 16;
    timer = 0.0f;

}
EN01:: ~EN01() 
{

}
void EN01::Draw()
{
    frameContadorEN++;
    if (frameContadorEN >= (60 / frameSpeedEN)) {
        frameContadorEN = 0;
        currentFrameEN++;

        if (currentFrameEN > totalFramesEN - 1) {
            currentFrameEN = 0;
            /*if (isAlive) {
                
            }*/
        }
        EN_frameRec.x = (float)currentFrameEN * ampladaFramesEN;//ampladaFrames = (float)Texture.Width/num requadres a dividir
    }
    DrawTextureRec(EN_texture, EN_frameRec, EN_pos, WHITE);
}
    
void EN01::Update()
{
    bomberDie();
    EN_hitbox = { EN_pos.x ,EN_pos.y, 16, 16 };
   /* for (int i = 0; i < collidersRef.size(); i++) {
        if (CheckCollisionRecs(EN_hitbox, collidersRef[i]->col)) {
            velocity.x = velocity.x * -1;
            velocity.y = velocity.y -1;
        } else{
            EN_pos.x += velocity.x;
            EN_pos.y += velocity.y;
        }
    }*/
    int randomValue = 0;
    const float interval = 1.0f;
    srand(time(NULL));

    float deltaTime = GetFrameTime();
    timer += deltaTime;

    if (timer >= interval) {
        randomValue = GetRandomValue(1, 4);
        timer = 0.0f;
        direction = randomValue;
    }
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

bool EN01::Collide() {
    bool col;
    if (direction == 1) {
        EN_hitbox.y = EN_pos.y - velocity.y;
        EN_hitbox.x = EN_pos.x;
    }
    else if (direction == 2) {
        EN_hitbox.y = EN_pos.y + velocity.y;
        EN_hitbox.x = EN_pos.x;
    }
    else if (direction == 3) {
        EN_hitbox.x = EN_pos.x - velocity.x;
        EN_hitbox.y = EN_pos.y;
    }
    else {
        EN_hitbox.x = EN_pos.x + velocity.x;
        EN_hitbox.y = EN_pos.y;
    }
    for (int i = 0; i < (*collidersRef).size(); i++) {
        col = CheckCollisionRecs(EN_hitbox, (*collidersRef)[i].col);
        if (col) {
            int randomValue = GetRandomValue(1, 4);
            timer = 0.0f;
            direction = randomValue;
            return true;
        }
    }
    if (!col) return false;
}
void EN01::bombDie() {
    /*bool colUp = false;
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
    }*/
}
void EN01::bomberDie() {
    bool col = CheckCollisionRecs(EN_hitbox, bomberman->bmanCol);
    if (col && bomberman->isAlive) {
        bomberman->Dead();
    }
}