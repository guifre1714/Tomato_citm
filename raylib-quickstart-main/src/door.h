#pragma once
#include <powerUp.h>

class Door : public powerUp {
public:
	Door();
	~Door();
	bool playerCol(Player* player);
	/*vector <EN01>* enemies;*/
};