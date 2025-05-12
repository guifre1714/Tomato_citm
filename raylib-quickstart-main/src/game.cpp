#include<game.h>
#include <vector>
using namespace std;

Game::Game()
{
	
}

Game::~Game() {
	bomberman.~Player();
}

void Game::Draw() {
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
	
}

void Game::Update() {
	

}