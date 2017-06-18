#include "mazeReader.h"


mazeReader::mazeReader()
{
}


mazeReader::~mazeReader()
{
}

void mazeReader::getTextInfo() {
	cout << "Pilih Karakter Sabilman (1-2)" << endl;
	cin >> texture;
	if (texture==1||texture==2) {
		remiria.loadTexture(texture);
	}
	else {
		remiria.loadTexture(1);
	}
	heightMaze = 1;
	widthMaze = 0;
	float TMPwidthMaze = 0;
	char karakter;
	file.open("maze.txt");
	while (!file.eof() && file.get(karakter)) {
		TMPwidthMaze++;
		if (karakter == 'n') {
			heightMaze++;
			if (TMPwidthMaze>widthMaze) {
				widthMaze = (TMPwidthMaze-2);
			}
			TMPwidthMaze = 0;
		}
		else if (karakter == 'd') {
			if (TMPwidthMaze>widthMaze) {
				widthMaze = (TMPwidthMaze-2);
			}
			TMPwidthMaze = 0;
		}
	}
	file.close();
}

void mazeReader::Read() {
	width = 2.0f / widthMaze;
	widthTembok = width;
	height = 2.0f / heightMaze;
	heightTembok = height;
	char singlechar;
	positionx = -(1 - (width / 2));
	xAwal = positionx;
	xAkhir = xAwal+(width*(widthMaze-1));
	positiony = 1 - (height / 2);
	yAwal = positiony;
	yAkhir = -(yAwal);
	file.open("maze.txt");
	while (file.get(singlechar)) {
		if (singlechar == '#') {
			data.push_back(singlechar);
		}
		else if (singlechar=='$') {
			data.push_back(singlechar);
		}
		else if(singlechar=='-')
		{
			data.push_back(singlechar);
		}
		else if (singlechar=='n'){
			data.push_back(singlechar);
		}
		else if (singlechar=='d') {
			data.push_back(singlechar);
		}
		else if(singlechar=='r'){
			data.push_back(singlechar);
		}
		else if (singlechar=='f') {
			data.push_back(singlechar);
		}
		else if (singlechar=='m') {
			data.push_back(singlechar);
			jumMakanan++;
		}

	}
	countMakanan = jumMakanan;
}

void mazeReader::drawObject() {
	positionx = xAwal;
	positiony = yAwal;
	for (int i = 0; i < data.size();i++) {
		
		if (data[i] == '#') {
			
			if (isiTembokData) {
				tembokData.push_back(Tembok(positionx, positiony));
			}		
			positionx += width;
		}
		else if (data[i] == '$') {
			if (isiTembokInnerData) {
				tembokInnerData.push_back(Tembok(positionx, positiony));
			}
			positionx += width;
		}
		else if (data[i] == 'n') {
			//stop ngitung width dan bikin object di line berikutnya
			positionx = xAwal;
			positiony -= height;
		}
		else if (data[i] == 'r') {
			//bikin player
			if (isiPemainData) {
				pemainX = positionx;
				pemainY = positiony;
				pemainData.push_back(Pemain(positionx, positiony));
			}
			positionx += width;
			
		}
		else if (data[i] == 'm') {
			if (isiMakananData) {
				makananData.push_back(Makanan(positionx,positiony));
			}
			positionx += width;
		}
		else if (data[i] == 'f') {
			//bikin enemy
			if (isiEnemyData) {
				enemyData.push_back(Enemy(positionx, positiony));
			}
			
			positionx += width;
		}
		else if (data[i] = '-') {
			//draw space dalam maze
			positionx += width;
		}
		else if (data[i] == 'd') {
			break;
			
		}
	}
	isiEnemyData = false;
	isiMakananData = false;
	isiTembokData = false;
	isiTembokInnerData = false;
	isiPemainData = false;
	if (isiSpawn) {
		int a;
		cout << "Pilih spawn point: " << endl;
		cin >>a;
		if(a!=NULL)
		pemainDraw();
	}
	else
	{
		pemainDraw();
	}
	isiSpawn = false;
	pemainDraw();
	enemyDraw();
	foodDraw();
	tembokDraw();
	tembokInnerDraw();
}

void mazeReader::inputan(SDL_Event evt) {
	if (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_KEYDOWN:
			if (evt.key.keysym.sym == SDLK_a) {
				pemainX -= 0.1f;
				break;
			}
			else if (evt.key.keysym.sym == SDLK_d) {
				pemainX += 0.1f;
				break;
			}
			else if (evt.key.keysym.sym == SDLK_w) {
				pemainY += 0.1f;
				break;
			}
			else if (evt.key.keysym.sym == SDLK_s) {
				pemainY -= 0.1f;
				break;
			}
		}
	}
}

void mazeReader::enemyMove() {
	if (patern==1) {

		for (int i = 0; i < enemyData.size();i++) {
			if (enemyData[i].arahPattern_2==0) {
				bool gerak = true;
				for (int j = 0; j < tembokData.size();j++) {
					if (abs(enemyData[i].posX + enemyData[i].velocity < tembokData[j].presentX + widthTembok - Tollerant2) && abs(enemyData[i].posX + enemyData[i].velocity + widthTembok - Tollerant2 > tembokData[j].presentX) && abs(enemyData[i].posY - enemyData[i].velocity < tembokData[j].presentY + heightTembok - Tollerant2) && abs(enemyData[i].posY - enemyData[i].velocity + heightTembok - Tollerant2 > tembokData[j].presentY)) {
						gerak = false;
						enemyData[i].arahPattern_2 = 1;
						break;
					}
				}
				if (gerak) {
					
					enemyData[i].posX += enemyData[i].velocity;
					enemyData[i].posY -= enemyData[i].velocity;
				}
			}
			else if(enemyData[i].arahPattern_2==1)
			{
				bool gerak = true;
				for (int j = 0; j < tembokData.size(); j++) {
					if (abs(enemyData[i].posX + enemyData[i].velocity < tembokData[j].presentX + widthTembok - Tollerant2) && abs(enemyData[i].posX + enemyData[i].velocity + widthTembok - Tollerant2 > tembokData[j].presentX) && abs(enemyData[i].posY + enemyData[i].velocity < tembokData[j].presentY + heightTembok - Tollerant2) && abs(enemyData[i].posY + enemyData[i].velocity + heightTembok - Tollerant2 > tembokData[j].presentY)) {
						gerak = false;
						enemyData[i].arahPattern_2 = 2;
						break;
					}
				}
				if (gerak) {

					enemyData[i].posX += enemyData[i].velocity;
					enemyData[i].posY += enemyData[i].velocity;
				}
			}
			else if (enemyData[i].arahPattern_2 == 2)
			{
				bool gerak = true;
				for (int j = 0; j < tembokData.size(); j++) {
					if (abs(enemyData[i].posX - enemyData[i].velocity < tembokData[j].presentX + widthTembok - Tollerant2) && abs(enemyData[i].posX - enemyData[i].velocity + widthTembok - Tollerant2 > tembokData[j].presentX) && abs(enemyData[i].posY + enemyData[i].velocity < tembokData[j].presentY + heightTembok - Tollerant2) && abs(enemyData[i].posY + enemyData[i].velocity + heightTembok - Tollerant2 > tembokData[j].presentY)) {
						gerak = false;
						enemyData[i].arahPattern_2 = 3;
						break;
					}
				}
				if (gerak) {

					enemyData[i].posX -= enemyData[i].velocity;
					enemyData[i].posY += enemyData[i].velocity;
				}
			}
			else if (enemyData[i].arahPattern_2 == 3)
			{
				bool gerak = true;
				for (int j = 0; j < tembokData.size(); j++) {
					if (abs(enemyData[i].posX - enemyData[i].velocity < tembokData[j].presentX + widthTembok - Tollerant2) && abs(enemyData[i].posX - enemyData[i].velocity + widthTembok - Tollerant2 > tembokData[j].presentX) && abs(enemyData[i].posY - enemyData[i].velocity < tembokData[j].presentY + heightTembok - Tollerant2) && abs(enemyData[i].posY - enemyData[i].velocity + heightTembok - Tollerant2 > tembokData[j].presentY)) {
						gerak = false;
						enemyData[i].arahPattern_2 = 0;
						break;
					}
				}
				if (gerak) {

					enemyData[i].posX -= enemyData[i].velocity;
					enemyData[i].posY -= enemyData[i].velocity;
				}
			}
			
		}
	}
	else if (patern == 2) {
		for (int  i = 0; i < enemyData.size(); i++)
		{
			float awalX = enemyData[i].posX;
			float awalY = enemyData[i].posY;

			if (enemyData[i].arah==0 || enemyData[i].arah == 2) {//X
				bool gerak = true;
				float vel = 0;
				int arah = enemyData[i].arah;

				if (arah==0) {
					vel = -enemyData[i].velocity;

				}
				else if (arah==2) {
					vel = enemyData[i].velocity;
				}

				for (int j = 0; j < tembokData.size(); j++)
				{
					if (abs(enemyData[i].posX+vel < tembokData[j].presentX + widthTembok - Tollerant) && abs(enemyData[i].posX+vel + widthTembok - Tollerant > tembokData[j].presentX) && abs(enemyData[i].posY < tembokData[j].presentY + heightTembok - Tollerant) && abs(enemyData[i].posY + heightTembok - Tollerant > tembokData[j].presentY)) {//ad collision/ nggk
						gerak = false;
						
						enemyData[i].nentuinArah();
						enemyData[i].posX = awalX;
						break;
					}
				}

				for (int j = 0; j < tembokInnerData.size(); j++)
				{
					if (abs(enemyData[i].posX + vel < tembokInnerData[j].presentX + widthTembok - Tollerant) && abs(enemyData[i].posX + vel + widthTembok - Tollerant > tembokInnerData[j].presentX) && abs(enemyData[i].posY < tembokInnerData[j].presentY + heightTembok - Tollerant) && abs(enemyData[i].posY + heightTembok - Tollerant > tembokInnerData[j].presentY)) {//ad collision/ nggk
						gerak = false;

						enemyData[i].nentuinArah();
						enemyData[i].posX = awalX;
						break;
					}
				}
				if (gerak==true) 
					enemyData[i].posX += vel;
			}
			else if (enemyData[i].arah == 1 || enemyData[i].arah ==3) {//ata
				bool gerak = true;
				float vel = 0;
				int arah = enemyData[i].arah;

				if (arah == 1) {
					vel = enemyData[i].velocity;
				}
				else if (arah == 3) {
					vel = -enemyData[i].velocity;
				}
				for (int j = 0; j < tembokData.size(); j++)
				{
					if (abs(enemyData[i].posX < tembokData[j].presentX + widthTembok - Tollerant) && abs(enemyData[i].posX + widthTembok - Tollerant > tembokData[j].presentX) && abs(enemyData[i].posY+vel < tembokData[j].presentY + heightTembok - Tollerant) && abs(enemyData[i].posY+vel + heightTembok - Tollerant > tembokData[j].presentY)) {
						gerak = false;
						
						enemyData[i].nentuinArah();
						enemyData[i].posY = awalY;
						break;
					}
				}

				for (int j = 0; j < tembokInnerData.size(); j++)
				{
					if (abs(enemyData[i].posX < tembokInnerData[j].presentX + widthTembok - Tollerant) && abs(enemyData[i].posX + widthTembok - Tollerant > tembokInnerData[j].presentX) && abs(enemyData[i].posY + vel < tembokInnerData[j].presentY + heightTembok - Tollerant) && abs(enemyData[i].posY + vel + heightTembok - Tollerant > tembokInnerData[j].presentY)) {
						gerak = false;

						enemyData[i].nentuinArah();
						enemyData[i].posY = awalY;
						break;
					}
				}

				if (gerak == true)
					enemyData[i].posY += vel;
			}
		
		}
		
	}

}

void mazeReader::pemainDraw() {
	for (int i = 0; i < pemainData.size();i++) {
		remiria.init(pemainX, pemainY, width, height);
	}
}

void mazeReader::enemyDraw() {
	for (int i = 0; i < enemyData.size(); i++) {
		furandure.init(enemyData[i].posX, enemyData[i].posY, width,height);
		enemyMove();
		if (loop > 700&& bloop==true) {
			revertEnemy *= -1;
			loop = 0;
			bloop = false;
		}
		else if (loop >1000 && bloop==false) {
			revertEnemy *= -1;
			loop = 0;
		}

	}

}

void mazeReader::tembokDraw() {
	for (int i = 0; i < tembokData.size(); i++)
	{
		wall.init(tembokData[i].presentX, tembokData[i].presentY, widthTembok, heightTembok);
	}
}

void mazeReader::tembokInnerDraw() {
	for (int i = 0; i < tembokInnerData.size(); i++)
	{
		wallInner.init(tembokInnerData[i].presentX, tembokInnerData[i].presentY, widthTembok, heightTembok);
	}
}

bool mazeReader::noMakananLeft() {
	if (countMakanan==0) {
		return true;
	}
	else
		return false;
}

void mazeReader::foodDraw() {
	for (int i = 0; i < makananData.size(); i++)
	{
		food.init(makananData[i].presentX, makananData[i].presentY, width, height);
	}
	if (noMakananLeft()) {
		countMakanan = jumMakanan;
		for (int i = 0; i < makananData.size(); i++)
		{
			makananData[i].presentX = makananData[i].posisiAwalX;
			makananData[i].presentY = makananData[i].posisiAwalY;
		}
	}
}

