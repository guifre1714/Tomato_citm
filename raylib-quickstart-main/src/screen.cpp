#include <screen.h>
#include <collider.h>
using namespace std;

int cont = 0;

Screen::Screen() {};
Screen::~Screen() {};

void Screen::Draw() {};
void Screen::HandleInput() {};
void Screen::Update() {};
bool Screen::nextLevel() {
	if (cont>179) {
		cont = 0;
		return true;
	}
	else {
		cont++;
		return false;
	}
};