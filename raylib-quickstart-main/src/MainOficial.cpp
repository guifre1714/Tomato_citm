#include "raylib.h"
#include <vector>
#include <iostream>

#include "resource_dir.h" // utility header for SearchAndSetResourceDir


int main()
{
	//setup

	const int screenWidth = 1280;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");



	while (!WindowShouldClose())
	{

		//input


		//update


		//render (draw)


	}

	//UnloadTexture();

	CloseWindow();
	return 0;

}