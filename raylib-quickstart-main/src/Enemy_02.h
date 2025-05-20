#pragma once
#include <enemy.h>


using namespace std;


class EN02 : public Enemy
{
public:
    EN02(Vector2 position, vector<Collider>* colliders, Player* player, vector <Bomba>* bombes);
    ~EN02();

    void Update();
    bool Collide();
};