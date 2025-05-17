#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>

#include "resource_dir.h"
#include <game.h>
#include <menu.h>
#include <Enemy_01.h>
#include <breakable.h>
#include <bomba.h>


using namespace std;

//basics per a funcionar
const int screenWidth = 1280;
const int screenHeight = 720;

int screen = 0;
vector <Screen*> screens;

//interficie
int puntuacio = 0;
int vida = 3;
int contador = 200;
float temps = 0.0f;
const int fontSize = 65;

//Càmera
Camera2D camera = { 0 };

void loadNextScreen() {
	StopMusicStream(screens[screen]->bgm);
	if (screen != screens.size() - 1) {
		screen++;
		camera.target.x = 608;
		camera.target.y = screenHeight / 2.0f - 20;
		camera.offset.x = screenWidth / 2.0f;
		camera.offset.y = screenHeight / 2.0f;
		camera.rotation = 0.0f;
		camera.zoom = 3.0f;
		screens[screen]->bomberman.bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!
		screens[screen]->bomberman.bmanPos.y = 272;

		screens[screen]->bomberman.bmanCol = { screens[screen]->bomberman.bmanPos.x, screens[screen]->bomberman.bmanPos.y, 12, 15 };

		screens[screen]->bomberman.frameRecB = { 0.0f, 0.0f, 12.0f, 16.0f };

		screens[screen]->bomberman.currentFrameB = 0;
		screens[screen]->bomberman.frameContadorB = 0;
		screens[screen]->bomberman.frameSpeedB = 8; //marca la velocitat dels FPS
	}
	else { 
		screen = 0; 
		camera.target.x = screenWidth / 2.0f;
		camera.target.y = screenHeight / 2.0f;
		camera.offset.x = screenWidth / 2.0f;
		camera.offset.y = screenHeight / 2.0f;
		camera.rotation = 0.0f;
		camera.zoom = 3.0f;
		puntuacio = 0;
		vida = 3;
	}
	PlayMusicStream(screens[screen]->bgm);
	contador = 200;
	temps = 0.0f;
}
int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);

	//vectors
	Menu menu;
	Game level1, level2, level3, level4;
	/*Screen inici, stage1, stage2, stage3, stage4, gameover;*/
	//screens.insert(screens.end(), &inici);
	screens.insert(screens.end(), &menu);
	//screens.insert(screens.end(), &stage1);
	screens.insert(screens.end(), &level1);
	//screens.insert(screens.end(), &stage2);
	screens.insert(screens.end(), &level2);
	////screens.insert(screens.end(), &stage3);
	screens.insert(screens.end(), &level3);
	////screens.insert(screens.end(), &stage4);
	screens.insert(screens.end(), &level4);

#pragma region Declaracio Screens
	/*stage1.Fons = LoadTexture("Sprites/menu/stage1.png");
	stage1.bgm= LoadMusicStream("music/02. Stage Start.mp3");

	stage2.Fons = LoadTexture("Sprites/menu/stage2.png");
	stage2.bgm = LoadMusicStream("music/02. Stage Start.mp3");

	stage3.Fons = LoadTexture("Sprites/menu/stage3.png");
	stage3.bgm = LoadMusicStream("music/02. Stage Start.mp3");

	stage4.Fons = LoadTexture("Sprites/menu/stage4.png");
	stage4.bgm = LoadMusicStream("music/02. Stage Start.mp3");*/
#pragma endregion

	PlayMusicStream(screens[screen]->bgm);

	camera.target.x = screenWidth / 2.0f;
	camera.target.y = screenHeight / 2.0f;
	camera.offset.x = screenWidth / 2.0f;
	camera.offset.y = screenHeight / 2.0f;
	camera.rotation = 0.0f;
	camera.zoom = 3.0f;

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_ENTER) && screen == 0 || screens[screen]->nextLevel() == true) {
			loadNextScreen();
		}
		UpdateMusicStream(screens[screen]->bgm);

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

		screens[screen]->HandleInput();

		BeginDrawing();
		
		if (screen != 0 && screen < 5) {
			ClearBackground(GRAY);
			DrawText(puntuacioText.c_str(), screenWidth - textw1 - 550, 32, 65, BLACK);
			DrawText(vidaText.c_str(), screenWidth - textw2 - 110, 32, 65, BLACK);
			DrawText(contadortext, (screenWidth - textWidth) / 5, screenHeight / 11 - fontSize / 2, fontSize, BLACK);
			DrawText(TIMEText.c_str(), screenWidth - textw4 - 1105, 32, 65, BLACK);
		} else { ClearBackground(BLACK); }
		//INICI CÀMERA (estàtic respecte a la càmera)
		BeginMode2D(camera);
		if (screens[screen]->bomberman.bmanPos.x >= 588 && screens[screen]->bomberman.bmanPos.x <= 652 && screen != 0)
		{
			camera.target = { screens[screen]->bomberman.bmanPos.x + 20, (float)screenHeight / 2 - 20};
		}
		DrawTexture(screens[screen]->Fons, screenWidth / 2 - screens[screen]->Fons.width / 2, screenHeight / 2 - screens[screen]->Fons.height / 2, WHITE);
		for (int j = 0; j < screens[screen]->bomberman.bombs.size(); j++) {
			screens[screen]->bomberman.bombs[j].Draw();
		}
		screens[screen]->Draw();

		//FINAL CÀMERA (estàtic respecte a la pantalla)
		EndMode2D();

		EndDrawing();
	}
	CloseWindow();
	return 0;
}