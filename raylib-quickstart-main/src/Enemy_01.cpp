#include <Enemy_01.h>
#include<game.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <player.h>
#include <ctime>
#include <collider.h>

using namespace std;

EN01::EN01(Vector2 position, vector<Collider>* colliders)
{
    velocity.x = 0.8;
    velocity.y = 0.8;
    direction = rand() % 4;
    collidersRef = colliders;
    EN_pos = position;
    EN_frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/enemics/globus.png");

    currentFrameEN = 0;
    frameContadorEN = 0;
    frameSpeedEN = 4; //marca la velocitat dels FPS
    totalFramesEN = 6;
    ampladaFramesEN = 16;


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
    DrawRectangle(EN_hitbox.x+1, EN_hitbox.y+1, 13, 13, RED);
    DrawTextureRec(EN_texture, EN_frameRec, EN_pos, WHITE);
}
    
void EN01::Update()
{
    EN_hitbox = { EN_pos.x ,EN_pos.y, 13, 13 };

   /* for (int i = 0; i < collidersRef.size(); i++) {
        if (CheckCollisionRecs(EN_hitbox, collidersRef[i]->col)) {
            velocity.x = velocity.x * -1;
            velocity.y = velocity.y -1;
        } else{
            EN_pos.x += velocity.x;
            EN_pos.y += velocity.y;
        }
    }*/
    if (direction <= 1) {
        dir = "up";
    }
    else if (direction == 2) {
        dir = "down";
    }
    else if (direction == 3) {
        dir = "left";
    }
    else {
        dir = "right";
    }
    if (dir == "up" && !Collide()) {
        EN_pos.y -= velocity.y;
    }
    if (!Collide()) {
        EN_pos.x += velocity.x;
    }
}

bool EN01::Collide() {
    bool col;
    if (dir == "up") {
        EN_hitbox.y = EN_pos.y - velocity.y;
        EN_hitbox.x = EN_pos.x;
    }
    else if (dir == "down") {
        EN_hitbox.y = EN_pos.y + velocity.y;
        EN_hitbox.x = EN_pos.x;
    }
    else if (dir == "left") {
        EN_hitbox.x = EN_pos.x - velocity.x;
        EN_hitbox.y = EN_pos.y;
    }
    else {
        EN_hitbox.x = EN_pos.x + velocity.x;
        EN_hitbox.y = EN_pos.y;
    }
    for (int i = 0; i < (*collidersRef).size(); i++) {
        col = CheckCollisionRecs(EN_hitbox, (*collidersRef)[i].col);
        if (col) return true;
    }
    if (!col) return false;
}