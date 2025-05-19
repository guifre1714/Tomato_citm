#include <screen.h>
#include <collider.h>
using namespace std;

int cont = 0;

Screen::Screen() {
	duration = 179;
};
Screen::~Screen() {};

void Screen::Draw() {};
void Screen::HandleInput() {};
void Screen::Update() {};
bool Screen::nextLevel() {
	if (cont>duration) {
		cont = 0;
		return true;
	}
	else {
		cont++;
		return false;
	}
};