#include<game.h>
#include <vector>
#include <string>
using namespace std;

Game::Game()
{
	Player player;
	bomberman = player;
	Fons = LoadTexture("Sprites/Fons.png");
	bgm = LoadMusicStream("music/03. Main BGM.mp3");
	//walk = LoadMusicStream("SFX/walk.wav");
}

Game::~Game() {
	bomberman.~Player();
	//UnloadMusicStream(bgm);
	//UnloadMusicStream(walk);
}

void Game::Draw() {
	//BUCLE FOR PER PINTAR ELS COLLIDERS DE LES CAIXES
	/*for (int i = 0; i < bomberman.colliders.size(); i++) {
		DrawRectangleRec(bomberman.colliders[i].col, GOLD);
	}*/
	bomberman.Draw();
}

void Game::HandleInput() {
	if (IsKeyDown(KEY_LEFT)) {
		bomberman.MoveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		bomberman.MoveRight();
	}
	else if (IsKeyDown(KEY_UP)) {
		bomberman.MoveUp();
	}
	else if (IsKeyDown(KEY_DOWN)) {

		bomberman.MoveDown();
	}
	else {
		bomberman.bmanTXT = LoadTexture("Sprites/idle.png");
	}
}

void Game::Update() {

}