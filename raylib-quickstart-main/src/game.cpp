#include<game.h>
#include <vector>
using namespace std;

Game::Game()
{
	col1.col = { 16, 16, 16, 16 };
	colliders.insert(colliders.begin(), col1);
}

Game::~Game() {

}

void Game::Draw() {
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