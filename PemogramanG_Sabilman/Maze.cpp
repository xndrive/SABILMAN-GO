#include "Maze.h"

Maze::Maze()
{
}


Maze::~Maze()
{
}

void Maze::init(float x, float y, float w, float h) {
	maze.init(x,y,w,h,"");
	//maze.draw(1,1,1);
}
