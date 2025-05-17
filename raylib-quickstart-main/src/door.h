#pragma once
#include <collider.h>
#include <Enemy_01.h>
#include <player.h>

class Door : public Collider {
public:
	Door();
	~Door();
	bool nextLevel(Player* player);
	/*vector <EN01>* enemies;*/
};