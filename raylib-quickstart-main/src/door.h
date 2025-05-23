#pragma once
#include <powerUp.h>

class Door : public powerUp {
public:
	Door();
	~Door();
	void Draw();
	bool playerCol(Player* player);
	/*vector <EN01>* enemies;*/
};