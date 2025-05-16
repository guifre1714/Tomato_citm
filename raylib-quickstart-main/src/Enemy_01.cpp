#include <Enemy_01.h>
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

    rect.width = 16;
    rect.height = 16;
}
void EN01::Draw()
{
    DrawRectangleRec(rect, RED);
}
void EN01::Update(const vector<Collider>& colliders)
{
    collidersRef = colliders;
    rect.x += velocity.x;
    rect.y += velocity.y;

    for (const Collider& c : collidersRef) {
        if (CheckCollisionRecs(rect, c.col)) {
            velocity.x *= -1;
            velocity.y *= -1;
            break;
        }
    }

    if (rect.x <= 0 || rect.x + rect.width >= GetScreenWidth()) {
        velocity.x *= -1;
    }

    if (rect.y <= 0 || rect.y + rect.height >= GetScreenHeight()) {
        velocity.y *= -1;
    }
}

