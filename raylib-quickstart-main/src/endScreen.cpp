#include<endScreen.h>
#include <vector>
#include <string>
#include <game.h>
#include "raylib.h"
using namespace std;

endScreen::endScreen() {
	bombHuman = LoadTexture("Sprites/assets/endBman.png");
	Fons = LoadTexture("Sprites/menu/bombermanEndScreen.png");
	bgm = LoadMusicStream("music/08. Ending.mp3");
	
	humanPos.x = 409;
	humanPos.y = 272;

	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 4; //marca la velocitat dels FPS
	totalFrames = 3;
	ampladaFrames = 16;
}

endScreen:: ~endScreen() {

}

void endScreen::Draw() {
	frameContador++;
	if (frameContador >= (60 / frameSpeed)) {
		frameContador = 0;
		currentFrame++;

		if (currentFrame > totalFrames - 1) {
		
			currentFrame = 0;
		}
		frameRec.x = (float)currentFrame * ampladaFrames;
	}
	DrawTextureRec(bombHuman, frameRec, humanPos, WHITE);
}

void endScreen::HandleInput() {


}

void endScreen::Update() {

}
