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

    EN_pos = { 16.0f, 0.0f, 12.0f, 16.0f };
    EN_texture = LoadTexture("Sprites/idle.png");
}
EN01:: ~EN01() {

}
void EN01::Draw()
{
    /*DrawTextureRec(EN_texture,EN_pos,velocity, WHITE);*/
    DrawTexture(EN_texture, EN_pos.x,EN_pos.y,  WHITE );
}
void EN01::Update(const vector<Collider>& colliders)
{
    collidersRef = colliders;
    EN_pos.x += velocity.x;
    EN_pos.y += velocity.y;

    for (const Collider& c : collidersRef) {
        if (CheckCollisionRecs(EN_pos, c.col)) {
            velocity.x *= -1;
            velocity.y *= -1;
            break;
        }
    }

    if (EN_pos.x <= 0 || EN_pos.x + EN_pos.width >= GetScreenWidth()) {
        velocity.x *= -1;
    }

    if (EN_pos.y <= 0 || EN_pos.y + EN_pos.height >= GetScreenHeight()) {
        velocity.y *= -1;
    }
}

