#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Maze.h"
#include "Pemain.h"
#include "enemy.h"
#include "Makanan.h"
#include <vector>
#include <SDL.h>
#include "object.h"
#include "Tembok.h"
#include <irrKlang.h>


	class mazeReader
	{
	public:
		float pemainX;
		float pemainY;
		float revertEnemy = 1;
		float Tollerant = 0.01f, Tollerant2= 0.02f;

		int loop=0, score=0, patern=2;
		int texture, spawn;
		bool bloop = true;
		bool isiTembokData = true;
		bool isiEnemyData = true;
		bool isiMakananData = true;
		bool isiTembokInnerData = true;
		bool isiPemainData = true;
		bool isiSpawn = true;

		bool boolArah = true;
		int jumMakanan=0, lastime=0, currentTime, countMakanan;
		
		std::vector <char> data;
		std::vector <Pemain> pemainData;
		std::vector <Tembok> tembokData;
		std::vector <Tembok> tembokInnerData;
		std::vector <Enemy> enemyData;
		std::vector <Makanan> makananData;
		
		Tembok wall;
		Tembok wallInner;
		Maze generate;
		Pemain remiria;
		Enemy furandure;
		Makanan food;

		ifstream file;
		float widthMaze, heightMaze, positionx, positiony, width, widthTembok, height, heightTembok, xAwal, xAkhir, yAwal, yAkhir;
		
		mazeReader();
		~mazeReader();
		void Read();
		void getTextInfo();
		void drawObject();
		void inputan(SDL_Event evt);
		void Update();
		void Render();
		
		void enemyMove();
		
		void tembokDraw();
		void tembokInnerDraw();
		void enemyDraw();
		void foodDraw();
		void pemainDraw();
		bool noMakananLeft();
	};

