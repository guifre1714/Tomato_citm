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

	Camera2D camera = { 0 };
	camera.target.x = 608;
	camera.target.y = screenHeight/2.0f-20;
	camera.offset.x = screenWidth / 2.0f;
	camera.offset.y = screenHeight / 2.0f;
	camera.rotation = 0.0f;
	camera.zoom = 3.0f;

	while (!WindowShouldClose())
	{
		string puntuacioText = "Score: " + to_string(puntuacio);
		int textWidth = MeasureText(puntuacioText.c_str(), 20);

		game.HandleInput();

		//ANIMACIO BOMBERMAN
		//game.bomberman.frameContadorB++;
		//if (game.bomberman.frameContadorB >= (60 / game.bomberman.frameSpeedB))
		//{
		//	game.bomberman.frameContadorB = 0;
		//	game.bomberman.currentFrameB++;
		//}
		//if (game.bomberman.currentFrameB > 5) game.bomberman.currentFrameB = 0; {

		//	game.bomberman.frameRecB.x = (float)game.bomberman.currentFrameB * (float)game.bomberman.bmanTXT.width / 3; //MIDA DISPLAY FRAME
		//}
		
		game.bomberman.frameRecB.x += 12.0f;
		if (game.bomberman.frameRecB.x>36.0f) {
			game.bomberman.frameRecB.x == 0;
		}


		BeginDrawing();
		ClearBackground(WHITE);
			
		BeginMode2D(camera);
		//cal ajustar mida per a que quadri ! ! ! ! ! ! ! ! ! !  ! !  ! ! ! 
		if (game.bomberman.bmanPos.x >= 588 && game.bomberman.bmanPos.x <= 652) {
			camera.target = { game.bomberman.bmanPos.x + 20, (float)screenHeight / 2 - 20};
		}
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		game.Draw();
		DrawText(puntuacioText.c_str(), screenWidth - textWidth - 20, 20, 20, BLACK);
		

		EndMode2D();
		EndDrawing();
	}


	CloseWindow();
	return 0;
}