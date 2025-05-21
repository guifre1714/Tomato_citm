#pragma once
#include <enemy.h>


using namespace std;


class EN01 : public Enemy
{
public:
    EN01(Vector2 position, vector<Collider>* colliders, Player* player, vector <Bomba>* bombes);

    void Update();
    void Dead();
    void Direction();
};
