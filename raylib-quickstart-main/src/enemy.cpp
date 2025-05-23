#include <Enemy.h>
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
    //Animation loop
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
    DrawTextureRec(EN_texture, EN_frameRec, EN_pos, WHITE);
}

void Enemy::Update() {};

void Enemy::bombDie() {//Function that checks if the enemy is killed by a bomb
    bool colUp = false;
    bool colDown = false;
    bool colLeft = false;
    bool colRight = false;
    for (int i = 0; i < bombs->size(); i++) {//For each bomb the player has currently placed, if the bomb has explocded:
        if ((*bombs)[i].boom == true) {
            //Checks if the enemy is colliding with the expanding explosion of the bomb
            if((*bombs)[i].expandUp) colUp = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectUp);
            if ((*bombs)[i].expandDown) colDown = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectDown);
            if ((*bombs)[i].expandLeft) colLeft = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectLeft);
            if ((*bombs)[i].expandRight) colRight = CheckCollisionRecs(EN_hitbox, (*bombs)[i].rectRight);
        }
        if (colUp || colDown || colLeft || colRight) {
            if (isAlive) {
                Dead();//Calls the Dead function if hit by explosion.
            }
        }
    }
}
void Enemy::bomberDie() {//Checks if the enemy is colliding with Bomberman. If bomberman is alive and the death animation isn't playing, kill bomberman.
    bool col = CheckCollisionRecs(EN_hitbox, bomberman->bmanCol);
    if (col && bomberman->isAlive && totalFramesEN != 5) {
        bomberman->Dead();
    }
}
void Enemy::Dead(){
}
void Enemy::Direction(){}