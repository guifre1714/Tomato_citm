/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h" // utility header for SearchAndSetResourceDir

class entity
{
public:
	Texture texture;
	Vector2 position;
	Rectangle collider;
};




bool CheckCollision(Rectangle rec1, Rectangle rec2)
{
	return (rec1.x < rec2.x + rec2.width &&
		rec1.x + rec1.width > rec2.x &&
		rec1.y < rec2.y + rec2.height &&
		rec1.y + rec1.height > rec2.y);
}

int main()
{
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
	Texture BlocDalt = LoadTexture("Sprites/blocDaltbaix.png"); //son amb el que colisionen
	Texture BlocLateral = LoadTexture("Sprites/blocsLateral.png");
	Texture2D Bomb = LoadTexture("Sprites/singleBomb.png");

	Texture2D globustxt = LoadTexture("Sprites/altg.png");

	int animFrames = 0;
	Image imDeadAnim = LoadImageAnim("resources/dead.gif", &animFrames);
	Texture2D texDeadAnim = LoadTextureFromImage(imDeadAnim);

	Vector2 BManPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio bomberman
	Vector2 globusPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio enemic globus

	//JO. MARCEL, MEU
	Vector2 bombPos = { -1.0f, -1.0f };

	//frames animacions base BOMBERMAN
	int currentFrameB = 0;
	int frameContadorB = 0;
	int frameSpeedB = 4; //marca la velocitat dels FPS
	bool dead = false;

	//framws animacions ENEMICS
	int currentFrameE = 0;
	int frameContadorE = 0;
	int frameSpeedE = 4; //marca la velocitat dels FPS
	//bool dead = false;

	//frames animacio/gif mort
	unsigned int nextFrameDataOffset = 0;

	int currentAnimFrame = 0;
	int frameDelay = 8;
	int frameCounter = 0;

	
	//BOMBERMAN:
	Rectangle frameRecB = { 0.0f, 0.0f, (float)BMan.width / 3, (float)BMan.height }; //MIDA DISPLAY FRAME
	//Rectangle deathRec = { 0.0f, 0.0f, (float)BMan.width / 7, (float)BMan.height }; //s'hauria de fer un altra textura amb la seva propia mida
	Vector2 characterPos = { 100.0f, 100.0f };
	float characterSpeed = 5.0f;
	Vector2 characterSize = { 50.0f, 50.0f };
	
	//ENEMICS:
	Rectangle frameRecE = { 0.0f, 0.0f, (float)globustxt.width / 6, (float)globustxt.height }; //MIDA DISPLAY FRAME

	//BOMBA:
	Rectangle frameRecBomb = { 0.0f, 0.0f, (float)Bomb.width / 3, (float)Bomb.height };
	
	
	//BLOCS:
	Vector2 wallSize = { (float)BlocLateral.width, (float)BlocLateral.height };
	Vector2 blocPos = { 400.0f, 300.0f };
	Rectangle blocCollider = { blocPos.x, blocPos.y, (float)BlocDalt.width, (float)BlocDalt.height };
	entity bloc = { bloc.texture = BlocDalt, bloc.position = blocPos, bloc.collider = blocCollider };

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

	entity globus = { globus.texture = globustxt, globus.position = globusPos };

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
		//MARCEL
		/*if (IsKeyPressed(KEY_C)) 
		{
			bombPos = BManPos;
		}*/

		Vector2 nextPos = characterPos;

		Rectangle characterRect = { nextPos.x, nextPos.y, characterSize.x, characterSize.y };
		Rectangle wallRect = { blocPos.x, blocPos.y, blocPos.x, blocPos.y };

		if (!CheckCollisionRecs(characterRect, wallRect)) 
		{
			characterPos = nextPos;
		}

		player.texture = BMan;
		player.position = BManPos;

		globus.position = globusPos;
		globus.texture = globustxt;

		/*UpdateMusicStream(currentMusic);*/
		bloc.collider = { bloc.position.x, bloc.position.y };

		//moviment personatge jugador
		bool isCollidingX = false;
		bool isCollidingY = false;

		bool actBomb = false;

		Vector2 playerVelocity = { 0.0f, 0.0f };

		if (IsKeyUp) { BMan = LoadTexture("Sprites/idle.png"); }//animacio bman quiet

		//if (IsKeyPressed(KEY_Z)) { dead = true; }//no va
		//if (IsKeyPressed(KEY_X)) { dead = true; }//no va

		if (IsKeyDown(KEY_RIGHT)) { BManPos.x += 1.3f; BMan = LoadTexture("Sprites/walkRight.png"); }
		if (IsKeyDown(KEY_LEFT)) { BManPos.x -= 1.3f; BMan = LoadTexture("Sprites/walkLeft.png"); }
		if (IsKeyDown(KEY_UP)) { BManPos.y -= 1.3f; BMan = LoadTexture("Sprites/walkBack.png"); }
		if (IsKeyDown(KEY_DOWN)) { BManPos.y += 1.3f; BMan = LoadTexture("Sprites/walkFront.png"); }

		if (IsKeyDown(KEY_Z) && !actBomb) 
		{
			actBomb = true;

		}

		//ANIMACIO BOMBERMAN
		frameContadorB++;
		if (frameContadorB >= (60 / frameSpeedB))
		{
			frameContadorB = 0;
			currentFrameB++;

			if (dead = true) {
				//if (currentFrame > 8) currentFrame = 0;

				//deathRec.x = (float)currentFrame * (float)BMan.width / 7; //MIDA DISPLAY FRAME

			}
			if (currentFrameB > 5) currentFrameB = 0;

			frameRecB.x = (float)currentFrameB * (float)BMan.width / 3; //MIDA DISPLAY FRAME
		}


		//ANIMACIO ENEMIC GLOBUS
		frameContadorE++;
		if (frameContadorE >= (60 / frameSpeedE))
		{
			frameContadorE = 0;
			currentFrameE++;

			
			if (currentFrameE > 5) currentFrameE = 0;

			frameRecE.x = (float)currentFrameE * (float)globustxt.width / 6; //MIDA DISPLAY FRAME
		}

		//if (dead = true) 
		// {
		//	frameCounter++;
		//	if (frameCounter >= frameDelay)
		//	{
		//		currentAnimFrame++;
		//		if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

		//		// Get memory offset position for next frame data in image.data
		//		nextFrameDataOffset = imDeadAnim.width * imDeadAnim.height * 4 * currentAnimFrame;

		//		// Update GPU texture data with next frame image data
		//		// WARNING: Data size (frame size) and pixel format must match already created texture
		//		UpdateTexture(texDeadAnim, ((unsigned char*)imDeadAnim.data) + nextFrameDataOffset);

		//		frameCounter = 0;
		//	}
		//}


		//COMENCA A DIBUIXAR

		BeginDrawing();
		BeginMode2D(camera);

		ClearBackground(RAYWHITE);// Setup the back buffer for drawing (clear color and depth buffers)

		//___TOT EL QUE S'HAGI DE MOSTRAR PER PANTALLA DAVALL D'AIXO___

		if (actBomb=true) DrawTextureRec(Bomb, frameRecBomb, BManPos, WHITE);

		/*if (bombPos.x != -1.0f && bombPos.y != -1.0f) 
		{

			printf("Drawing bomb at position: (%f, %f)\n", bombPos.x, bombPos.y);
			DrawTexture(Bomb, bombPos.x - Bomb.width / 2, bombPos.y - Bomb.height / 2);  
		}
			DrawTexture(Bomb, bombPos.x - Bomb.width / 2, bombPos.y - Bomb.height / 2, WHITE);  
		}*/

		/*if (IsKeyPressed(KEY_C))
		{
			bombPos = BManPos;
			DrawTexture(Bomb, bombPos, WHITE);
		}*/


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

		//DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		DrawTexture(BlocDalt, screenWidth / 2 - BlocDalt.width / 2, screenHeight / 2 - (BlocDalt.height*6.5), WHITE);
		DrawTexture(BlocDalt, screenWidth / 2 - BlocDalt.width / 2, screenHeight / 2 + (BlocDalt.height*5.5), WHITE);

		DrawTexture(BlocLateral, screenWidth / 2 - (BlocLateral.width *15.5), screenHeight / 2 - BlocLateral.height/2, WHITE);
		DrawTexture(BlocLateral, screenWidth / 2 + (BlocLateral.width * 14.5), screenHeight / 2 - BlocLateral.height / 2, WHITE);



		DrawTextureRec(BMan, frameRecB, BManPos, WHITE);

		DrawTextureRec(globustxt, frameRecB, globusPos, WHITE);

		/*if (dead = true)
		{
			DrawTexture(texDeadAnim, GetScreenWidth() / 2 - texDeadAnim.width / 2, 140, WHITE);
		}*/

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

		DrawRectangleV(characterPos, characterSize, BLUE);

		DrawTexture(BlocLateral, blocPos.x - BlocLateral.width / 2, blocPos.y - BlocLateral.height / 2, WHITE);

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
	UnloadTexture(BlocDalt);
	UnloadTexture(Fons);
	UnloadTexture(BlocLateral);
	/*UnloadMusicStream(currentMusic);
	UnloadMusicStream(startMusic);
	UnloadMusicStream(bgm);*/

	CloseAudioDevice();

	UnloadTexture(texDeadAnim);   // Unload texture
	UnloadImage(imDeadAnim);
	UnloadTexture(Bomb);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}