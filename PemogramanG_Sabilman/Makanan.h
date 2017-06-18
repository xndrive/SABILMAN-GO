#pragma once
#include "Object.h"

class Makanan
{
public:
	Object makanan;
	float posisiAwalX;
	float posisiAwalY;
	float transX;
	float transY;
	float presentX, presentY;

	Makanan();
	Makanan(float a, float b);
	~Makanan();

	void init(float x, float y, float w, float h);
};

