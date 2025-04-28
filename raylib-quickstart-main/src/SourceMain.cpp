#include "raylib.h"
#include <vector>
#include <iostream>

#include "resource_dir.h"


int main()
{
	//basics per a funcionar
	const int screenWidth = 1280;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");

	//load textures

	//vectors

	//camara



	while (!WindowShouldClose())
	{
		//input



		//update


		//render(draw)



	}

	//UnloadTexture();

	CloseWindow();
	return 0;
}