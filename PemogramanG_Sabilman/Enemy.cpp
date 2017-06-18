#include "Enemy.h"


Enemy::Enemy() {

}
Enemy::Enemy(float x, float y)
{
	this->posX = x;
	this->posY = y;
	this->posAwalX = x;
	this->posAwalY = y;
	this->velocity = 0.001f;
	this->veloAwal = velocity;
	this->multiple = 1;
	this->arah = 1;
	this->arahPattern_2 = 0;
}


Enemy::~Enemy()
{

}

void Enemy::init(float x, float y, float w, float h) {
	_enemy.init(x, y, w, h,"furandure.png");
}

void Enemy::nentuinArah() {
	int hasil_rand = 0; 
	bool loop = true;
	while (loop) {
		hasil_rand= rand() % 4;
		if (hasil_rand != arah) {
			arah = hasil_rand;
			loop = false;
		}
	}
}
