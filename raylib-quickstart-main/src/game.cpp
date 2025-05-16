#include<game.h>
#include<bomba.h>
#include <vector>
#include <Enemy_01.h>
#include <string>
using namespace std;

int i = 0;
int j = 0;

Game::Game()
{
	Player player;
	bomberman = player;
	instantiateColliders();
	j = 120;
	Fons = LoadTexture("Sprites/Fons.png");
	bgm = LoadMusicStream("music/03. Main BGM.mp3");
	walk = LoadSound("SFX/walk.wav");
	bomb = LoadSound("SFX/bomb.wav");

	//enemic
	EN01 enemy(5, 5, 16, 16, 5, 5);
	enemic.insert(enemic.end(), enemy);

}

Game::~Game() {
	bomberman.~Player();
	UnloadMusicStream(bgm);
	UnloadSound(walk);
}

void Game::Draw() {
	//BUCLE FOR PER PINTAR ELS COLLIDERS DE LES CAIXES
	/*for (int i = 0; i < bomberman.colliders.size(); i++) {
		DrawRectangleRec(bomberman.colliders[i].col, GOLD);
	}*/
	bomberman.Draw();
	for (int i = 0; i<=enemic.size()-1;i++)
	{
		enemic[i].Draw();
	}
}

void Game::HandleInput() {
	if (IsKeyDown(KEY_Z)&& bomberman.isAlive==true) {
		bomberman.Dead();
	}
	if (bomberman.isAlive) {
		if (IsKeyDown(KEY_LEFT)) {
			bomberman.MoveLeft();
			if (i > 20) {
				PlaySound(walk);
				i = 0;
			}
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			bomberman.MoveRight();
			if (i > 20) {
				PlaySound(walk);
				i = 0;
			}
		}
		else if (IsKeyDown(KEY_UP)) {
			bomberman.MoveUp();
			if (i > 20) {
				PlaySound(walk);
				i = 0;
			}
		}
		else if (IsKeyDown(KEY_DOWN)) {

			bomberman.MoveDown();
			if (i > 20) {
				PlaySound(walk);
				i = 0;
			}
		}
		else {
			bomberman.bmanTXT = LoadTexture("Sprites/idle.png");
		}
		if (IsKeyPressed(KEY_X)) {
			if (j > 120) {
				bomberman.createBomb();
				PlaySound(bomb);
				j = 0;
			}
		}
		if (j > 120 && bomberman.bombExist == true) {
			bomberman.bombExist = false;
			bomberman.bombs[0].~Bomba();
			bomberman.bombs.erase(bomberman.bombs.begin());
		}
		i++;
		j++;
	}
	
}

void Game::instantiateColliders() {
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
}

void Game::Update() 
{
	for (int i = 0; i <= enemic.size() - 1; i++)
	{
		enemic[i].Update();
	}
}