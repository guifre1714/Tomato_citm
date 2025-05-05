#include "raylib.h"
#include <vector>
#include <iostream>

#include "resource_dir.h"
#include <game.hpp>


int main()
{
	//basics per a funcionar
	const int screenWidth = 1000;
	const int screenHeight = 500;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);

	//load textures

	//vectors

	//camara

	Game game;

	while (!WindowShouldClose())
	{
		//input

		//update

		//render(draw)

		BeginDrawing();
		ClearBackground(WHITE);
		game.Draw();

		EndDrawing();
	}


	CloseWindow();
	return 0;
}