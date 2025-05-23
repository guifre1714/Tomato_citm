#pragma once
#include <enemy.h>


using namespace std;


class EN03 : public Enemy
{
public:
    EN03(Vector2 position, vector<Collider>* colliders, Player* player, vector <Bomba>* bombes);

    void Update();
    void Dead();
    void Direction();
};