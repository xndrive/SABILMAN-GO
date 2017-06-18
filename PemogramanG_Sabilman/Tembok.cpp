#include "Tembok.h"



Tembok::Tembok()
{
}

Tembok::Tembok(float x, float y) {
	presentX = x;
	presentY = y;
	posAwalX = x;
	posAwalY = y;
	transX = 100.f;
	transY = 100.f;

}

Tembok::~Tembok()
{

}

void Tembok::init(float x, float y, float w, float h) {
	tembok.init(x, y, w, h,"");
}
