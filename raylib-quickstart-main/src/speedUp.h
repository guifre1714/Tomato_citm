#include <powerUp.h>

class speedUp : public powerUp {
public:
	speedUp(vector <Collider>* bColliders);
	~speedUp();

	bool playerCol(Player* player);
	vector <Collider>* blocs;
};