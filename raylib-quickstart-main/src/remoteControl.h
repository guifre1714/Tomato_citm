#include<powerUp.h>

class remoteControl :public powerUp {
public:
	remoteControl();
	~remoteControl();

	bool playerCol(Player* player);
};