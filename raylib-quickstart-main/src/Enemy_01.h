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
    ~EN01();
    Rectangle EN_pos;
    Vector2 velocity;
    vector<Collider> collidersRef;
    Texture2D EN_texture;

    void Draw();
    void Update(const vector<Collider>& colliders);
};
