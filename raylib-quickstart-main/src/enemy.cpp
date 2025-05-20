#include <Enemy.h>
#include <ctime>
#include <ctime>  


using namespace std;

Enemy::Enemy() {
    isAlive = true;
};
Enemy:: ~Enemy()
{

}
void Enemy::Draw()
{
    frameContadorEN++;
    if (frameContadorEN >= (60 / frameSpeedEN)) {
        frameContadorEN = 0;
        currentFrameEN++;

        if (currentFrameEN == totalFramesEN) {
            if (totalFramesEN == 5) {
                isAlive = false;
            }
            else {
                currentFrameEN = 0;
            }
        }
        EN_frameRec.x = (float)currentFrameEN * ampladaFramesEN;//ampladaFrames = (float)Texture.Width/num requadres a dividir
    }
    DrawRectangle(EN_col.x, EN_col.y, EN_col.width, EN_col.height, RED);
    DrawTextureRec(EN_texture, EN_frameRec, EN_pos, WHITE);
}

void Enemy::Update(){}

bool Enemy::Collide() {
    return false;

}
void Enemy::bombDie() {
    bool colUp = false;
    bool colDown = false;
    bool colLeft = false;
    bool colRight = false;
    for (int i = 0; i < bombs->size(); i++) {
        if ((*bombs)[i].boom == true) {
            colUp = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectUp);
            colDown = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectDown);
            colLeft = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectLeft);
            colRight = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectRight);
        }
        if (colUp || colDown || colLeft || colRight) {
            if (isAlive) {
                Dead();
                break;
            }
        }
    }
}
void Enemy::bomberDie() {
    bool col = CheckCollisionRecs(EN_hitbox, bomberman->bmanCol);
    if (col && bomberman->isAlive) {
        bomberman->Dead();
    }
}
void Enemy::Dead(){
    move = false;
    EN_texture = LoadTexture("Sprites/enemics/mortG.png");
    currentFrameEN = 0;
    totalFramesEN = 5;
}