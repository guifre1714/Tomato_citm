#include <screen.h>
#include <collider.h>
using namespace std;

Screen::Screen(Music ost, Texture background) {
	bgm = ost;
	Fons = background;
};
Screen::~Screen() {};

void Screen::Draw() {};
void Screen::HandleInput() {};
void Screen::Update() {};
bool Screen::nextLevel() {
	return false;
};