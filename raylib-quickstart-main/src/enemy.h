#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <collider.h>
#include <player.h>
#include <screen.h>
#include <bomba.h>


using namespace std;


class Enemy
{
public:
    Enemy();
    ~Enemy();

    virtual void Draw();
    virtual void Update();
    virtual bool Collide();

    Vector2 EN_pos;
    Rectangle EN_hitbox;
    Rectangle EN_col;
    Rectangle EN_frameRec;
    Vector2 velocity;
    vector<Collider>* collidersRef;
    Texture2D EN_texture;
    Player* bomberman;
    vector <Bomba>* bombs;

    int currentFrameEN;
    int frameContadorEN;
    int frameSpeedEN; //marca la velocitat dels FPS
    int totalFramesEN;
    int ampladaFramesEN;

    int direction;
    int points;
    float timer;

    bool isAlive;
    bool move;

    virtual void bomberDie();
    virtual void bombDie();
    void Dead();
};
