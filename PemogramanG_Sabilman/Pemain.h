#pragma once
#include "Object.h"
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

using namespace std;

class Pemain : public Object
{
public:
	Object _pemain;
	GLuint texture[1];
	float posX, posY;
	float posAwalX, posAwalY;
	Pemain();
	Pemain(float x, float y);
	~Pemain();
	void init(float x, float y, float w, float h);
	void move();
	void sprite();
};

