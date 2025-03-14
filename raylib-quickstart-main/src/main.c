/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h" // utility header for SearchAndSetResourceDir

typedef struct entity {
	Texture texture;
	Vector2 position;
	Rectangle collider;
} entity;
int main()
{
	//BASURERO DE CODI
	// 
	// draw some text using the default font
	//DrawText("Jajaja aixo es una pestanya normal", 200, 200, 20, WHITE);






	//CODI OFICIAL FUNCIONAL
	const int screenWidth = 1280;
	const int screenHeight = 800;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Bomberman Test");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	
	Texture Fons = LoadTexture("Sprites/Fons.png");//cal afegir el nom de cada carpeta on esta la imatge
	Texture BMan = LoadTexture("Sprites/bomberman.png");

	Vector2 BManPos = { (float)screenWidth / 2, (float)screenHeight / 2 };

	entity player = { .texture = BMan,  .position = BManPos, .collider = {};
	
	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		if (IsKeyDown(KEY_RIGHT)) BManPos.x += 2.0f;
		if (IsKeyDown(KEY_LEFT)) BManPos.x -= 2.0f;
		if (IsKeyDown(KEY_UP)) BManPos.y -= 2.0f;
		if (IsKeyDown(KEY_DOWN)) BManPos.y += 2.0f;

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(RAYWHITE);

		// draw our texture to the screen
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		//DrawTexture(BMan, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		DrawTextureV(BMan, BManPos, WHITE);

		// end the frame and get ready for the next one (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(Fons);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}