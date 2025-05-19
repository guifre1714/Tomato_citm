#include <Enemy_01.h>
#include<game.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <player.h>
#include <ctime>
#include <collider.h>

using namespace std;

EN01::EN01()
{
    velocity.x = 5;
    velocity.y = 5;

    EN_pos.x = 409;
    EN_pos.y = 272;
    EN_frameRec = { 0.0f, 0.0f, 12.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/enemics/globus.png");

    currentFrameEN = 0;
    frameContadorEN = 0;
    frameSpeedEN = 8; //marca la velocitat dels FPS
    totalFramesEN = 6;
    ampladaFramesEN = 16;
}
EN01:: ~EN01() {

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
    
void EN01::Update(const vector<Collider>& colliders)
{
    collidersRef = colliders;
    EN_pos.x += velocity.x;
    EN_pos.y += velocity.y;

    for (const Collider& c : collidersRef) {
        if (CheckCollisionRecs(EN_hitbox, c.col)) {
            velocity.x *= -1;
            velocity.y *= -1;
            break;
        }
    }

    if (EN_pos.x <= 0 || EN_pos.x + EN_hitbox.width >= GetScreenWidth()) {
        velocity.x *= -1;
    }

    if (EN_pos.y <= 0 || EN_pos.y + EN_hitbox.height >= GetScreenHeight()) {
        velocity.y *= -1;
    }
}

