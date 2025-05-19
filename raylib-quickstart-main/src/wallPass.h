#include <powerUp.h>

class wallPass :public powerUp {
public:
	wallPass(vector <Collider>* bColliders);
	~wallPass();

	bool playerCol(Player* player);
	vector <Collider>* blocs;
};