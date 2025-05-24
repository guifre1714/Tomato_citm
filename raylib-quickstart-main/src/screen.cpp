#include <screen.h>
#include <collider.h>
using namespace std;

Screen::Screen() {//Set the duration of the screen. Set the timer to 0.
	duration = 179;
	timer = 0;
};
Screen::~Screen() {};

void Screen::Draw() {};
void Screen::HandleInput() {};
void Screen::Update() {};
bool Screen::nextLevel() {return true;};