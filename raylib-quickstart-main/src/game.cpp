#include<game.h>
#include <vector>
using namespace std;

Game::Game()
{

}

Game::~Game() {

}

void Game::Draw() {
	DrawRectangleRec(bomberman.colliders[0].col, GOLD);
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
}