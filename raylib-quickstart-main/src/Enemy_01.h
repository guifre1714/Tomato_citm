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
    EN01();
    void Draw();
    void Update(const vector<Collider>& colliders);
    ~EN01();

    Rectangle rect;
    Vector2 velocity;
    vector<Collider> collidersRef;

    EN01(float x, float y, float width, float height, float vx, float vy)
    {
        rect = { x, y, width, height };
        velocity = { vx, vy };
    }
    
};
