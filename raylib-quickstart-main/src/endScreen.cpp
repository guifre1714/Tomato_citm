#include<endScreen.h>
#include <vector>
#include <string>
#include <game.h>
#include "raylib.h"
using namespace std;

endScreen::endScreen() {
	bombHuman = LoadTexture("Sprites/bomberman/walkRight.png");
	Fons = LoadTexture("Sprites/menu/bombermanEndScreen.png");
	bgm = LoadMusicStream("music/08. Ending.mp3");
	
	humanPos.x = 430;
	humanPos.y = 416;

	frameRec = { 0.0f, 0.0f, 16.0f, 16.0f };
	currentFrame = 0;
	frameContador = 0;
	frameSpeed = 6; //marca la velocitat dels FPS
	totalFrames = 3;
	ampladaFrames = 16;
	
}

endScreen:: ~endScreen() {

}

void endScreen::Draw() {
	//Animation loop.
	frameContador++;
	if (frameContador >= (60 / frameSpeed)) {
		frameContador = 0;
		currentFrame++;

		if (currentFrame > totalFrames - 1) {
		
			currentFrame = 0;
		}
		frameRec.x = (float)currentFrame * ampladaFrames;
	}
	if (humanPos.x >= 627) {
		bombHuman = LoadTexture("Sprites/assets/endBman.png");		
	}
	DrawTextureRec(bombHuman, frameRec, humanPos, WHITE);
	
	//Draws two black rectangles in front of the human to simulate the effect of the original game
	DrawRectangle(420, 416, 92, 16, BLACK);
	DrawRectangle(768, 416, 100, 16, BLACK);
}

void endScreen::HandleInput() {
	humanPos.x += 0.5;
	if (timer > duration) {//When the sequence ends resets the player so that if you win again it plays accordingly.
		bombHuman = LoadTexture("Sprites/bomberman/walkRight.png");
		humanPos.x = 430;
		humanPos.y = 416;
	}
}

void endScreen::Update() {

}
