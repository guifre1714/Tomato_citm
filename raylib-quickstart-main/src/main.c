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

bool CheckCollision(Rectangle rec1, Rectangle rec2) 
{
	return (rec1.x < rec2.x + rec2.width &&
		rec1.x + rec1.width > rec2.x &&
		rec1.y < rec2.y + rec2.height &&
		rec1.y + rec1.height > rec2.y);
}

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
	Texture2D BMan = LoadTexture("Sprites/walkf1.png");
	Texture Blocs = LoadTexture("Sprites/blocsfons.png"); //són amb el que colisionen

	Vector2 BManPos = { (float)screenWidth / 2, (float)screenHeight / 2 };

	//blocs:

	Vector2 blocPos = { 400.0f, 200.0f };
	Rectangle blocCollider = { blocPos.x, blocPos.y, (float)Blocs.width, (float)Blocs.height };
	entity bloc = { .texture = Blocs, .position = blocPos, .collider = blocCollider };


	//els meus canvis
	Rectangle playerCollider = { BManPos.x, BManPos.y, (float)BMan.width, (float)BMan.height };
	entity player = { .texture = BMan, .position = BManPos, .collider = playerCollider };

	Camera2D camera = { 0 };
	camera.target = (Vector2){ player.position.x + 20.0f, player.position.y + 20.0f };
	camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 5.0f;

	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		bloc.collider.x = bloc.position.x;
		bloc.collider.y = bloc.position.y;

		if (IsKeyDown(KEY_RIGHT)) BManPos.x += 2.0f;
		if (IsKeyDown(KEY_LEFT)) BManPos.x -= 2.0f;
		if (IsKeyDown(KEY_UP)) BManPos.y -= 2.0f;
		if (IsKeyDown(KEY_DOWN)) BManPos.y += 2.0f;
		player.position = BManPos;
		camera.target = (Vector2){ player.position.x + 20, player.position.y + 20 };
		// drawing
		BeginDrawing();
		BeginMode2D(camera);
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(RAYWHITE);

		// draw our texture to the screen
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		//DrawTexture(BMan, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		DrawTextureV(BMan, BManPos, WHITE);

		bool isColliding = CheckCollision(player.collider, bloc.collider);

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