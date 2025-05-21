#include <vector>
#include <player.h>
#include <collider.h>
#include <screen.h>
#include <breakable.h>
#include <Enemy_01.h>
#include <Enemy_02.h>
#include <bomba.h>
#include <door.h>
#include <speedUp.h>
#include <powerUp.h>
#include <bombUp.h>
#include <random>
#include <remoteControl.h>
#include <wallPass.h>
#include <score.h>

using namespace std;

class Game : public Screen{
public:
	Game(int nivell, int* pLife, int* pScreen, int* pMBombs, unsigned int seed, bool* isRemoteControl, int* puntuacio, int* contador);
	~Game();

	void Draw();
	void Update();
	void HandleInput();
	bool nextLevel();
	void instantiateCoses();
	void checkPowerUps();

	int level;
	int* time;
	int* score;
	bool timeUp;
	Sound walk;
	Sound walkUp;
	mt19937 rng;

	bool* areRemoteControl;
     
	vector<Enemy*> enemics;
	vector<Score*> scores;

	vector <Vector2> spawnPos;
	vector <Vector2> powerUpPositions;
	Door door;
	vector <powerUp> powerUps;
	vector<Collider>* blocs;

	Sound powerUpSound;
	Sound clearSound;
	bool clear;
#pragma region Colliders
	Collider col1;
	Collider col2;
	Collider col3;
	Collider col4;
	Collider col5;
	Collider col6;
	Collider col7;
	Collider col8;
	Collider col9;
	Collider col10;
	Collider col11;
	Collider col12;
	Collider col13;
	Collider col14;
	Collider col15;
	Collider col16;
	Collider col17;
	Collider col18;
	Collider col19;
	Collider col20;
	Collider col21;
	Collider col22;
	Collider col23;
	Collider col24;
	Collider col25;
	Collider col26;
	Collider col27;
	Collider col28;
	Collider col29;
	Collider col30;
	Collider col31;
	Collider col32;
	Collider col33;
	Collider col34;
	Collider col35;
	Collider col36;
	Collider col37;
	Collider col38;
	Collider col39;
	Collider col40;
	Collider col41;
	Collider col42;
	Collider col43;
	Collider col44;
	Collider col45;
	Collider col46;
	Collider col47;
	Collider col48;
	Collider col49;
	Collider col50;
	Collider col51;
	Collider col52;
	Collider col53;
	Collider col54;
	Collider col55;
	Collider col56;
	Collider col57;
	Collider col58;
	Collider col59;
	Collider col60;
	Collider col61;
	Collider col62;
	Collider col63;
	Collider col64;
	Collider col65;
	Collider col66;
	Collider col67;
	Collider col68;
	Collider col69;
	Collider col70;
	Collider col71;
	Collider col72;
	Collider col73;
	Collider col74;
#pragma endregion
};
