#include <powerUp.h>

class bombUp : public powerUp {
public:
	bombUp();
	~bombUp();

	bool playerCol(Player* player);
};