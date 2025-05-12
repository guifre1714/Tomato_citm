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
	const int screenHeight = 720;

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
	int vida = 3;

	Camera2D camera = { 0 };
	camera.target.x = 608;
	camera.target.y = screenHeight / 2.0f - 20;
	camera.offset.x = screenWidth / 2.0f;
	camera.offset.y = screenHeight / 2.0f;
	camera.rotation = 0.0f;
	camera.zoom = 3.5f;

	while (!WindowShouldClose())
	{
		//interficie superior
		string puntuacioText = to_string(puntuacio);
		int textw1 = MeasureText(puntuacioText.c_str(), 500);

		string vidaText = "Left " + to_string(vida-1);
		int textw2 = MeasureText(vidaText.c_str(), 40);

		


		//input

		//update

		//render(draw)
		game.HandleInput();
		

		BeginDrawing();
		ClearBackground(WHITE);
			
		BeginMode2D(camera);
		//cal ajustar mida per a que quadri ! ! ! ! ! ! ! ! ! !  ! !  ! ! ! 
		if (game.bomberman.bmanPos.x >= 588 && game.bomberman.bmanPos.x <= 654) {
			camera.target = { game.bomberman.bmanPos.x + 20, (float)screenHeight / 2 - 68};
		if (game.bomberman.bmanPos.x >= 588 && game.bomberman.bmanPos.x <= 652) {
			camera.target = { game.bomberman.bmanPos.x + 20, (float)screenHeight / 2 - 20};
		}
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		game.Draw();
		DrawText(puntuacioText.c_str(), screenWidth - textw1 - 50, 50, 50, BLACK);
		DrawText(vidaText.c_str(), screenWidth - textw2 - 400, 230, 30, BLACK);
		

		EndMode2D();
		EndDrawing();
	}


	CloseWindow();
	return 0;
}