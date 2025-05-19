#include <powerUp.h>

class bombUp : public powerUp {
public:
	bombUp(vector <Collider>* bColliders);
	~bombUp();

	bool playerCol(Player* player);
	vector <Collider>* blocs;
};