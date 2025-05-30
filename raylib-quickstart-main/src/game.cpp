﻿#include<game.h>

using namespace std;

int i = 0;//Aux var we will later use

Game::Game(int nivell, int* pLife, int* pScreen, int* pMBombs, unsigned int seed, bool* isRemoteControl, int* puntuacio, int* contador):rng(seed)
{
	//Initialise all variables.
	duration = 179;
	timer = -1;
	level = nivell;
	Player player;
	bomberman = player;
	bomberman.score = puntuacio;
	bomberman.vides = pLife;
	bomberman.maxBombs = pMBombs;
	bomberman.pantalla = pScreen;
	timeUp = false;
	clear = false;
	freeze = false;
	mySeed = seed;
	score = puntuacio;
	time = contador;
	instantiateCoses();
	Fons = LoadTexture("Sprites/assets/Fons.png");
	bgm = LoadMusicStream("music/03. Main BGM.mp3");
	walk = LoadSound("SFX/walk.wav");
	walkUp = LoadSound("SFX/walkUp.wav");
	areRemoteControl = isRemoteControl;
	blocs = &bomberman.colliders;
	powerUpSound = LoadSound("SFX/powerUp.wav");
	clearSound = LoadSound("SFX/clear.wav");
}

Game::~Game() {
	bomberman.~Player();
	UnloadMusicStream(bgm);
	UnloadSound(walk);
}

void Game::Draw() {
	//Draw all elements in their correct order.
	door.Draw();
	for (int i = 0; i < powerUps.size(); i++) {
		powerUps[i].Draw();
	}
	for (int k = 0; k <= bomberman.colliders.size() - 1; k++) {
		if (bomberman.colliders[k].breakable) {

			bomberman.colliders[k].Draw();
		}
		if (bomberman.colliders[k].destroy) {
			bomberman.colliders.erase(bomberman.colliders.begin() + k);
		}
	}
	for (int i = 0; i < enemics.size(); i++) {
		enemics[i]->Draw();
	}
	for (int i = 0; i < scores.size(); i++) {
		if (scores[i]->time >= 90) {
			scores.erase(scores.begin() + i);
		}
		else {
			scores[i]->Draw();
		}
	}
	bomberman.Draw();
	for (int j = 0; j < bomberman.bombs.size(); j++) {
		bomberman.bombs[j].Draw();
	}
}

void Game::HandleInput() {
	if (IsKeyDown(KEY_Z) && bomberman.isAlive==true) {//DEBUG: Kill yourself.
		bomberman.Dead();
	}
	if (IsKeyDown(KEY_W)) {//DEBUG: Activate WallPass
		bomberman.isWallPass = true;
	}
	if (!freeze) {//this freeze bool is used for when Bomberman goes through the door's level, so that he doesn't move while the stage clear music plays
		if (bomberman.isAlive) {//bool to check if bomberman is alive, if false
			if (IsKeyDown(KEY_LEFT)) {
				bomberman.MoveLeft();//Bomberman moves left
				if (i > 20) {//every 0.3 seconds plays the sound of Bomberman walking
					PlaySound(walk);
					i = 0;//resets the tally counter so that it can start over again
				}
			}
			else if (IsKeyDown(KEY_RIGHT)) {
				bomberman.MoveRight();//Bomberman moves right
				if (i > 20) {
					PlaySound(walk);
					i = 0;
				}
			}
			else if (IsKeyDown(KEY_UP)) {
				bomberman.MoveUp();//Bomberman moves up
				if (i > 20) {
					PlaySound(walkUp);//when Bomberman moves in the Y axis it plays another walking sound
					i = 0;
				}
			}
			else if (IsKeyDown(KEY_DOWN)) {
				bomberman.MoveDown();//Bomberman moves down
				if (i > 20) {
					PlaySound(walkUp);
					i = 0;
				}
			}
			else if (!bomberman.idle) {//when Bomberman isn't moving in any direction, it loads the "idle sprite", which is just Bomberman staring at the front
				bomberman.idle = true;//this bool is so that it only loads ONCE the sprite
				bomberman.bmanTXT = LoadTexture("Sprites/bomberman/idle.png");
			}
			if (IsKeyPressed(KEY_X) && bomberman.bombs.size() < *bomberman.maxBombs) {//when key X is pressed and there are less bombs spawned in game than the maximum you can create
				bomberman.createBomb();//calls createBomb function from player
			}
			if ((*areRemoteControl) == true) {//checks if the power-up RemoteControl is active
				if (IsKeyPressed(KEY_C)) {//when the C key is pressed
					for (int j = 0; j < bomberman.bombs.size(); j++) {//checks every bomb spawned in the game
						bomberman.bombs[j].boom = true;//and makes them explode
						PlaySound(bomberman.bombs[j].kaboom);//and also plays the explosion sound
					}
				}
			}
			i++;//adds one to the tally counter for each pass that game does through HandleInput (which is 60 times for each second)
		}
	}
#pragma region DEBUG
	//DEBUG: KILL ALL ENEMIES
	if (IsKeyPressed(KEY_K)) {
		for (int i = 0; i < enemics.size(); i++) {
			enemics[i]->isAlive = false;
		}
	}
	//DEBUG: SPAWN POWER UPS
	if (IsKeyPressed(KEY_ONE)) {
		speedUp speedUp(&bomberman.colliders);
		speedUp.col.x = bomberman.bmanPos.x + 16;
		speedUp.col.y = bomberman.bmanPos.y + 1;
		powerUps.insert(powerUps.begin(), speedUp);
	}
	if (IsKeyPressed(KEY_TWO)) {
		bombUp bombUp(&bomberman.colliders);
		bombUp.col.x = bomberman.bmanPos.x + 16;
		bombUp.col.y = bomberman.bmanPos.y + 1;
		powerUps.insert(powerUps.begin(), bombUp);
	}
	if (IsKeyPressed(KEY_THREE)) {
		wallPass wallPass(&bomberman.colliders);
		wallPass.col.x = bomberman.bmanPos.x + 16;
		wallPass.col.y = bomberman.bmanPos.y + 1;
		powerUps.insert(powerUps.begin(), wallPass);
	}
	if (IsKeyPressed(KEY_FOUR)) {
		remoteControl remoteControl(&bomberman.colliders);
		remoteControl.col.x = bomberman.bmanPos.x + 16;
		remoteControl.col.y = bomberman.bmanPos.y + 1;
		powerUps.insert(powerUps.begin(), remoteControl);
	}
	//DEBUG: SPAWN DOOR
	if (IsKeyPressed(KEY_D)) { 
		door.col.x = bomberman.bmanPos.x + 21;
		door.col.y = bomberman.bmanPos.y + 7;
	}
#pragma endregion
}

void Game::instantiateCoses() {
int l;
#pragma region Create Colliders
#pragma region Parets
	col1.col = { 408, 256, 464, 16 };
	bomberman.colliders.insert(bomberman.colliders.end(), col1);
	col2.col = { 408, 448, 464, 16 };
	bomberman.colliders.insert(bomberman.colliders.end(), col2);
	col3.col = { 392, 256, 16, 300 };
	bomberman.colliders.insert(bomberman.colliders.end(), col3);
	col4.col = { 872, 256, 16, 300 };
	bomberman.colliders.insert(bomberman.colliders.end(), col4);
#pragma endregion
	//fila 1
	col5.col = { 425, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col5);
	col6.col = { 457, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col6);
	col7.col = { 489, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col7);
	col8.col = { 521, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col8);
	col9.col = { 553, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col9);
	col10.col = { 585, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col10);
	col11.col = { 617, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col11);
	col12.col = { 649, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col12);
	col13.col = { 681, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col13);
	col14.col = { 713, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col14);
	col15.col = { 745, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col15);
	col16.col = { 777, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col16);
	col17.col = { 809, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col17);
	col18.col = { 841, 289, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col18);
	//fila 2
	col19.col = { 425, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col19);
	col20.col = { 457, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col20);
	col21.col = { 489,	321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col21);
	col22.col = { 521, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col22);
	col23.col = { 553, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col23);
	col24.col = { 585, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col24);
	col25.col = { 617, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col25);
	col26.col = { 649, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col26);
	col27.col = { 681, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col27);
	col28.col = { 713, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col28);
	col29.col = { 745, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col29);
	col30.col = { 777, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col30);
	col31.col = { 809, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col31);
	col32.col = { 841, 321, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col32);
	//fila 3
	col33.col = { 425, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col33);
	col34.col = { 457, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col34);
	col35.col = { 489, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col35);
	col36.col = { 521, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col36);
	col37.col = { 553, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col37);
	col38.col = { 585, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col38);
	col39.col = { 617, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col39);
	col40.col = { 649, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col40);
	col41.col = { 681, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col41);
	col42.col = { 713, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col42);
	col43.col = { 745, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col43);
	col44.col = { 777, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col44);
	col45.col = { 809, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col45);
	col46.col = { 841, 353, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col46);
	//fila 4
	col47.col = { 425, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col47);
	col48.col = { 457, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col48);
	col49.col = { 489, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col49);
	col50.col = { 521, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col50);
	col51.col = { 553, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col51);
	col52.col = { 585, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col52);
	col53.col = { 617, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col53);
	col54.col = { 649, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col54);
	col55.col = { 681, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col55);
	col56.col = { 713, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col56);
	col57.col = { 745, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col57);
	col58.col = { 777, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col58);
	col59.col = { 809, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col59);
	col60.col = { 841, 385, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col60);
	//fila 5
	col61.col = { 425, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col61);
	col62.col = { 457, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col62);
	col63.col = { 489, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col63);
	col64.col = { 521, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col64);
	col65.col = { 553, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col65);
	col66.col = { 585, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col66);
	col67.col = { 617, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col67);
	col68.col = { 649, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col68);
	col69.col = { 681, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col69);
	col70.col = { 713, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col70);
	col71.col = { 745, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col71);
	col72.col = { 777, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col72);
	col73.col = { 809, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col73);
	col74.col = { 841, 417, 13, 13 };
	bomberman.colliders.insert(bomberman.colliders.end(), col74);
#pragma endregion
#pragma region Positions where things can spawn
	for (int k = 2; k <= 28; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 16);
		pos.y = 272;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 28; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 16);
		pos.y = 304;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 28; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 16);
		pos.y = 336;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 28; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 16);
		pos.y = 368;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 28; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 16);
		pos.y = 400;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 28; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 16);
		pos.y = 432;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 14; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 32);
		pos.y = 320;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 13; k++) {
		Vector2 pos;
		pos.x = 440 + (k * 32);
		pos.y = 288;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 14; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 32);
		pos.y = 352;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 14; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 32);
		pos.y = 384;
		spawnPos.insert(spawnPos.end(), pos);
	}
	for (int k = 0; k <= 14; k++) {
		Vector2 pos;
		pos.x = 408 + (k * 32);
		pos.y = 416;
		spawnPos.insert(spawnPos.end(), pos);
	}
#pragma endregion
	uniform_int_distribution<int> numBlocs(60, 80);
	int num = numBlocs(rng);
	bomberman.snapPositions = spawnPos;
	int globus_amount;
	int gota_amount;
	//Different level set ups.
	if (level == 3){ globus_amount = 6; gota_amount = 0; }
	else if (level == 5) { globus_amount = 4; gota_amount = 2; }
	else if (level == 7) { globus_amount = 3; gota_amount = 3; }
	else { globus_amount = 4; gota_amount = 4; }

	//Spawn enemies in random locations (based on seed).
	for (int i = 0; i < globus_amount; ++i) {
		if (spawnPos.empty()) break;

		uniform_int_distribution<int> blocPos(0, spawnPos.size() - 1);
		int l = blocPos(rng);

		// Security validation.
		if (l >= 0 && l < spawnPos.size()) {
			enemics.push_back(new EN01(spawnPos[l], &bomberman.colliders, &bomberman, &bomberman.bombs));
			spawnPos.erase(spawnPos.begin() + l);
		}
	}
	for (int i = 0; i < gota_amount; ++i) {
		if (spawnPos.empty()) break;

		uniform_int_distribution<int> blocPos(0, spawnPos.size() - 1);
		int l = blocPos(rng);

		// Security validation.
		if (l >= 0 && l < spawnPos.size()) {
			enemics.push_back(new EN03(spawnPos[l], &bomberman.colliders, &bomberman, &bomberman.bombs));
			spawnPos.erase(spawnPos.begin() + l);
		}
	}
	//Spawn breakable blocks in free positions after spawning enemies (depends on seed).
	uniform_int_distribution<int> blocPos(0, spawnPos.size() - 1);
	for (int k = 0; k < num; k++) 
	{
		l = blocPos(rng);
		Breakable bloc(spawnPos[l]);
		powerUpPositions.insert(powerUpPositions.end(), spawnPos[l]);
		bomberman.colliders.insert(bomberman.colliders.end(), bloc);
	}
	//Ends setting up all possible positions in which the player can place a bomb.
	Vector2 pos;
	pos.x = 424;
	pos.y = 272;
	bomberman.snapPositions.insert(bomberman.snapPositions.begin(), pos);
	Vector2 pos2;
	pos2.x = 408;
	pos2.y = 272;
	bomberman.snapPositions.insert(bomberman.snapPositions.begin(), pos2);
	Vector2 pos3;
	pos3.x = 408;
	pos3.y = 288;
	bomberman.snapPositions.insert(bomberman.snapPositions.begin(), pos3);
	//Spawn door at a random breakable wall position and do the same with each level's power up.
	uniform_int_distribution<int> pUpPos(0, powerUpPositions.size() - 1);
	l = pUpPos(rng);
	door.col.x = powerUpPositions[l].x + 8;
	door.col.y = powerUpPositions[l].y + 8;
	door.col.width = 1;
	door.col.height = 1;
	powerUpPositions.erase(powerUpPositions.begin() + l);
	//Spawn only one power up per level.
	if (level == 9) {
		speedUp speedUp(&bomberman.colliders);
		l = pUpPos(rng);
		speedUp.col.x = powerUpPositions[l].x + 1;
		speedUp.col.y = powerUpPositions[l].y + 1;
		powerUps.insert(powerUps.begin(), speedUp);
		powerUpPositions.erase(powerUpPositions.begin() + l);
	}
	if (level == 7) {
		remoteControl remoteControl(&bomberman.colliders);
		l = pUpPos(rng);
		remoteControl.col.x = powerUpPositions[l].x + 1;
		remoteControl.col.y = powerUpPositions[l].y + 1;
		powerUps.insert(powerUps.begin(), remoteControl);
		powerUpPositions.erase(powerUpPositions.begin() + l);
	}
	if (level == 5) {
		wallPass wallPass(&bomberman.colliders);
		l = pUpPos(rng);
		wallPass.col.x = powerUpPositions[l].x + 1;
		wallPass.col.y = powerUpPositions[l].y + 1;
		powerUps.insert(powerUps.begin(), wallPass);
		powerUpPositions.erase(powerUpPositions.begin() + l);
	}
	else {
		bombUp bombUp(&bomberman.colliders);
		l = pUpPos(rng);
		bombUp.col.x = powerUpPositions[l].x + 1;
		bombUp.col.y = powerUpPositions[l].y + 1;
		powerUps.insert(powerUps.begin(), bombUp);
		powerUpPositions.erase(powerUpPositions.begin() + l);
	}
}

void Game::Update() 
{
	if (!clear && enemics.size() == 0) {//If the last enemy is killed, play the clear sound to let the player know he can now go through the door.
		clear = true;
		PlaySound(clearSound);
	}
	for (int i = 0; i < enemics.size(); i++)
	{
		//Check if an enemy has died and draw the score it gives.
		if (enemics[i]->isAlive == false) {
			(*score) += enemics[i]->points;
			bomberman.p_guanyats = *score;
			spawnPos.push_back(enemics[i]->EN_pos);
			if (enemics[i]->points == 100){
				scores.push_back(new Score(enemics[i]->EN_pos, LoadTexture("Sprites/puntuacio/100.png")));
			} else if (enemics[i]->points == 8000) {
				scores.push_back(new Score(enemics[i]->EN_pos, LoadTexture("Sprites/puntuacio/8000.png")));
			} else if (enemics[i]->points == 200) {
				scores.push_back(new Score(enemics[i]->EN_pos, LoadTexture("Sprites/puntuacio/200.png")));
			}
			enemics.erase(enemics.begin() + i);
		}//If the checked enemy is not dead, call its update function.
		else {
			enemics[i]->Update();
		}
	}
	checkPowerUps();//Check if player has picked up a power up.
	for (int j = 0; j < bomberman.bombs.size(); j++) {
		bomberman.bombs[j].remoCon = (*areRemoteControl);//Set bombs to remote control mode if player has said power up.
	}
	//When time is up: erase all active enemies and spawn 10 COIN enemies at random locations.
	if ((*time) <= 0 && !timeUp) {
		if (enemics.size() != 0) {
			for (int i = 0; i < enemics.size(); i++)
			{
				spawnPos.push_back(enemics[i]->EN_pos);
				enemics.erase(enemics.begin() + i);
			}
		}
		else {
			for (int i = 0; i < 10; ++i) {
				if (spawnPos.empty()) break;

				uniform_int_distribution<int> blocPos(0, spawnPos.size() - 1);
				int l = blocPos(rng);

				// Validació per seguretat
				if (l >= 0 && l < spawnPos.size()) {
					enemics.push_back(new EN02(spawnPos[l], &bomberman.colliders, &bomberman, &bomberman.bombs));
					spawnPos.erase(spawnPos.begin() + l);
				}
			}
			timeUp = true;
		}
	}
}

bool Game::nextLevel() {//Check if player can pass through door.
	for (int j = 0; j < bomberman.colliders.size(); j++) {
		if (CheckCollisionRecs(door.col, bomberman.colliders[j].col) == true || enemics.size()>0) {
			return false;
		}
	}
	return door.playerCol(&bomberman);
}

void Game::checkPowerUps() {//Check if player has picked up a power up and which one.
	bool collided = false;
	for (int i = 0; i < powerUps.size(); i++)
	{
		if (powerUps[i].playerCol(&bomberman)) {//Check if player is touching a power up.
			for (int j = 0; j < (*blocs).size(); j++) {//Check if said power up is still behind a block.
				if (!collided) {
					collided = CheckCollisionRecs(powerUps[i].col, bomberman.colliders[j].col);
				}
			}
			if (!collided) {//If the power up is not behind a block, play the power up sound, give its according effect to the player and erase it.
				PlaySound(powerUpSound);
				bgm = LoadMusicStream("music/04. Power-Up Get.mp3");
				PlayMusicStream(bgm);
				if (powerUps[i].type == "speedUp") {
					bomberman.vel += 0.2;
					powerUps.erase(powerUps.begin() + i);
				}
				else if (powerUps[i].type == "bombUp") {
					++(*bomberman.maxBombs);
					bomberman.gainedBomb = true;
					powerUps.erase(powerUps.begin() + i);
				}
				else if (powerUps[i].type == "remoteControl") {
					(*areRemoteControl) = true;
					powerUps.erase(powerUps.begin() + i);
				}
				else if (powerUps[i].type == "wallPass") {
					bomberman.isWallPass = true;
					powerUps.erase(powerUps.begin() + i);
				}
			}
		}
	}
}