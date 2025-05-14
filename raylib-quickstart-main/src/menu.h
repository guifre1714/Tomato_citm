#include <vector>
#include <screen.h>
using namespace std;

class Menu : public Screen {
public:
	Menu();
	~Menu();

	void Draw();
	void Update();
	void HandleInput();
	int selected;
};