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
    bomberDie();
    bombDie();
    EN_hitbox = { EN_pos.x+1 ,EN_pos.y+1, 13, 13 };
    EN_col = { EN_pos.x - 1 ,EN_pos.y - 1, 17, 17 };

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