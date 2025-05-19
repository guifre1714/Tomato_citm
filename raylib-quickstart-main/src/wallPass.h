#include <powerUp.h>

class wallPass :public powerUp {
public:
	wallPass();
	~wallPass();

	bool playerCol(Player* player);
};