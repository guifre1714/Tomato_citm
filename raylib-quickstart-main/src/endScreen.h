#include <vector>
#include <screen.h>
using namespace std;

class endScreen : public Screen {
public:
	endScreen();
	~endScreen();

	void Draw();
	void Update();
	void HandleInput();

	Texture2D bombHuman;
	Vector2 humanPos;
	Rectangle frameRec;
	
	int currentFrame;
	int frameContador;
	int frameSpeed; //marca la velocitat dels FPS
	int totalFrames;
	int ampladaFrames;

};