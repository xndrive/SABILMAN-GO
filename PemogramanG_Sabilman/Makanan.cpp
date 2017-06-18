#include "Makanan.h"


Makanan::Makanan() {

}

Makanan::Makanan(float a, float b)
{
	posisiAwalX = a;
	posisiAwalY = b;
	presentX = a;
	presentY = b;
	transX = 100.0f;
	transY = 100.0f;
}


Makanan::~Makanan()
{
}

void Makanan::init(float x, float y, float w, float h) {
	makanan.init(x, y, w, h,"food.png");
}
