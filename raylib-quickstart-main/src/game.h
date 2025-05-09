#pragma once
#include <vector>
#include <player.h>
#include <collider.h>
using namespace std;

class Game {
public:
	Game();
	~Game();

	void Draw();
	void Update();
	void HandleInput();

	vector <Collider> colliders;

	Collider col1;
private:
	Player bomberman;
};