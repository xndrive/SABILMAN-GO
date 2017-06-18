#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

using namespace std;
class Object
{
public:
	Object();
	~Object();
	void init(float x, float y, float width, float height, const char* loc);
	void draw(float r, float g, float b);
	unsigned char* image;
	void loadTexture(int a);

private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;
	GLuint texture, texture2;
};

