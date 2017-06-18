#include "Pemain.h"


Pemain::Pemain()
{
}

Pemain::Pemain(float x, float y) {
	this->posX = x;
	this->posY = y;
	this->posAwalX = x;
	this->posAwalY = y;
}


Pemain::~Pemain()
{
}

void Pemain::init(float x, float y, float w, float h) {
	_pemain.init(x,y,w,h,"remiria.png");
	//_pemain.sprite("remiria.png");
	//_pemain.draw(0,1,0);
	
}




