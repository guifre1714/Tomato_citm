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

//Basic vars
const int screenWidth = 1280;
const int screenHeight = 720;

int screen = 0; //Current screen
int auxScreen = screen; //Auxiliar var to detect when the screen changes
vector <Screen*> screens; //Vector of all the screens in the game

//UI vars
int puntuacio = 0;
int vida = 3;
int contador = 200;
const int fontSize = 65;
float temps = 0.0f;

//Vars shared between screens
int maxBombs = 1;
bool isRemoteControl = false;

//Camera
Camera2D camera = { 0 };

//Function that creates the base screens: Group members, Menu, "Stage", Game Over & Victory, and adds them to a vector of Screen*.
vector<Screen*> setUpScreens(int* vida, int* pantalla) {
	vector<Screen*> screenList;

	Screen* inici = new Screen();
	inici->bgm = LoadMusicStream("music/00. Kokiri Forest.mp3");
	inici->duration = 3600;
	screenList.insert(screenList.end(), inici);

	Menu* menu = new Menu();
	screenList.insert(screenList.end(), menu);

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
//Function that adds a "Game" screen to the position next to the current screen in the screens vector.
void addGameToScreens(vector<Screen*>& screenList, int levelIndex, int* vida, int* pantalla) {
	int nextIndex = levelIndex + 1;
	unsigned int seed = rand() % 130; //Seed that gives a set of screens we like
	// Check if the next screen exists and is a Game and delete if so (i don't wwant to have 2 game screens back to back xd)
	if (nextIndex < screenList.size()) {
		Game* gamePtr = dynamic_cast<Game*>(screenList[nextIndex]);
		if (gamePtr != nullptr) {
			seed = screenList[nextIndex]->mySeed;
			delete screenList[nextIndex];          
			screenList.erase(screenList.begin() + nextIndex);
		}
	}

	// Create and insert the new Game into the passed vector
	Game* level = new Game(levelIndex + 1, vida, pantalla, &maxBombs, seed, &isRemoteControl, &puntuacio, &contador);
	screenList.insert(screenList.begin() + nextIndex, level);
}
//Function that loads the next screen in the Screens vector and sets the camera and player variables to the ones needed.
void loadNextScreen() {
	contador = 200;
	StopMusicStream(screens[screen]->bgm);
	if (screen == screens.size() - 2) { //If the screen from which the function is called, loads the menu back again and resets all player variables.
		screen = 1;
		puntuacio = 0;
		vida = 3;
		maxBombs = 1;
	} else if (screen >= 0 && screen!=9 && screen != screens.size()-2) {//If the screen isn't the menu, stage 4 or game over:
		if (screen % 2 == 0 && screen != 0) {//If  screen is divisible by 0 (meaning the current screen it isn't a Game (level) screen:
			if (screen != screens.size() - 1 && screen != screens.size() - 2) {//If the screen isn't the victory screen nor the game over screen:
				addGameToScreens(screens, screen, &vida, &screen);//Creates a Game screen, loads it and resets the player's position and variables (except for the shared ones declared previously).
				screen++;
				screens[screen]->bomberman.resetPlayer();
			}
			else {//If the current screen is the victory screen or the game over screen, loads the menu and resets the shared variables.
				screen = 1;
				puntuacio = 0;
				vida = 3;
				maxBombs = 1;
			}
		}
		else {//Additional check because in some cases the game over screen can be located in a position non divisible by 2.
			if (screen == screens.size() - 1) {
				screen = 1;
				puntuacio = 0;
				vida = 3;
				maxBombs = 1;
			}
			else {
				screen++;
			}
		}
	} else if (screen == 9) {//If the current screen is the last level and this function is called (meaning you won), skips the penultimate screen in the Screens vector and loads the last one (Victory screen).
		screen = screens.size()-1;
	}
	//Regardless of the screen, it has to reset the music (bgm) and the timer.
	PlayMusicStream(screens[screen]->bgm);
	contador = 200;
	temps = 0.0f;
}
void screenManagement() {
	if (vida == 0) {//If life == 0, load the GameOver screen.
		screen = screens.size() - 2;
		puntuacio = 0;
		vida = 3;
		maxBombs = 1;
		PlayMusicStream(screens[screen]->bgm);
		contador = 200;
		temps = 0.0f;

	}
	//DEBUG: Press the ENTER key to load the next scene.
	if (IsKeyPressed(KEY_ENTER)) {
		loadNextScreen();
	}
	/*Here is a somewhat tricky bit :
	We wanted certain screens, as the stage screens, the group screen, the game over screen and the victory screen to jump to the next one
	automatically after a certain time has passed, so we did the next:
	*/
	if (screens[screen]->nextLevel() == true) {//If the conditions to go into the next level are met:
		if (screens[screen]->timer > screens[screen]->duration) {//If the timer has surpassed the duration of the scene:
			screens[screen]->timer = 0;//Resets the timer (so that if you go back to that screen it starts all over again).
			loadNextScreen();//Loads the next screen.
		}
		else if(screens[screen]->timer == -1){/*If the screen timer is set to - 1 freezes the movement and starts the timer by setting it to 0.
			This was made to recreate the effect of the original of the game stopping and playing the tune when you beat a level.*/
			StopMusicStream(screens[screen]->bgm);
			screens[screen]->bgm = LoadMusicStream("music/05. Stage Clear.mp3");
			PlayMusicStream(screens[screen]->bgm);
			screens[screen]->freeze = true;
			screens[screen]->bomberman.bmanTXT = LoadTexture("Sprites/bomberman/idle.png");
			screens[screen]->timer = 0;
		}
		if (screens[screen]->timer >= 0){//Runs the timer
			screens[screen]->timer++;
		}
	}
}
int main()
{
	//Initializes the game
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");
	SetTargetFPS(60);

	screens = setUpScreens(&vida, &screen);//Creates the initial screens

	PlayMusicStream(screens[screen]->bgm);//Plays the bgm associated to the current screen

	while (!WindowShouldClose())
	{
		if (auxScreen != screen) {//If the screen has changed without the LoadNextScreen function being called:
			if (vida != 0 && screen != 1 && screen != screens.size()-1) {//If the player is alive and the screen isn't the victory screen:
				//Resets the level
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
			else {//Else it loads the menu camera configuration
				camera.target.x = screenWidth / 2.0f;
				camera.target.y = screenHeight / 2.0f;
				camera.offset.x = screenWidth / 2.0f;
				camera.offset.y = screenHeight / 2.0f;
				camera.rotation = 0.0f;
				camera.zoom = 3.0f;
			}
			auxScreen = screen;//Sets the auxiliar var to be the same as screen again.
		}
		//DEBUG: END TIME
		if (IsKeyPressed(KEY_T)) {
			contador = 0;
		}
		UpdateMusicStream(screens[screen]->bgm);
		screenManagement();
		//UI
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
		//END UI

		//INITIAL SCREEN TEXT
		string degree = "Project 1\t\tVideo Game Design and Development\t\tCITM UPC";
		string team = "Elena Ibanez, Marcel Pascual, Marc Port";
		string tutor = "Alejandro Paris Gomez";
		string other="github.com/guifre1714/Tomato_citm";
	
		screens[screen]->HandleInput();//Calls the HandleInput function of the current screen.
		screens[screen]->Update();//Calls the Update function of the current screen.

		BeginDrawing();

		if (screen == 0) {//If the screen is the first one, draw the according text.
			DrawText(degree.c_str(), 200, 100, 30, WHITE);
			DrawText(team.c_str(), 240, 250, 40, WHITE);
			DrawText(tutor.c_str(), 450, 400, 30, WHITE);
			DrawText(other.c_str(), 350, 450, 30, WHITE);
		}
		//If the screen is a Game, draw the UI. Else, make the background black.
		if (screen != 0 && screen != 1 && screen != 2 && screen != 4 && screen != 6 && screen != 8 && screen != screens.size() - 1 && screen != screens.size() - 2) {
			ClearBackground(GRAY);
			DrawText(puntuacioText.c_str(), screenWidth - textw1 - 550, 32, 65, BLACK);
			DrawText(vidaText.c_str(), screenWidth - textw2 - 110, 32, 65, BLACK);
			DrawText(contadortext, (screenWidth - textWidth) / 5, screenHeight / 11 - fontSize / 2, fontSize, BLACK);
			DrawText(TIMEText.c_str(), screenWidth - textw4 - 1105, 32, 65, BLACK);
		} else { ClearBackground(BLACK); }
		BeginMode2D(camera);//Initializes the camera
		//Makes the camera follow the player and stay in boundaries
		if (screens[screen]->bomberman.bmanPos.x >= 588 && screens[screen]->bomberman.bmanPos.x <= 652 && screen != 0)
		{
			camera.target = { screens[screen]->bomberman.bmanPos.x + 20, (float)screenHeight / 2 - 20};
		}
		//Draw whichever texture is assigned to the background of the current screen.
		DrawTexture(screens[screen]->Fons, screenWidth / 2 - screens[screen]->Fons.width / 2, screenHeight / 2 - screens[screen]->Fons.height / 2, WHITE);
		screens[screen]->Draw();//Calls the draw function of the current screen.

		EndMode2D();//Ends camera mode

		EndDrawing();
	}
	CloseWindow();
	return 0;
}