#include <vector>
#include <player.h>
#include <collider.h>
#include <screen.h>
using namespace std;

class Game : public Screen{
public:
	Game();
	~Game();

	void Draw();
	void Update();
	void HandleInput();

	Sound walk;
	Sound bomb;
};