#include<game.h>
#include <vector>
#include <string>
using namespace std;

int i = 0;

Game::Game()
{
	Player player;
	bomberman = player;
	Fons = LoadTexture("Sprites/Fons.png");
	bgm = LoadMusicStream("music/03. Main BGM.mp3");
	walk = LoadSound("SFX/walk.wav");
}

Game::~Game() {
	bomberman.~Player();
	UnloadMusicStream(bgm);
	UnloadSound(walk);
}

void Game::Draw() {
	//BUCLE FOR PER PINTAR ELS COLLIDERS DE LES CAIXES
	/*for (int i = 0; i < bomberman.colliders.size(); i++) {
		DrawRectangleRec(bomberman.colliders[i].col, GOLD);
	}*/
	bomberman.Draw();
}

void Game::HandleInput() {
	cout << i;
	if (IsKeyDown(KEY_LEFT)) {
		bomberman.MoveLeft();
		if (i > 20) {
			PlaySound(walk);
			i = 0;
		}
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		bomberman.MoveRight();
		if (i > 20) {
			PlaySound(walk);
			i = 0;
		}
	}
	else if (IsKeyDown(KEY_UP)) {
		bomberman.MoveUp();
		if (i > 20) {
			PlaySound(walk);
			i = 0;
		}
	}
	else if (IsKeyDown(KEY_DOWN)) {

		bomberman.MoveDown();
		if (i > 20) {
			PlaySound(walk);
			i = 0;
		}
	}
	else {
		bomberman.bmanTXT = LoadTexture("Sprites/idle.png");
	}
	i++;
}

void Game::Update() {

}