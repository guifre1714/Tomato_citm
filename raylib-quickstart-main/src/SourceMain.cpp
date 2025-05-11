#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>

#include "resource_dir.h"
#include <game.h>

using namespace std;


int main()
{   

	//basics per a funcionar
	const int screenWidth = 1280;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);

	//load textures
	Texture Fons = LoadTexture("Sprites/Fons.png");

	//vectors

	//camara

	Game game;

	int puntuacio = 0;
	
	Camera2D camera = { 0 };
	camera.target.x = game.bomberman.bmanPos.x + 20.0f;
	camera.target.y = game.bomberman.bmanPos.y + 20.0f;
	/*camera.target = game.bomberman.bmanPos+20.0f;*/
	/*camera.target = { game.bomberman.bmanPos.x + 20.0f,game.bomberman.bmanPos.y + 20.0f };*/

	camera.offset.x = screenWidth / 4.0f;
	camera.offset.y = screenHeight / 4.0f;
	//camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };

	camera.rotation = 3.0f;
	camera.zoom = 500.0f;

	while (!WindowShouldClose())
	{
		/*string puntuacioText = "Score: " + to_string(puntuacio);
		int textWidth = MeasureText(puntuacioText.c_str(), 20);*/

		


		//input

		//update

		//render(draw)
		game.HandleInput();
		/*BeginMode2D(camera);
		camera.target = { game.bomberman.bmanPos.x + 20.0f,game.bomberman.bmanPos.y + 20.0f };*/

		BeginDrawing();
		ClearBackground(WHITE);
		
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		game.Draw();
		//DrawText(puntuacioText.c_str(), screenWidth - textWidth - 20, 20, 20, BLACK);
		


		EndDrawing();
	}


	CloseWindow();
	return 0;
}