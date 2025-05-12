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

	//interficie
	int puntuacio = 0;
	int vida = 3;
	int contador = 200;
	float temps = 0.0f;
	const int fontSize = 65;

	//Càmera
	Camera2D camera = { 0 };
	camera.target.x = 608;
	camera.target.y = screenHeight/2.0f-20;
	camera.offset.x = screenWidth / 2.0f;
	camera.offset.y = screenHeight / 2.0f;
	camera.rotation = 0.0f;
	camera.zoom = 3.0f;

	while (!WindowShouldClose())
	{
		
		
#pragma region Animacions Bomberman
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

		//anim
		game.bomberman.frameRecB.x += 12.0f; //passa al seguent frame
		if (game.bomberman.frameRecB.x > 36.0f) { //si arriba al final del spritesheet-
			game.bomberman.frameRecB.x == 0;	//-torna al 1r frame
		}
#pragma endregion

		
			

		//interficie superior
		float delta = GetFrameTime();
		temps += delta;
		if (temps >= 1.0f && contador > 0) 
		{
			contador--;
			temps = 0.0f;
		}
		string puntuacioText = to_string(puntuacio);
		int textw1 = MeasureText(puntuacioText.c_str(), 50);
		string vidaText = "LEFT " + to_string(vida - 1);
		int textw2 = MeasureText(vidaText.c_str(), 50);
		const char* contadortext = TextFormat("%d", contador);
		int textWidth = MeasureText(contadortext, fontSize);
		string TIMEText = "TIME ";
		int textw4 = MeasureText(TIMEText.c_str(), 50);

		game.HandleInput();


		BeginDrawing();
		ClearBackground(WHITE);

		//INICI CÀMERA (estàtic respecte a la càmera)
		BeginMode2D(camera);
		if (game.bomberman.bmanPos.x >= 588 && game.bomberman.bmanPos.x <= 652) 
		{
			camera.target = { game.bomberman.bmanPos.x + 20, (float)screenHeight / 2 - 20};
		}
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		game.Draw();

		//FINAL CÀMERA (estàtic respecte a la pantalla)
		EndMode2D();
		DrawText(puntuacioText.c_str(), screenWidth - textw1 - 550, 32, 65, BLACK);
		DrawText(vidaText.c_str(), screenWidth - textw2 - 110, 32, 65, BLACK);
		DrawText(contadortext, (screenWidth - textWidth) / 5, screenHeight / 11 - fontSize / 2, fontSize, BLACK);
		DrawText(TIMEText.c_str(), screenWidth - textw4 - 1105, 32, 65, BLACK);

		EndDrawing();

	}

		CloseWindow();
		return 0;
	
}