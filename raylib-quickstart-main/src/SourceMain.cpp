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
	//DrawTexture(BMan, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
	//DrawTextureV(BMan, BManPos, WHITE);





	//CODI OFICIAL FUNCIONAL
	const int screenWidth = 1280;
	const int screenHeight = 800;



	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Music startMusic = LoadMusicStream("music/02. Stage Start.mp3");
	Music bgm = LoadMusicStream("music/03. Main BGM.mp3");
	Music currentMusic = startMusic;
	int music = 0;

	PlayMusicStream(currentMusic);
	float timePlayedMusic = 0.0f;

	Texture Fons = LoadTexture("Sprites/Fons.png");//cal afegir el nom de cada carpeta on esta la imatge
	Texture2D BMan = LoadTexture("Sprites/idle.png");
	BMan = LoadTexture("Sprites/walkFront.png");
	BMan = LoadTexture("Sprites/walkBack.png");
	BMan = LoadTexture("Sprites/walkLeft.png");
	BMan = LoadTexture("Sprites/walkRight.png");
	//BMan = LoadTexture("Sprites/death.png"); //s'hauria de fer un altra textura2D
	Texture Blocs = LoadTexture("Sprites/blocsfons.png"); //son amb el que colisionen
	Texture2D Bomb = LoadTexture("Sprites/bomb.png");

	int animFrames = 0;
	Image imDeadAnim = LoadImageAnim("resources/dead.gif", &animFrames);
	Texture2D texDeadAnim = LoadTextureFromImage(imDeadAnim);

	Vector2 BManPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio bomberman


	//frames animacions base
	int currentFrame = 0;
	int frameContador = 0;
	int frameSpeed = 4; //marca la velocitat dels FPS
	bool dead = false;

	//frames animacio/gif mort
	unsigned int nextFrameDataOffset = 0;

	int currentAnimFrame = 0;
	int frameDelay = 8;
	int frameCounter = 0;

	//blocs:

	Vector2 blocPos = { 400.0f, 200.0f };
	Rectangle blocCollider = { blocPos.x, blocPos.y, (float)Blocs.width, (float)Blocs.height };
	entity bloc = { bloc.texture = Blocs, bloc.position = blocPos, bloc.collider = blocCollider };
	//prova:
	Rectangle frameRec = { 0.0f, 0.0f, (float)BMan.width / 3, (float)BMan.height }; //MIDA DISPLAY FRAME
	//Rectangle deathRec = { 0.0f, 0.0f, (float)BMan.width / 7, (float)BMan.height }; //s'hauria de fer un altra textura amb la seva propia mida
	Rectangle blocks[] =
	{
		{ 200.0f, 150.0f, 100.0f, 50.0f }, // Block 1
		{ 400.0f, 300.0f, 150.0f, 75.0f }, // Block 2
		{ 600.0f, 450.0f, 100.0f, 100.0f }  // Block 3
	};

	int numBlocks = sizeof(blocks) / sizeof(blocks[0]);
	//hola

	//els meus canvis
	Rectangle playerCollider = { BManPos.x, BManPos.y, (float)BMan.width / 3, (float)BMan.height };
	entity player = { player.texture = BMan, player.position = BManPos, player.collider = playerCollider };

	Camera2D camera = { 0 };
	camera.target.x = player.position.x + 20.0f;
	camera.target.y = player.position.y + 20.0f;
	camera.offset.x = screenWidth / 2.0f;
	camera.offset.y = screenHeight / 2.0f;
	camera.rotation = 0.0f;
	camera.zoom = 3.5f;

	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		player.texture = BMan;
		player.position = BManPos;

		/*UpdateMusicStream(currentMusic);*/
		bloc.collider = { bloc.position.x, bloc.position.y };

		//moviment personatge jugador
		bool isCollidingX = false;
		bool isCollidingY = false;

		Vector2 playerVelocity = { 0.0f, 0.0f };

		if (IsKeyUp) { BMan = LoadTexture("Sprites/idle.png"); }//animacio bman quiet

		if (IsKeyPressed(KEY_Z)) { dead = true; }//no va
		if (IsKeyPressed(KEY_X)) { dead = true; }//no va

		if (IsKeyDown(KEY_RIGHT)) { BManPos.x += 1.3f; BMan = LoadTexture("Sprites/walkRight.png"); }
		if (IsKeyDown(KEY_LEFT)) { BManPos.x -= 1.3f; BMan = LoadTexture("Sprites/walkLeft.png"); }
		if (IsKeyDown(KEY_UP)) { BManPos.y -= 1.3f; BMan = LoadTexture("Sprites/walkBack.png"); }
		if (IsKeyDown(KEY_DOWN)) { BManPos.y += 1.3f; BMan = LoadTexture("Sprites/walkFront.png"); }

		player.position = BManPos;


		frameContador++;
		if (frameContador >= (60 / frameSpeed))
		{
			frameContador = 0;
			currentFrame++;

			if (dead = true) {
				//if (currentFrame > 8) currentFrame = 0;

				//deathRec.x = (float)currentFrame * (float)BMan.width / 7; //MIDA DISPLAY FRAME

			}
			if (currentFrame > 5) currentFrame = 0;

			frameRec.x = (float)currentFrame * (float)BMan.width / 3; //MIDA DISPLAY FRAME
		}

		if (dead = true) {
			frameCounter++;
			if (frameCounter >= frameDelay)
			{
				currentAnimFrame++;
				if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

				// Get memory offset position for next frame data in image.data
				nextFrameDataOffset = imDeadAnim.width * imDeadAnim.height * 4 * currentAnimFrame;

				// Update GPU texture data with next frame image data
				// WARNING: Data size (frame size) and pixel format must match already created texture
				UpdateTexture(texDeadAnim, ((unsigned char*)imDeadAnim.data) + nextFrameDataOffset);

				frameCounter = 0;
			}
		}


		//COMEN�A A DIBUIXAR

		BeginDrawing();
		BeginMode2D(camera);

		ClearBackground(RAYWHITE);// Setup the back buffer for drawing (clear color and depth buffers)

		//___TOT EL QUE S'HAGI DE MOSTRAR PER PANTALLA DAVALL D'AIXO___

		if (BManPos.x > 555 && BManPos.x < 685) {
			camera.target = { player.position.x + 20, (float)screenHeight / 2 - 20 };
		}
		// drawing
		for (int i = 0; i < numBlocks; i++)
		{
			DrawRectangleRec(blocks[i], GRAY);
		}
		DrawRectangleLinesEx(player.collider, 2, RED);
		if (isCollidingX || isCollidingY)
		{
			DrawText("Collision Detected!", 350, 10, 20, RED);
		}

		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		DrawTexture(Blocs, screenWidth / 2 - Blocs.width / 2, screenHeight / 2 - Blocs.height / 2, WHITE);

		DrawTextureRec(BMan, frameRec, BManPos, WHITE);

		if (dead = true)
		{
			DrawTexture(texDeadAnim, GetScreenWidth() / 2 - texDeadAnim.width / 2, 140, WHITE);
		}

		Rectangle futureColliderX = player.collider;
		futureColliderX.x += playerVelocity.x;
		for (int i = 0; i < numBlocks; i++) {
			if (CheckCollision(futureColliderX, blocks[i]))
			{
				isCollidingX = true;
				break;
			}
		}

		Rectangle futureColliderY = player.collider;
		futureColliderY.y += playerVelocity.y;
		for (int i = 0; i < numBlocks; i++) {
			if (CheckCollision(futureColliderY, blocks[i]))
			{
				isCollidingY = true;
				break;
			}
		}

		if (!isCollidingX)
		{
			player.position.x += playerVelocity.x;
		}
		if (!isCollidingY)
		{
			player.position.y += playerVelocity.y;
		}

		player.collider = { player.position.x, player.position.y };

		/*timePlayedMusic = GetMusicTimePlayed(currentMusic) / GetMusicTimeLength(currentMusic);*/

		/*if (timePlayedMusic > 1.0f) {
			if (music == 0) {

				StopMusicStream(currentMusic);
				currentMusic = bgm;
				music = 1;

				PlayMusicStream(currentMusic);
			}
			else {
				timePlayedMusic = 1.0f;
			}
		}*/
		EndDrawing();
	}
	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(BMan);
	UnloadTexture(Blocs);
	UnloadTexture(Fons);
	/*UnloadMusicStream(currentMusic);
	UnloadMusicStream(startMusic);
	UnloadMusicStream(bgm);*/

	CloseAudioDevice();

	UnloadTexture(texDeadAnim);   // Unload texture
	UnloadImage(imDeadAnim);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}