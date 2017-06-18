#pragma once
#include "Game.h"
#include "Pemain.h"
#include "Enemy.h"
#include "mazeReader.h"
#include <irrKlang.h>

using namespace irrklang;
class Demo :
	public Engine::Game
{
public:
	Pemain pemain;
	Enemy enemy1, enemy2, enemy3, enemy4;
	mazeReader read;
	ISoundEngine *SoundEngine = createIrrKlangDevice();

	float Tollerant = 0.02f;
	int highscore = 0;
	int money = 0;
	int lives = 3;

	bool boolSizingMaze=false;
	bool bCekPemainKeEnemy = true;
	bool bCekEnemyStuck= false;
	bool repeat = true;
	int timerinvisible = 0;

	int levelBase=7;
	int currentLevel = 1;
	int levelVel = 0;
	//SDL_Event evt;
	const char* MP3NAME = "bgm/UN OWEN WAS HER.mp3";
	const char* SFX1 = "bgm/pickup.wav";
	const char* SFX2 = "bgm/dead.wav";
	Demo();
	~Demo();
	void Init();
	void Update(float deltaTime);
	void Render();
	void BGM();
	void stopBGM();
	int GameOver();
	void TampilMenu();
	bool cekLives();
	void CekEnemyStuck();
	void Reset();
	int getScore();
	int getHighscore();
	int getMoney();
	int getCurrentLevel();
	int getLives();
	int mul = 1;

	void movePemainX(float a);
	void movePemainY(float a);
	void moveEnemy();
	void pemainKeEnemy();
	bool getRepeat();

	//level
	void enemyMoveFaster(float a);
	void changePatern(int a);
	void moveAllInnerWall();
	void monitorLevel();
	void sizingMaze(int a);
	void cekCollisionFood();
	void cekEnemyStuck();




};

