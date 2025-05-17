#pragma once
#include <collider.h>
#include <player.h>

class powerUp : public Collider {
public:
	powerUp();
	~powerUp();
	string type;
	virtual bool playerCol(Player* player);
};