#pragma once
#include "object.h"
class Tembok
{
public:
	Object tembok;
	float presentX, presentY;
	float posAwalX, posAwalY;
	float transX, transY;
	Tembok();
	Tembok(float x, float y);
	~Tembok();

	void init(float x, float y, float w, float h);
};

