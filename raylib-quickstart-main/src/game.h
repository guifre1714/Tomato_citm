#pragma once
#include <player.h>

class Game {
public:
	Game();
	~Game();

	void Draw();
	void Update();
	void HandleInput();

private:
	Player bomberman;
	
};