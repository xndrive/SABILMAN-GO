#include "Demo.h"
#include <cstdlib>



#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Demo::Demo()
{
}


Demo::~Demo()
{
}

void Demo::enemyMoveFaster(float a) {
	for (int i = 0; i < read.enemyData.size(); i++)
	{
		read.enemyData[i].velocity = a;
	}
}

void Demo::changePatern(int a) {
	
	for (int i = 0; i < read.enemyData.size(); i++)
	{
		read.enemyData[i].velocity = 0.0009f;
	}
	read.patern = a;

}

void Demo::monitorLevel() {
	
	if (read.score==levelBase*1) {
		currentLevel = 2;
		enemyMoveFaster(0.002f);
		mul = 2;
	
	}
	else if(read.score == levelBase*2)
	{

		currentLevel = 3;
		moveAllInnerWall();
		for (int i = 0; i < read.enemyData.size(); i++)
		{
			read.enemyData[i].posX = read.enemyData[i].posAwalX;
			read.enemyData[i].posY = read.enemyData[i].posAwalY;
		}
		changePatern(1);
	}
	else if (read.score == levelBase*3) {
		currentLevel = 4;
		enemyMoveFaster(0.0013f);
	}
	else if(read.score == levelBase*4){
		currentLevel = 5;
		//Tollerant = -0.005;
		boolSizingMaze = true;
	}
	else if (read.score == levelBase*5) {
		currentLevel = 6;
		enemyMoveFaster(0.002f);
	}
	else if (read.score >= levelBase*6) {
		enemyMoveFaster(0.004f);
	}
}

void Demo::CekEnemyStuck() {
	float before;
	float after;
	int timer;
	for (int i = 0; i < read.enemyData.size(); i++)
	{
		if (read.enemyData[i].cek) {
			before = read.enemyData[i].posX;
			read.enemyData[i].cek=false;
			timer = 0;
		}
		else if (timer>3000) {
			read.enemyData[i].posX = 0;
			read.enemyData[i].posY = 0;
		}
		
	}
}

void Demo::sizingMaze(int a) {
	float limit = a *read.width;
	if (read.widthTembok<limit) {
		read.widthTembok += 0.00111f;
		read.heightTembok += 0.00111f;
	}
}

void Demo::Reset() {
	for (int i = 0; i < read.enemyData.size();i++) {
		read.enemyData[i].posX = read.enemyData[i].posAwalX;
		read.enemyData[i].velocity = read.enemyData[i].veloAwal;
		read.enemyData[i].posY = read.enemyData[i].posAwalY;
	}

	for (int i = 0; i < read.tembokInnerData.size(); i++) {
		read.tembokInnerData[i].presentX = read.tembokInnerData[i].posAwalX;
		read.tembokInnerData[i].presentY = read.tembokInnerData[i].posAwalY;
	}
	for (int i = 0; i < read.makananData.size(); i++) {
		read.makananData[i].presentX = read.makananData[i].posisiAwalX;
		read.makananData[i].presentY = read.makananData[i].posisiAwalY;
	}
	if (read.score > highscore) {
		highscore = read.score;
	}
	money += read.score;
	read.patern = 2;
	read.score = 0;
	read.score = 0;
	lives = 3;
	currentLevel = 1; 
	read.widthTembok = read.width;
	read.heightTembok = read.height;
	boolSizingMaze = false;
	SoundEngine->play2D(this->MP3NAME, true);
}


void Demo::moveAllInnerWall() {
	for (int i = 0; i <read.tembokInnerData.size() ; i++)
	{
		read.tembokInnerData[i].presentX = read.tembokInnerData[i].transX;
	}
}

bool Demo::getRepeat() {
	return this->repeat;
}

bool Demo::cekLives() {
	if (lives == 0) {
		SoundEngine->stopAllSounds();
		return true;
	}
	else
	{
		return false;
	}
}

void Demo::pemainKeEnemy() {
	
	if (bCekPemainKeEnemy) {
		for (int i = 0; i < read.enemyData.size(); i++) {
			if (abs(read.pemainX < read.enemyData[i].posX + read.width - (Tollerant * 2)) && abs(read.pemainX + read.width - (Tollerant * 2) > read.enemyData[i].posX) && abs(read.pemainY < read.enemyData[i].posY + read.height - (Tollerant * 2)) && abs(read.pemainY + read.height - (Tollerant * 2) > read.enemyData[i].posY)) {
				lives--;
				read.pemainX = 0.0f;
				read.pemainY = 0.0f;
				bCekPemainKeEnemy = false;
				SoundEngine->play2D(this->SFX2, false);

				if (lives == 0) {
					SoundEngine->stopAllSounds();
					GameOver();
					

				}
			}
		}
	}
	else {
		if (timerinvisible>3000) {
			bCekPemainKeEnemy = true;
			timerinvisible = 0;
		}
		else
			timerinvisible += 10;
	}
}

void Demo::moveEnemy() {
	read.enemyMove();
}

void Demo::movePemainX(float a) {
	float tempX = read.pemainX+a;
	float before = read.pemainX;
	bool gerak = true;
	for (int i = 0; i < read.tembokData.size(); i++)
	{
		if (abs(tempX < read.tembokData[i].presentX + read.width-Tollerant) && abs(tempX + read.width-Tollerant > read.tembokData[i].presentX) && abs(read.pemainY < read.tembokData[i].presentY + read.height-Tollerant) && abs(read.pemainY + read.height-Tollerant > read.tembokData[i].presentY)) {
			read.pemainX = before;
			gerak = false;
			break;
		}
	}

	for (int i = 0; i < read.tembokInnerData.size(); i++)
	{
		if (abs(tempX < read.tembokInnerData[i].presentX + read.width - Tollerant) && abs(tempX + read.width - Tollerant > read.tembokInnerData[i].presentX) && abs(read.pemainY < read.tembokInnerData[i].presentY + read.height - Tollerant) && abs(read.pemainY + read.height - Tollerant > read.tembokInnerData[i].presentY)) {
			read.pemainX = before;
			gerak = false;
			break;
		}
	}
	if (gerak) {
		read.pemainX += a*mul;
	}
}

void Demo::movePemainY(float a) {
	float tempY = read.pemainY + a;
	float before = read.pemainY;
	bool gerak = true;
	for (int i = 0; i < read.tembokData.size(); i++)
	{
		if (abs(read.pemainX < read.tembokData[i].presentX + read.width-Tollerant) && abs(read.pemainX + read.width-Tollerant > read.tembokData[i].presentX) && abs(tempY < read.tembokData[i].presentY + read.height-Tollerant) && abs(tempY + read.height-Tollerant > read.tembokData[i].presentY)) {
			read.pemainY = before;
			gerak = false;
			break;
		}
	}

	for (int i = 0; i < read.tembokInnerData.size(); i++)
	{
		if (abs(read.pemainX < read.tembokInnerData[i].presentX + read.width - Tollerant) && abs(read.pemainX + read.width - Tollerant > read.tembokInnerData[i].presentX) && abs(tempY < read.tembokInnerData[i].presentY + read.height - Tollerant) && abs(tempY + read.height - Tollerant > read.tembokInnerData[i].presentY)) {
			read.pemainY = before;
			gerak = false;
			break;
		}
	}
	if (gerak) {
		read.pemainY += a*mul;
	}
}

int Demo::getLives() {
	return lives;
}

int Demo::getHighscore() {
	return highscore;
}

int Demo::getScore() {
	return read.score;
}

int Demo::getMoney() {
	return money;
}

int Demo::getCurrentLevel() {
	return currentLevel;
}

void Demo::Init()
{
	
	glEnable(GL_TEXTURE_2D);
	BGM();
	read.getTextInfo();
	read.Read();

}

void Demo::Update(float deltaTime)
{
	if (boolSizingMaze) {
		sizingMaze(2);
		for (int i = 0; i < read.enemyData.size(); i++)
		{
			read.enemyData[i].velocity = 0.0009f;
		}
	}
	cekCollisionFood();
	pemainKeEnemy();
	
}

void Demo::cekCollisionFood() {
	for (int i = 0; i < read.makananData.size(); i++) {
		if (abs(read.pemainX < read.makananData[i].presentX + read.width - read.Tollerant2) && abs(read.pemainX + read.width - read.Tollerant2 > read.makananData[i].presentX) && abs(read.pemainY < read.makananData[i].presentY + read.height - read.Tollerant2) && abs(read.pemainY + read.height - read.Tollerant2 > read.makananData[i].presentY)) {
			read.makananData[i].presentX = read.makananData[i].transX;
			read.makananData[i].presentY = read.makananData[i].transY;
			read.countMakanan--;
			read.score++;
			SoundEngine->play2D(this->SFX1, false);
		}
	}
}

void Demo::Render()
{
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	read.drawObject();
	monitorLevel();
}

void Demo::BGM() {
	SoundEngine->play2D(this->MP3NAME, GL_TRUE);
}

void Demo::stopBGM() {
	SoundEngine->stopAllSounds();
}

int main(int argc, char** argv) {
	//Engine::Game &game = Demo();
	//game.Start("Bully the Charisma!!!", 800, 800, false, WindowFlag::WINDOWED, 120, 1);


	VideoMode videoMode(640, 480);
	RenderWindow window(videoMode, "Project Pemrograman Game");

	sf::Texture background;
	sf::Sprite backgroundImage;

	if (!background.loadFromFile("image/background.jpg"))
		std::cout << "Error: tidak dapat menampilkan gambar" << std::endl;

	backgroundImage.setTexture(background);

	sf::Texture texture;
	if (!texture.loadFromFile("image/tombol.png"))
	{
		return 1;
	}
	// load texture tombol
	sf::Sprite sprite;
	sprite.setPosition(220, 200);
	sprite.setTexture(texture);
	sprite.setScale(0.6f, 0.7f);

	sf::Sprite sprite1;
	sprite1.setPosition(220, 300);
	sprite1.setTexture(texture);
	sprite1.setScale(0.6f, 0.7f);

	RectangleShape rectangle;
	rectangle.setPosition(30, 30);
	rectangle.setSize(Vector2f(50, 30));

	rectangle.setFillColor(Color::Yellow);
	rectangle.setOutlineColor(Color::Blue);
	rectangle.setOutlineThickness(3);

	Font font;
	if (!font.loadFromFile("extra_fonts/Roboto-Medium.ttf")) {
		cout << "gagal";
	}

	Text text;

	text.setFont(font);
	text.setPosition(200, 50);
	text.setCharacterSize(50);
	text.setString("SABILMAN");
	text.setFillColor(sf::Color::Black);


	Text textMulai;

	textMulai.setFont(font);
	textMulai.setPosition(270, 210);
	textMulai.setCharacterSize(30);
	textMulai.setString("MULAI");
	textMulai.setFillColor(sf::Color::White);

	Text textKeluar;

	textKeluar.setFont(font);
	textKeluar.setPosition(260, 310);
	textKeluar.setCharacterSize(30);
	textKeluar.setString("KELUAR");
	textKeluar.setFillColor(sf::Color::White);

	sf::Vector2f mp;
	mp.x = sf::Mouse::getPosition(window).x;
	mp.y = sf::Mouse::getPosition(window).y;
	while (window.isOpen())

	{
		window.clear();
		window.draw(backgroundImage);
		window.draw(text);

		window.draw(sprite);
		window.draw(sprite1);
		window.draw(textMulai);
		window.draw(textKeluar);
		//window.draw(rectangle);
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) ||
				((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();
			else
			{

				if (event.type == Event::KeyPressed)
				{
					switch (event.key.code)
					{
					case Keyboard::Up: rectangle.move(0, -10);
						break;
					case Keyboard::Down: rectangle.move(0, 10);
						break;
					case Keyboard::Left: rectangle.move(-10, 0);
						break;
					case Keyboard::Right: rectangle.move(10, 0);
						break;
					}

				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					mp.x = sf::Mouse::getPosition(window).x;
					mp.y = sf::Mouse::getPosition(window).y;
					if (sprite.getGlobalBounds().contains(Vector2f(mp.x, mp.y))) {
						window.close();
						Engine::Game &game = Demo();
						game.Start("Sabilman", 800, 600, false, WindowFlag::WINDOWED, 120, 1);
						

		
					}
					if (sprite1.getGlobalBounds().contains(Vector2f(mp.x, mp.y))) {
							exit(0);

					}

				}
			}

		}
	}
	return 0;
}
int Demo::GameOver() {
	
	VideoMode videoMode(300, 200);
	RenderWindow window(videoMode, "Project Pemrograman Game");

	sf::Texture background;
	sf::Sprite backgroundImage;

	if (!background.loadFromFile("image/background.jpg"))
		std::cout << "Error: tidak dapat menampilkan gambar" << std::endl;

	backgroundImage.setTexture(background);

	sf::Texture texture;
	if (!texture.loadFromFile("image/tombol.png"))
	{
		return 1;
	}
	// load texture tombol
	sf::Sprite sprite;
	sprite.setPosition(20, 80);
	sprite.setTexture(texture);
	sprite.setScale(0.3f, 0.4f);

	sf::Sprite sprite1;
	sprite1.setPosition(150, 80);
	sprite1.setTexture(texture);
	sprite1.setScale(0.3f, 0.4f);



	Font font;
	if (!font.loadFromFile("extra_fonts/Roboto-Medium.ttf")) {
		cout << "gagal";
	}

	Text text;

	text.setFont(font);
	text.setPosition(60, 30);
	text.setCharacterSize(40);
	text.setString("Main Lagi?");
	text.setFillColor(sf::Color::Black);


	Text textMulai;

	textMulai.setFont(font);
	textMulai.setPosition(60, 80);
	textMulai.setCharacterSize(30);
	textMulai.setString("YA");
	textMulai.setFillColor(sf::Color::White);

	Text textKeluar;

	textKeluar.setFont(font);
	textKeluar.setPosition(150, 80);
	textKeluar.setCharacterSize(30);
	textKeluar.setString("TIDAK");
	textKeluar.setFillColor(sf::Color::White);

	sf::Vector2f mp;
	mp.x = sf::Mouse::getPosition(window).x;
	mp.y = sf::Mouse::getPosition(window).y;
	while (window.isOpen())

	{
		window.clear();
		window.draw(backgroundImage);
		window.draw(text);

		window.draw(sprite);
		window.draw(sprite1);
		window.draw(textMulai);
		window.draw(textKeluar);
		
		window.display();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) ||
				((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
				window.close();
			else
			{

				if (event.type == Event::KeyPressed)
				{
					switch (event.key.code)
					{
					
					}

				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					mp.x = sf::Mouse::getPosition(window).x;
					mp.y = sf::Mouse::getPosition(window).y;
					if (sprite.getGlobalBounds().contains(Vector2f(mp.x, mp.y))) {
						window.close();
						SDL_Quit();
						Engine::Game &game = Demo();
						game.Start("Sabilman", 800, 600, false, WindowFlag::WINDOWED, 120, 1);

					}
					if (sprite1.getGlobalBounds().contains(Vector2f(mp.x, mp.y))) {
							exit(0);

					}

				}
			}

		}
	}
	return 0;
}
