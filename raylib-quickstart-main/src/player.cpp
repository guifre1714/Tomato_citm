#include <player.h>
#include <vector>
#include <collider.h>
#include <game.h>
#include <bomba.h>

Player::Player() {
	bombExist = false;
	bmanTXT = LoadTexture("Sprites/idle.png");
	vel = 0.8f;

	bmanPos.x = 410; //CAL AJUSTAR POSICIO INICIAL !!!!!!!!!
	bmanPos.y = 272;
	
	bmanCol = { bmanPos.x, bmanPos.y, 12, 15 };

	frameRecB = { 0.0f, 0.0f, 12.0f, 16.0f };

	currentFrameB = 0;
	frameContadorB = 0;
	frameSpeedB = 8; //marca la velocitat dels FPS
	
	totalFrames=3;
	ampladaFrames = 12;

	
	instantiateColliders();

	colliders.insert(colliders.end(), col1);
	colliders.insert(colliders.end(), col2);
}

Player::~Player() {
	UnloadTexture(bmanTXT);
}


void Player::Draw() {
	frameContadorB ++;
	if (frameContadorB >= (60 / frameSpeedB)) {
		frameContadorB = 0;
		currentFrameB ++;

		if (currentFrameB > totalFrames) {
			currentFrameB = 0;
		}
		frameRecB.x = (float)currentFrameB * ampladaFrames;//12 = (float)Texture.Width/num requadres a dividir, en aquest cas 3
	}
	if (bombExist) {
		bombs[0].Draw();
	}
	DrawTextureRec(bmanTXT,frameRecB, bmanPos, WHITE);
}

void Player::MoveUp() {
	bmanTXT = LoadTexture("Sprites/walkBack.png");
	dir = "up";
	if (!Collide()) {
		bmanPos.y -= vel;
	}

}
void Player::MoveDown() {
	bmanTXT = LoadTexture("Sprites/walkFront.png");
	dir = "down";
	if (!Collide()) {
		bmanPos.y += vel;
	}
}
void Player::MoveLeft() {
	bmanTXT = LoadTexture("Sprites/walkLeft.png");
	dir = "left";
	if (!Collide()) {
		bmanPos.x -= vel;
	}
}
void Player::MoveRight() {
	
	bmanTXT = LoadTexture("Sprites/walkRight.png");
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
	//fila 1
	col5.col = { 425, 289, 13, 13 }; //{x, y, alçada, amplada} has de: {+1, +1, 13, 13}
	colliders.insert(colliders.end(), col5);
	col6.col = { 457, 289, 13, 13 };
	colliders.insert(colliders.end(), col6);
	col7.col = { 489, 289, 13, 13 };
	colliders.insert(colliders.end(), col7);
	col8.col = { 521, 289, 13, 13 };
	colliders.insert(colliders.end(), col8);
	col9.col = { 553, 289, 13, 13 };
	colliders.insert(colliders.end(), col9);
	col10.col = { 585, 289, 13, 13 };
	colliders.insert(colliders.end(), col10);
	col11.col = { 617, 289, 13, 13 };
	colliders.insert(colliders.end(), col11);
	col12.col = { 649, 289, 13, 13 };
	colliders.insert(colliders.end(), col12);
	col13.col = { 681, 289, 13, 13 };
	colliders.insert(colliders.end(), col13);
	col14.col = { 713, 289, 13, 13 };
	colliders.insert(colliders.end(), col14);
	col15.col = { 745, 289, 13, 13 };
	colliders.insert(colliders.end(), col15);
	col16.col = { 777, 289, 13, 13 };
	colliders.insert(colliders.end(), col16);
	col17.col = { 809, 289, 13, 13 };
	colliders.insert(colliders.end(), col17);
	col18.col = { 841, 289, 13, 13 };
	colliders.insert(colliders.end(), col18);
	//fila 2
	col19.col = { 425, 321, 13, 13 };
	colliders.insert(colliders.end(), col19);
	col20.col = { 457, 321, 13, 13 };
	colliders.insert(colliders.end(), col20);
	col21.col = { 489,	321, 13, 13 };
	colliders.insert(colliders.end(), col21);
	col22.col = { 521, 321, 13, 13 };
	colliders.insert(colliders.end(), col22);
	col23.col = { 553, 321, 13, 13 };
	colliders.insert(colliders.end(), col23);
	col24.col = { 585, 321, 13, 13 };
	colliders.insert(colliders.end(), col24);
	col25.col = { 617, 321, 13, 13 };
	colliders.insert(colliders.end(), col25);
	col26.col = { 649, 321, 13, 13 };
	colliders.insert(colliders.end(), col26);
	col27.col = { 681, 321, 13, 13 };
	colliders.insert(colliders.end(), col27);
	col28.col = { 713, 321, 13, 13 };
	colliders.insert(colliders.end(), col28);
	col29.col = { 745, 321, 13, 13 };
	colliders.insert(colliders.end(), col29);
	col30.col = { 777, 321, 13, 13 };
	colliders.insert(colliders.end(), col30);
	col31.col = { 809, 321, 13, 13 };
	colliders.insert(colliders.end(), col31);
	col32.col = { 841, 321, 13, 13 };
	colliders.insert(colliders.end(), col32);
	//fila 3
	col33.col = { 425, 353, 13, 13 };
	colliders.insert(colliders.end(), col33);
	col34.col = { 457, 353, 13, 13 };
	colliders.insert(colliders.end(), col34);
	col35.col = { 489, 353, 13, 13 };
	colliders.insert(colliders.end(), col35);
	col36.col = { 521, 353, 13, 13 };
	colliders.insert(colliders.end(), col36);
	col37.col = { 553, 353, 13, 13 };
	colliders.insert(colliders.end(), col37);
	col38.col = { 585, 353, 13, 13 };
	colliders.insert(colliders.end(), col38);
	col39.col = { 617, 353, 13, 13 };
	colliders.insert(colliders.end(), col39);
	col40.col = { 649, 353, 13, 13 };
	colliders.insert(colliders.end(), col40);
	col41.col = { 681, 353, 13, 13 };
	colliders.insert(colliders.end(), col41);
	col42.col = { 713, 353, 13, 13 };
	colliders.insert(colliders.end(), col42);
	col43.col = { 745, 353, 13, 13 };
	colliders.insert(colliders.end(), col43);
	col44.col = { 777, 353, 13, 13 };
	colliders.insert(colliders.end(), col44);
	col45.col = { 809, 353, 13, 13 };
	colliders.insert(colliders.end(), col45);
	col46.col = { 841, 353, 13, 13 };
	colliders.insert(colliders.end(), col46);
	//fila 4
	col47.col = { 425, 385, 13, 13 };
	colliders.insert(colliders.end(), col47);
	col48.col = { 457, 385, 13, 13 };
	colliders.insert(colliders.end(), col48);
	col49.col = { 489, 385, 13, 13 };
	colliders.insert(colliders.end(), col49);
	col50.col = { 521, 385, 13, 13 };
	colliders.insert(colliders.end(), col50);
	col51.col = { 553, 385, 13, 13 };
	colliders.insert(colliders.end(), col51);
	col52.col = { 585, 385, 13, 13 };
	colliders.insert(colliders.end(), col52);
	col53.col = { 617, 385, 13, 13 };
	colliders.insert(colliders.end(), col53);
	col54.col = { 649, 385, 13, 13 };
	colliders.insert(colliders.end(), col54);
	col55.col = { 681, 385, 13, 13 };
	colliders.insert(colliders.end(), col55);
	col56.col = { 713, 385, 13, 13 };
	colliders.insert(colliders.end(), col56);
	col57.col = { 745, 385, 13, 13 };
	colliders.insert(colliders.end(), col57);
	col58.col = { 777, 385, 13, 13 };
	colliders.insert(colliders.end(), col58);
	col59.col = { 809, 385, 13, 13 };
	colliders.insert(colliders.end(), col59);
	col60.col = { 841, 385, 13, 13 };
	colliders.insert(colliders.end(), col60);
	//fila 5
	col61.col = { 425, 417, 13, 13 };
	colliders.insert(colliders.end(), col61);
	col62.col = { 457, 417, 13, 13 };
	colliders.insert(colliders.end(), col62);
	col63.col = { 489, 417, 13, 13 };
	colliders.insert(colliders.end(), col63);
	col64.col = { 521, 417, 13, 13 };
	colliders.insert(colliders.end(), col64);
	col65.col = { 553, 417, 13, 13 };
	colliders.insert(colliders.end(), col65);
	col66.col = { 585, 417, 13, 13 };
	colliders.insert(colliders.end(), col66);
	col67.col = { 617, 417, 13, 13 };
	colliders.insert(colliders.end(), col67);
	col68.col = { 649, 417, 13, 13 };
	colliders.insert(colliders.end(), col68);
	col69.col = { 681, 417, 13, 13 };
	colliders.insert(colliders.end(), col69);
	col70.col = { 713, 417, 13, 13 };
	colliders.insert(colliders.end(), col70);
	col71.col = { 745, 417, 13, 13 };
	colliders.insert(colliders.end(), col71);
	col72.col = { 777, 417, 13, 13 };
	colliders.insert(colliders.end(), col72);
	col73.col = { 809, 417, 13, 13 };
	colliders.insert(colliders.end(), col73);
	col74.col = { 841, 417, 13, 13 };
	colliders.insert(colliders.end(), col74);
#pragma endregion
}
void Player::createBomb() {
	Bomba bomb(bmanPos);
	bombs.insert(bombs.end(), bomb);
	bombExist = true;
}