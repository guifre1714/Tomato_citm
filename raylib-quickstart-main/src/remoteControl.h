#include<powerUp.h>

class remoteControl :public powerUp {
public:
	remoteControl(vector <Collider>* bColliders);
	~remoteControl();

	bool playerCol(Player* player);
	vector <Collider>* blocs;
};