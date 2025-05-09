#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>

#include "resource_dir.h"
#include <game.hpp>


int main()
{   
	//MARCEL//puntuacio

	int puntuacio = 0;

	//basics per a funcionar
	const int screenWidth = 1280;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);
	Texture Fons = LoadTexture("Sprites/Fons.png");

	//load textures

	//vectors

	//camara

	Game game;

	while (!WindowShouldClose())
	{
		//marcel//puntuacio
		ClearBackground(RAYWHITE);

		std::string puntuacioText = "Score: " + std::to_string(puntuacio);

		int textWidth = MeasureText(puntuacioText.c_str(), 20);

		DrawText(puntuacioText.c_str(), screenWidth - textWidth - 20, 20, 20, BLACK);


		//input

		//update

		//render(draw)
		game.HandleInput();

		BeginDrawing();
		ClearBackground(WHITE);
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		game.Draw();
		


		EndDrawing();
	}


	CloseWindow();
	return 0;
}