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
#include <endScreen.h>

using namespace std;

//basics per a funcionar
const int screenWidth = 1280;
const int screenHeight = 720;

int screen = 0;
int auxScreen = screen;
vector <Screen*> screens;

//interficie
int puntuacio = 0;
int vida = 3;
int contador = 5;
int maxBombs = 1;
float temps = 0.0f;
const int fontSize = 65;
bool isRemoteControl = false;

//Càmera
Camera2D camera = { 0 };

vector<Screen*> setUpScreens(int* vida, int* pantalla) {
	vector<Screen*> screenList;
	if (screen == 0 || screen == screens.size()-1) {
		Menu* menu = new Menu();
		screenList.insert(screenList.end(), menu);
	}
	Screen* stage1 = new Screen();
	stage1->Fons = LoadTexture("Sprites/menu/stage1.png");
	stage1->bgm = LoadMusicStream("music/02. Stage Start.mp3");
	screenList.insert(screenList.end(), stage1);

	Screen* stage2 = new Screen();
	stage2->Fons = LoadTexture("Sprites/menu/stage2.png");
	stage2->bgm = LoadMusicStream("music/02. Stage Start.mp3");
	screenList.insert(screenList.end(), stage2);

	Screen* stage3 = new Screen();
	stage3->Fons = LoadTexture("Sprites/menu/stage3.png");
	stage3->bgm = LoadMusicStream("music/02. Stage Start.mp3");
	screenList.insert(screenList.end(), stage3);

	Screen* stage4 = new Screen();
	stage4->Fons = LoadTexture("Sprites/menu/stage4.png");
	stage4->bgm = LoadMusicStream("music/02. Stage Start.mp3");
	screenList.insert(screenList.end(), stage4);

	Screen* gameOver = new Screen();
	gameOver->Fons = LoadTexture("Sprites/menu/gameOver.png");
	gameOver->bgm = LoadMusicStream("music/10. Game Over.mp3");
	gameOver->duration = 419;
	screenList.insert(screenList.end(), gameOver);

	endScreen* endS = new endScreen();
	screenList.insert(screenList.end(), endS);
	endS->duration = 780;
	return screenList;
}
void addGameToScreens(vector<Screen*>& screenList, int levelIndex, int* vida, int* pantalla) {
	int nextIndex = levelIndex + 1;
	unsigned int seed = rand() % 500;
	// Check if the next screen exists and is a Game and delete if so (i don't wwant to have 2 game screens back to back xd
	if (nextIndex < screenList.size()) {
		Game* gamePtr = dynamic_cast<Game*>(screenList[nextIndex]);
		if (gamePtr != nullptr) {
			seed = screenList[nextIndex]->mySeed;
			delete screenList[nextIndex];          
			screenList.erase(screenList.begin() + nextIndex);
		}
	}

	// Create and insert the new Game
	Game* level = new Game(levelIndex + 1, vida, pantalla, &maxBombs, seed, &isRemoteControl, &puntuacio, &contador);
	screenList.insert(screenList.begin() + nextIndex, level);
}

void loadNextScreen() {
	contador = 5;
	StopMusicStream(screens[screen]->bgm);
	if (screen >= 0 && screen!=8 && screen != screens.size()-2) {
		if (screen == 1 || screen == 3 || screen == 5 || screen == 7) {
			if (screen != screens.size() - 1 && screen != screens.size() - 2) {
				addGameToScreens(screens, screen, &vida, &screen);
				screen++;
				screens[screen]->bomberman.resetPlayer();
			}
			else {
				screen = 0;
				puntuacio = 0;
				vida = 3;
				maxBombs = 1;
			}
		}
		else {
			if (screen == screens.size() - 1) {
				screen = 0;
				puntuacio = 0;
				vida = 3;
				maxBombs = 1;
			}
			else {
				screen++;
			}
		}
	}
	else if (screen == 8) {
		screen = screens.size()-1;
	}
	else if (screen == screens.size()-2) {
		screen = 0;
		puntuacio = 0;
		vida = 3;
		maxBombs = 1;
	}
	PlayMusicStream(screens[screen]->bgm);
	contador = 5;
	temps = 0.0f;
}
void screenManagement() {
	if (vida == 0) {
		screen = screens.size() - 2;
		puntuacio = 0;
		vida = 3;
		maxBombs = 1;
		PlayMusicStream(screens[screen]->bgm);
		contador = 200;
		temps = 0.0f;

	}
	if (IsKeyPressed(KEY_ENTER) || screens[screen]->nextLevel() == true) {
		loadNextScreen();
	}
}
int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);

	screens = setUpScreens(&vida, &screen);

	PlayMusicStream(screens[screen]->bgm);

	while (!WindowShouldClose())
	{
		if (screen == 0) {
			camera.target.x = screenWidth / 2.0f;
			camera.target.y = screenHeight / 2.0f;
			camera.offset.x = screenWidth / 2.0f;
			camera.offset.y = screenHeight / 2.0f;
			camera.rotation = 0.0f;
			camera.zoom = 3.0f;
		}
		if (auxScreen != screen) {
			if (vida != 0 && screen != 0 && screen != screens.size()-1) {
				PlayMusicStream(screens[screen]->bgm);
				camera.target.x = 608;
				camera.target.y = screenHeight / 2.0f-20;
				camera.offset.x = screenWidth / 2.0f;
				camera.offset.y = screenHeight / 2.0f;
				camera.rotation = 0.0f;
				camera.zoom = 3.0f;
				isRemoteControl = false;
				screens[screen]->bomberman.resetPlayer();
			}
			else {
				camera.target.x = screenWidth / 2.0f;
				camera.target.y = screenHeight / 2.0f;
				camera.offset.x = screenWidth / 2.0f;
				camera.offset.y = screenHeight / 2.0f;
				camera.rotation = 0.0f;
				camera.zoom = 3.0f;
			}
			auxScreen = screen;
		}
		UpdateMusicStream(screens[screen]->bgm);
		screenManagement();
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
		screens[screen]->Update();

		BeginDrawing();
		
		if (screen != 0 && screen != 1 && screen != 3 && screen != 5 && screen != 7 && screen != screens.size() - 1 && screen != screens.size() - 2) {
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