#include<menu.h>
#include <vector>
#include <string>
#include <game.h>
#include "raylib.h"
using namespace std;

Menu::Menu()
{
	bgm = LoadMusicStream("music/01. Title Screen.mp3");
	Fons = LoadTexture("Sprites/menu/titol.png");
}

Menu::~Menu() {
	UnloadMusicStream(bgm);
}

void Menu::Draw() {
}

void Menu::HandleInput() {
	if (IsKeyPressed(KEY_ESCAPE)) {
		abort();
	}
}

void Menu::Update() {

}