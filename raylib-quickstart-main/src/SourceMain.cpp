/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include <vector>
#include <iostream>

#include "resource_dir.h" // utility header for SearchAndSetResourceDir

class Bloc {
public:
	Vector2 BlocPos;
	float width, height;

	Bloc() {};
	Bloc(float x, float y, float width = 40, float height = 40)
	{
		this->BlocPos = { x,y };
		this->width = width;
		this->height = height;
	}

	Rectangle getRect() const {
		return { BlocPos.x, BlocPos.y, width, height };
	}

	void draw() const {
		DrawRectangleRec(getRect(), DARKGRAY);
	}
};

class Player {
public:
	Vector2 BManPos;
	float width, height;
	float speed = 1.3f;
	Texture2D BManText;

	//frames animacions base BOMBERMAN
	int currentFrameB = 0;
	int frameContadorB = 0;
	int frameSpeedB = 4; //marca la velocitat dels FPS
	bool dead = false;

	Player() {};
	Player(float x, float y, Texture2D BManTexture)
	{	
		this->BManPos = { x,y };
		this->BManText = BManTexture;
	}

	Rectangle getRect() const {
		return { BManPos.x, BManPos.y, width, height };
	}

	Rectangle frameRecB = { 0.0f, 0.0f, (float)BManText.width / 3, (float)BManText.height }; //MIDA DISPLAY FRAME

	void animacio() {
		//ANIMACIO BOMBERMAN
		frameContadorB++;
		if (frameContadorB >= (60 / frameSpeedB))
		{
			frameContadorB = 0;
			currentFrameB++;

			//if (dead = true) {
			//	//if (currentFrame > 8) currentFrame = 0;

			//	//deathRec.x = (float)currentFrame * (float)BMan.width / 7; //MIDA DISPLAY FRAME

			//}
			if (currentFrameB > 5) currentFrameB = 0;

			frameRecB.x = (float)currentFrameB * (float)BManText.width / 3; //MIDA DISPLAY FRAME
		}
	}

	void draw() const {
		DrawTextureRec(BManText, frameRecB, BManPos, WHITE);
	}

	void moveAndCollide(const std::vector<Bloc>& blocs) {
		// Guardem la posició anterior
		Vector2 oldPos = BManPos;

		// Moviment
		if (IsKeyUp) { BManText = LoadTexture("Sprites/idle.png"); }//animacio bman quiet

		if (IsKeyDown(KEY_RIGHT)) { BManPos.x += speed; BManText = LoadTexture("Sprites/walkRight.png"); }
		if (IsKeyDown(KEY_LEFT)) { BManPos.x -= speed; BManText = LoadTexture("Sprites/walkLeft.png"); }
		if (IsKeyDown(KEY_UP)) { BManPos.y -= speed; BManText = LoadTexture("Sprites/walkBack.png"); }
		if (IsKeyDown(KEY_DOWN)) { BManPos.y += speed; BManText = LoadTexture("Sprites/walkFront.png"); }


		// Comprovem col·lisió amb blocs
		for (const Bloc& bloc : blocs) {
			if (CheckCollisionRecs(getRect(), bloc.getRect())) {
				// Si hi ha col·lisió, retornem a la posició anterior
				BManPos = oldPos;
				break;
			}
		}
	}
};

class Enemy {
public:
	Vector2 globusPos;
	float width = 40, height = 40;
	float speed = 1.3f;
	Texture2D globustxt;

	//frames animacions ENEMICS
	int currentFrameE = 0;
	int frameContadorE = 0;
	int frameSpeedE = 4; //marca la velocitat dels FPS
	//bool dead = false;

	Enemy() {};
	Enemy(float x, float y, Texture2D globustxt)
	{
		this->globusPos = { x,y };
		this->globustxt = globustxt;
	}

	Rectangle getRect() const {
		return { globusPos.x, globusPos.y, width, height };
	}

	Rectangle frameRecE = { 0.0f, 0.0f, (float)globustxt.width / 3, (float)globustxt.height }; //MIDA DISPLAY FRAME

	void animacio() {
		
	}

	void draw() const {
		DrawTextureRec(globustxt, frameRecE, globusPos, WHITE);
	}

	void moveAndCollide(const std::vector<Bloc>& blocs) {
		// Guardem la posició anterior
		Vector2 oldPos = globusPos;

		// Moviment

		// Comprovem col·lisió amb blocs
		for (const Bloc& bloc : blocs) {
			if (CheckCollisionRecs(getRect(), bloc.getRect())) {
				// Si hi ha col·lisió, retornem a la posició anterior
				globusPos = oldPos;
				break;
			}
		}
	}
};


int main()
{
	//basics per a funcionar
	const int screenWidth = 1280;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Bomberman Test");
	InitAudioDevice();

	SearchAndSetResourceDir("resources");

	//creacio classes
	Player bomberman;
	Bloc blocs;
	Enemy globus;


	//carregar textures
	Texture Fons = LoadTexture("Sprites/Fons.png");//cal afegir el nom de cada carpeta on esta la imatge
	
	Texture2D BMan = LoadTexture("Sprites/idle.png");
	BMan = LoadTexture("Sprites/walkFront.png");
	BMan = LoadTexture("Sprites/walkBack.png");
	BMan = LoadTexture("Sprites/walkLeft.png");
	BMan = LoadTexture("Sprites/walkRight.png");
	//BMan = LoadTexture("Sprites/death.png"); //s'hauria de fer un altra textura2D
	
	Texture BlocDalt = LoadTexture("Sprites/blocDaltbaix.png"); //son amb el que colisionen
	Texture BlocLateral = LoadTexture("Sprites/blocsLateral.png");
	Texture2D Bomb = LoadTexture("Sprites/bomb.png");
	Texture BlocSol = LoadTexture("Sprites/blocIndividual.png");

	Texture2D globustxt = LoadTexture("Sprites/altg.png");


	//vectors moviment
	Vector2 BManPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio bomberman
	Vector2 globusPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio enemic globus


	//animacions
	

	//moviment i display
	
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


	//camara
	Camera2D camera = { 0 };
	camera.target.x = bomberman.BManPos.x + 20.0f;
	camera.target.y = bomberman.BManPos.y + 20.0f;

	/*camera.target.x = BManPos.x + 20.0f;
	camera.target.y = BManPos.y + 20.0f;*/
	camera.offset.x = screenWidth / 2.0f;
	camera.offset.y = screenHeight / 2.0f;
	camera.rotation = 0.0f;
	camera.zoom = 3.5f;

	SetTargetFPS(60);



	//GAME LOOP
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{


		//ns que es aixo
		Vector2 nextPos = characterPos;
		Rectangle characterRect = { nextPos.x, nextPos.y, characterSize.x, characterSize.y };


		//assignar totes les variables a les classes
		bomberman.BManText = BMan;
		bomberman.BManPos = BManPos;

		globus.globusPos = globusPos;
		globus.globustxt = globustxt;


		BeginDrawing();
		BeginMode2D(camera);

		ClearBackground(RAYWHITE);

		// drawing
		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
		DrawTexture(BlocDalt, screenWidth / 2 - BlocDalt.width / 2, screenHeight / 2 - (BlocDalt.height * 6.5), WHITE);
		DrawTexture(BlocDalt, screenWidth / 2 - BlocDalt.width / 2, screenHeight / 2 + (BlocDalt.height * 5.5), WHITE);

		DrawTexture(BlocLateral, screenWidth / 2 - (BlocLateral.width * 15.5), screenHeight / 2 - BlocLateral.height / 2, WHITE);
		DrawTexture(BlocLateral, screenWidth / 2 + (BlocLateral.width * 14.5), screenHeight / 2 - BlocLateral.height / 2, WHITE);


		/*bomberman.draw();*/
		DrawTextureRec(BMan, frameRecB, BManPos, WHITE);

		/*globus.draw();*/
		DrawTextureRec(globustxt, frameRecB, globusPos, WHITE);

		DrawRectangleV(characterPos, characterSize, BLUE);
		EndDrawing();
	}

	// unload textures per a netejar
	UnloadTexture(BMan);
	UnloadTexture(BlocDalt);
	UnloadTexture(Fons);
	UnloadTexture(BlocLateral);

	CloseWindow();
	return 0;
}



////class Bloc {
//public:
//    Vector2 pos;
//    float width, height;
//
//    Bloc(float x, float y, float width = 40, float height = 40)
//        : pos{ x, y }, width(width), height(height) {}
//
//    Rectangle getRect() const {
//        return { pos.x, pos.y, width, height };
//    }
//
//    void draw() const {
//        DrawRectangleRec(getRect(), DARKGRAY);
//    }
//};
//
//class Player {
//public:
//    Vector2 pos;
//    float width = 40, height = 40;
//    float speed = 4.0f;
//
//    Player(float x, float y)
//        : pos{ x, y } {}
//
//    Rectangle getRect() const {
//        return { pos.x, pos.y, width, height };
//    }
//
//    void draw() const {
//        DrawRectangleRec(getRect(), BLUE);
//    }
//
//    void moveAndCollide(const std::vector<Bloc>& blocs) {
//        // Guardem la posició anterior
//        Vector2 oldPos = pos;
//
//        // Moviment
//        if (IsKeyDown(KEY_RIGHT)) pos.x += speed;
//        if (IsKeyDown(KEY_LEFT)) pos.x -= speed;
//        if (IsKeyDown(KEY_DOWN)) pos.y += speed;
//        if (IsKeyDown(KEY_UP)) pos.y -= speed;
//
//        // Comprovem col·lisió amb blocs
//        for (const Bloc& bloc : blocs) {
//            if (CheckCollisionRecs(getRect(), bloc.getRect())) {
//                // Si hi ha col·lisió, retornem a la posició anterior
//                pos = oldPos;
//                break;
//            }
//        }
//    }
//};
//int main() {
//	const int screenWidth = 800;
//	const int screenHeight = 600;
//
//	InitWindow(screenWidth, screenHeight, "Player amb Vector2 i col·lisions");
//
//	Player player(100, 100);
//
//	std::vector<Bloc> blocs = {
//		Bloc(300, 200),
//		Bloc(400, 200),
//		Bloc(500, 300),
//		Bloc(200, 400)
//	};
//
//	SetTargetFPS(60);
//
//	while (!WindowShouldClose()) {
//		player.moveAndCollide(blocs);
//
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		player.draw();
//
//		for (const Bloc& bloc : blocs) {
//			bloc.draw();
//		}
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//
//	return 0;
//}



//int main()
//{
//	//CODI OFICIAL FUNCIONAL
//	const int screenWidth = 1280;
//	const int screenHeight = 800;
//
//
//	// Tell the window to use vsync and work on high DPI displays
//	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
//
//	// Create the window and OpenGL context
//	InitWindow(screenWidth, screenHeight, "Bomberman Test");
//	InitAudioDevice();
//
//	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
//	SearchAndSetResourceDir("resources");
//
//	// Load a texture from the resources directory
//	Music startMusic = LoadMusicStream("music/02. Stage Start.mp3");
//	Music bgm = LoadMusicStream("music/03. Main BGM.mp3");
//	Music currentMusic = startMusic;
//	int music = 0;
//
//	PlayMusicStream(currentMusic);
//	float timePlayedMusic = 0.0f;
//
//	Texture Fons = LoadTexture("Sprites/Fons.png");//cal afegir el nom de cada carpeta on esta la imatge
//	Texture2D BMan = LoadTexture("Sprites/idle.png");
//	BMan = LoadTexture("Sprites/walkFront.png");
//	BMan = LoadTexture("Sprites/walkBack.png");
//	BMan = LoadTexture("Sprites/walkLeft.png");
//	BMan = LoadTexture("Sprites/walkRight.png");
//	//BMan = LoadTexture("Sprites/death.png"); //s'hauria de fer un altra textura2D
//	Texture BlocDalt = LoadTexture("Sprites/blocDaltbaix.png"); //son amb el que colisionen
//	Texture BlocLateral = LoadTexture("Sprites/blocsLateral.png");
//	Texture2D Bomb = LoadTexture("Sprites/bomb.png");
//	Texture BlocSol = LoadTexture("Sprites/blocIndividual.png");
//
//	Texture2D globustxt = LoadTexture("Sprites/altg.png");
//
//	int animFrames = 0;
//	Image imDeadAnim = LoadImageAnim("resources/dead.gif", &animFrames);
//	Texture2D texDeadAnim = LoadTextureFromImage(imDeadAnim);
//
//	Vector2 BManPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio bomberman
//	Vector2 globusPos = { (float)screenWidth / 2, (float)screenHeight / 2 };//posicio enemic globus
//
//	//JO. MARCEL, MEU
//	Vector2 bombPos = { -1.0f, -1.0f };
//
//	//frames animacions base BOMBERMAN
//	int currentFrameB = 0;
//	int frameContadorB = 0;
//	int frameSpeedB = 4; //marca la velocitat dels FPS
//	bool dead = false;
//
//	//framws animacions ENEMICS
//	int currentFrameE = 0;
//	int frameContadorE = 0;
//	int frameSpeedE = 4; //marca la velocitat dels FPS
//	//bool dead = false;
//
//	//frames animacio/gif mort
//	unsigned int nextFrameDataOffset = 0;
//
//	int currentAnimFrame = 0;
//	int frameDelay = 8;
//	int frameCounter = 0;
//
//	
//	//BOMBERMAN:
//	Rectangle frameRecB = { 0.0f, 0.0f, (float)BMan.width / 3, (float)BMan.height }; //MIDA DISPLAY FRAME
//	//Rectangle deathRec = { 0.0f, 0.0f, (float)BMan.width / 7, (float)BMan.height }; //s'hauria de fer un altra textura amb la seva propia mida
//	Vector2 characterPos = { 100.0f, 100.0f };
//	float characterSpeed = 5.0f;
//	Vector2 characterSize = { 50.0f, 50.0f };
//	
//	//ENEMICS:
//	Rectangle frameRecE = { 0.0f, 0.0f, (float)globustxt.width / 6, (float)globustxt.height }; //MIDA DISPLAY FRAME
//
//	//BOMBA:
//	Rectangle frameRecBomb = { 0.0f, 0.0f, (float)Bomb.width / 3, (float)Bomb.height };
//	
//	
//	/*Player bomberman(100.0f, 100.0f, BMan);
//	Enemy globus(100.0f, 100.0f, globustxt);*/
//
//	//entity player = { player.texture = BMan, player.position = BManPos, player.collider = playerCollider };
//	
//
//	//entity globus = { globus.texture = globustxt, globus.position = globusPos };
//
//	Camera2D camera = { 0 };
//	/*camera.target.x = bomberman.BManPos.x + 20.0f;
//	camera.target.y = bomberman.BManPos.y + 20.0f;*/
//
//	camera.target.x = BManPos.x + 20.0f;
//	camera.target.y = BManPos.y + 20.0f;
//	camera.offset.x = screenWidth / 2.0f;
//	camera.offset.y = screenHeight / 2.0f;
//	camera.rotation = 0.0f;
//	camera.zoom = 3.5f;
//
//	SetTargetFPS(60);
//
//	// game loop
//	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
//	{
//		//MARCEL
//		/*if (IsKeyPressed(KEY_C)) 
//		{
//			bombPos = BManPos;
//		}*/
//
//		/*Player bomberman;
//		Enemy globus;
//		Bloc blocs;*/
//
//		Vector2 nextPos = characterPos;
//
//		Rectangle characterRect = { nextPos.x, nextPos.y, characterSize.x, characterSize.y };
//		
//
//		/*bomberman.BManText = BMan;
//		bomberman.BManPos = BManPos;
//
//		globus.globusPos = globusPos;
//		globus.globustxt = globustxt;*/
//
//		/*UpdateMusicStream(currentMusic);*/
//		
//
//		
//
//		bool actBomb = false;
//
//		Vector2 playerVelocity = { 0.0f, 0.0f };
//
//		if (IsKeyUp) { BMan = LoadTexture("Sprites/idle.png"); }//animacio bman quiet
//
//		//if (IsKeyPressed(KEY_Z)) { dead = true; }//no va
//
//		if (IsKeyDown(KEY_RIGHT)) { BManPos.x += 1.3f; BMan = LoadTexture("Sprites/walkRight.png"); }
//		if (IsKeyDown(KEY_LEFT)) { BManPos.x -= 1.3f; BMan = LoadTexture("Sprites/walkLeft.png"); }
//		if (IsKeyDown(KEY_UP)) { BManPos.y -= 1.3f; BMan = LoadTexture("Sprites/walkBack.png"); }
//		if (IsKeyDown(KEY_DOWN)) { BManPos.y += 1.3f; BMan = LoadTexture("Sprites/walkFront.png"); }
//
//		if (IsKeyDown(KEY_Z) && !actBomb) 
//		{
//			actBomb = true;
//
//		}
//
//		//ANIMACIO BOMBERMAN
//		frameContadorB++;
//		if (frameContadorB >= (60 / frameSpeedB))
//		{
//			frameContadorB = 0;
//			currentFrameB++;
//
//			if (dead = true) {
//				//if (currentFrame > 8) currentFrame = 0;
//
//				//deathRec.x = (float)currentFrame * (float)BMan.width / 7; //MIDA DISPLAY FRAME
//
//			}
//			if (currentFrameB > 5) currentFrameB = 0;
//
//			frameRecB.x = (float)currentFrameB * (float)BMan.width / 3; //MIDA DISPLAY FRAME
//		}
//
//
//		//ANIMACIO ENEMIC GLOBUS
//		frameContadorE++;
//		if (frameContadorE >= (60 / frameSpeedE))
//		{
//			frameContadorE = 0;
//			currentFrameE++;
//
//			
//			if (currentFrameE > 5) currentFrameE = 0;
//
//			frameRecE.x = (float)currentFrameE * (float)globustxt.width / 6; //MIDA DISPLAY FRAME
//		}
//
//		//if (dead = true) 
//		// {
//		//	frameCounter++;
//		//	if (frameCounter >= frameDelay)
//		//	{
//		//		currentAnimFrame++;
//		//		if (currentAnimFrame >= animFrames) currentAnimFrame = 0;
//
//		//		// Get memory offset position for next frame data in image.data
//		//		nextFrameDataOffset = imDeadAnim.width * imDeadAnim.height * 4 * currentAnimFrame;
//
//		//		// Update GPU texture data with next frame image data
//		//		// WARNING: Data size (frame size) and pixel format must match already created texture
//		//		UpdateTexture(texDeadAnim, ((unsigned char*)imDeadAnim.data) + nextFrameDataOffset);
//
//		//		frameCounter = 0;
//		//	}
//		//}
//
//
//		//COMENCA A DIBUIXAR
//
//		BeginDrawing();
//		BeginMode2D(camera);
//
//		ClearBackground(RAYWHITE);// Setup the back buffer for drawing (clear color and depth buffers)
//
//		//___TOT EL QUE S'HAGI DE MOSTRAR PER PANTALLA DAVALL D'AIXO___
//
//		if (actBomb=true) DrawTextureRec(Bomb, frameRecBomb, BManPos, WHITE);
//
//		/*if (bombPos.x != -1.0f && bombPos.y != -1.0f) 
//		{
//
//			printf("Drawing bomb at position: (%f, %f)\n", bombPos.x, bombPos.y);
//			DrawTexture(Bomb, bombPos.x - Bomb.width / 2, bombPos.y - Bomb.height / 2);  
//		}
//			DrawTexture(Bomb, bombPos.x - Bomb.width / 2, bombPos.y - Bomb.height / 2, WHITE);  
//		}*/
//
//		/*if (IsKeyPressed(KEY_C))
//		{
//			bombPos = BManPos;
//			DrawTexture(Bomb, bombPos, WHITE);
//		}*/
//
//
//		/*if (BManPos.x > 555 && BManPos.x < 685) {
//			camera.target = { bomberman.BManPos.x + 20, (float)screenHeight / 2 - 20 };
//		}*/
//		if (BManPos.x > 555 && BManPos.x < 685) {
//			camera.target = { BManPos.x + 20, (float)screenHeight / 2 - 20 };
//		}
//
//		// drawing
//		DrawTexture(Fons, screenWidth / 2 - Fons.width / 2, screenHeight / 2 - Fons.height / 2, WHITE);
//		DrawTexture(BlocDalt, screenWidth / 2 - BlocDalt.width / 2, screenHeight / 2 - (BlocDalt.height*6.5), WHITE);
//		DrawTexture(BlocDalt, screenWidth / 2 - BlocDalt.width / 2, screenHeight / 2 + (BlocDalt.height*5.5), WHITE);
//
//		DrawTexture(BlocLateral, screenWidth / 2 - (BlocLateral.width *15.5), screenHeight / 2 - BlocLateral.height/2, WHITE);
//		DrawTexture(BlocLateral, screenWidth / 2 + (BlocLateral.width * 14.5), screenHeight / 2 - BlocLateral.height / 2, WHITE);
//
//
//		/*bomberman.draw();*/
//		DrawTextureRec(BMan, frameRecB, BManPos, WHITE);
//
//		/*globus.draw();*/
//		DrawTextureRec(globustxt, frameRecB, globusPos, WHITE);
//
//		/*if (dead = true)
//		{
//			DrawTexture(texDeadAnim, GetScreenWidth() / 2 - texDeadAnim.width / 2, 140, WHITE);
//		}*/
//
//		
//
//		DrawRectangleV(characterPos, characterSize, BLUE);
//
//		//DrawTexture(BlocLateral, BlocPos.x - BlocLateral.width / 2, blocs.BlocPos.y - BlocLateral.height / 2, WHITE);
//
//		/*timePlayedMusic = GetMusicTimePlayed(currentMusic) / GetMusicTimeLength(currentMusic);*/
//
//		/*if (timePlayedMusic > 1.0f) {
//			if (music == 0) {
//
//				StopMusicStream(currentMusic);
//				currentMusic = bgm;
//				music = 1;
//
//				PlayMusicStream(currentMusic);
//			}
//			else {
//				timePlayedMusic = 1.0f;
//			}
//		}*/
//		EndDrawing();
//	}
//	// cleanup
//	// unload our texture so it can be cleaned up
//	UnloadTexture(BMan);
//	UnloadTexture(BlocDalt);
//	UnloadTexture(Fons);
//	UnloadTexture(BlocLateral);
//	/*UnloadMusicStream(currentMusic);
//	UnloadMusicStream(startMusic);
//	UnloadMusicStream(bgm);*/
//
//	CloseAudioDevice();
//
//	UnloadTexture(texDeadAnim);   // Unload texture
//	UnloadImage(imDeadAnim);
//	UnloadTexture(Bomb);
//
//	// destroy the window and cleanup the OpenGL context
//	CloseWindow();
//	return 0;
//}