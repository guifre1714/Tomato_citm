#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <collider.h>
#include <player.h>
#include <screen.h>


using namespace std;


class EN01
{
public:
    EN01(Vector2 position, vector<Collider>* colliders, Player* player);
    ~EN01();

    void Draw();
    void Update();
    bool Collide();

    Vector2 EN_pos;
    Rectangle EN_hitbox;
    Rectangle EN_frameRec;
    Vector2 velocity;
    vector<Collider>* collidersRef;
    Texture2D EN_texture;
    Player* bomberman;

    int currentFrameEN;
    int frameContadorEN;
    int frameSpeedEN; //marca la velocitat dels FPS
    int totalFramesEN;
    int ampladaFramesEN;

    int direction;
    float timer;

    void bomberDie();
    void bombDie();
};
