#include<game.h>

Game::Game()
{

}

Game::~Game() {

}

void Game::Draw() {
	bomberman.Draw();
}

void Game::HandleInput() {
	
	bomberman.Animation();

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