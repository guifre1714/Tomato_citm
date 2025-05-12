#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
using namespace std;

Player::Player() {

	bmanTXT = LoadTexture("Sprites/base.png");

	vel = 0.8f;

	bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!

	bmanPos.y = 272;
	bmanCol = { bmanPos.x, bmanPos.y, 12, 16 };

	instantiateColliders();

	colliders.insert(colliders.end(), col1);
	colliders.insert(colliders.end(), col2);
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}


void Player::Draw() {
	DrawTextureV(bmanTXT, bmanPos, WHITE);
}

void Player::MoveUp() {
	dir = "up";
	if (!Collide()) {
		bmanPos.y -= vel;
	}

}
void Player::MoveDown() {
	dir = "down";
	if (!Collide()) {
		bmanPos.y += vel;
	}
}
void Player::MoveLeft() {
	dir = "left";
	if (!Collide()) {
		bmanPos.x -= vel;
	}
}
void Player::MoveRight() {
	dir = "right";
	if (!Collide()) {
		bmanPos.x += vel;
	}
}

bool Player::Collide() {
	bool col;
	if (dir == "up") {
		bmanCol.y = bmanPos.y - vel;
		bmanCol.x = bmanPos.x;
	}
	else if (dir == "down") {
		bmanCol.y = bmanPos.y + vel;
		bmanCol.x = bmanPos.x;
	}
	else if (dir == "left") {
		bmanCol.x = bmanPos.x - vel;
		bmanCol.y = bmanPos.y;
	}
	else {
		bmanCol.x = bmanPos.x + vel;
		bmanCol.y = bmanPos.y;
	}
	for (int i = 0; i < colliders.size(); i++) {
		col = CheckCollisionRecs(bmanCol, colliders[i].col);
		if (col) return true;
	}
	if (!col) return false;
}

void Player::instantiateColliders() {
#pragma region Create Colliders
	#pragma region Parets
	col1.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col1);
	col2.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col2);
	col3.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col3);
	col4.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col4);
	#pragma endregion
	col5.col = { 424, 288, 15, 15 };
	colliders.insert(colliders.end(), col5);
	col6.col = { 456, 288, 15, 15 };
	colliders.insert(colliders.end(), col6);
	col7.col = { 488, 288, 15, 15 };
	colliders.insert(colliders.end(), col7);
	col8.col = { 520, 288, 15, 15 };
	colliders.insert(colliders.end(), col8);
	col9.col = { 552, 288, 15, 15 };
	colliders.insert(colliders.end(), col9);
	col10.col = { 584, 288, 15, 15 };
	colliders.insert(colliders.end(), col10);
	col11.col = { 616, 288, 15, 15 };
	colliders.insert(colliders.end(), col11);
	col12.col = { 648, 288, 15, 15 };
	colliders.insert(colliders.end(), col12);
	col13.col = { 680, 288, 15, 15 };
	colliders.insert(colliders.end(), col13);
	col14.col = { 712, 288, 15, 15 };
	colliders.insert(colliders.end(), col14);
	col15.col = { 744, 288, 15, 15 };
	colliders.insert(colliders.end(), col15);
	col16.col = { 776, 288, 15, 15 };
	colliders.insert(colliders.end(), col16);
	col17.col = { 808, 288, 15, 15 };
	colliders.insert(colliders.end(), col17);
	col18.col = { 840, 288, 15, 15 };
	colliders.insert(colliders.end(), col18);
	col19.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col19);
	col20.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col20);
	col21.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col21);
	col22.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col22);
	col23.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col23);
	col24.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col24);
	col25.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col25);
	col26.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col26);
	col27.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col27);
	col28.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col28);
	col29.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col29);
	col30.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col30);
	col31.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col31);
	col32.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col32);
	col33.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col33);
	col34.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col34);
	col35.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col35);
	col36.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col36);
	col37.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col37);
	col38.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col38);
	col39.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col39);
	col40.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col40);
	col41.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col41);
	col42.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col42);
	col43.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col43);
	col44.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col44);
	col45.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col45);
	col46.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col46);
	col47.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col47);
	col48.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col48);
	col49.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col49);
	col50.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col50);
	col51.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col51);
	col52.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col52);
	col53.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col53);
	col54.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col54);
	col55.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col55);
	col56.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col56);
	col57.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col57);
	col58.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col58);
	col59.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col59);
	col60.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col60);
	col61.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col61);
	col62.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col62);
	col63.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col63);
	col64.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col64);
	col65.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col65);
	col66.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col66);
	col67.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col67);
	col68.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col68);
	col69.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col69);
	col70.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col70);
	col71.col = { 392, 256, 16, 300 };
	colliders.insert(colliders.end(), col71);
	col72.col = { 872, 256, 16, 300 };
	colliders.insert(colliders.end(), col72);
	col73.col = { 408, 256, 464, 16 };
	colliders.insert(colliders.end(), col73);
	col74.col = { 408, 448, 464, 16 };
	colliders.insert(colliders.end(), col74);
#pragma endregion
}