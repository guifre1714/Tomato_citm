#include <screen.h>
#include <collider.h>
using namespace std;

Screen::Screen() {
	duration = 179;
	timer = 0;
};
Screen::~Screen() {};

void Screen::Draw() {};
void Screen::HandleInput() {};
void Screen::Update() {};
bool Screen::nextLevel() {return true;};