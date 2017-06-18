#pragma once
#include "Object.h"
class Enemy: public Object
{
public:
	Object _enemy;
	Enemy();
	Enemy(float x, float y);
	~Enemy();
	float tempX, tempY;
	float posX, posY;
	float transX, transY;
	float posAwalX, posAwalY;
	float velocity, veloAwal, multiple;
	int arah, arahPattern_2;
	bool cek = true;

	void init(float x, float y, float w, float h);
	void nentuinArah();



};

