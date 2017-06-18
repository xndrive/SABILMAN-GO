#include "Object.h"


Object::Object()
{
	_vboID = 0;
}


Object::~Object()
{
	if (_vboID!=0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Object::loadTexture(int a) {
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

										   // Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
	int widthI, heightI;

	if (a== 1) {
		image = SOIL_load_image("image/join2.png", &widthI, &heightI, 0, SOIL_LOAD_RGBA);
	}
	else if (a==2) {
		image = SOIL_load_image("image/join.png", &widthI, &heightI, 0, SOIL_LOAD_RGBA);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthI, heightI, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Object::init(float x, float y, float width, float height,const char* loc) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (loc=="") {
		glBegin(GL_QUADS);
		glVertex2f(x + width / 2, y + height / 2);
		glVertex2f(x - width / 2, y + height / 2);
		glVertex2f(x - width / 2, y - height / 2);
		glVertex2f(x + width / 2, y - height / 2);
		glEnd();
	}
	else if(loc=="remiria.png"){
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.33f, 0.0f); glVertex3f(x + width / 2, y + height / 2,0);
		glTexCoord2f(0.0f, 0.0f);  glVertex3f(x - width / 2, y + height / 2,0);
		glTexCoord2f(0.0f, 1.0f);  glVertex3f(x - width / 2, y - height / 2,0);
		glTexCoord2f(0.33f, 1.0f); glVertex3f(x + width / 2, y - height / 2,0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (loc=="furandure.png") {
		
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.68f, 0.0f); glVertex3f(x + width / 2, y + height / 2, 0);
		glTexCoord2f(0.38f, 0.0f); glVertex3f(x - width / 2, y + height / 2, 0);
		glTexCoord2f(0.38f, 1.0f); glVertex3f(x - width / 2, y - height / 2, 0);
		glTexCoord2f(0.68f, 1.0f); glVertex3f(x + width / 2, y - height / 2, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (loc=="food.png") {
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(x + width / 2, y + height / 2, 0);
		glTexCoord2f(0.68f, 0.0f);  
		glVertex3f(x - width / 2, y + height / 2, 0);
		glTexCoord2f(0.68f, 1.0f); 
		glVertex3f(x - width / 2, y - height / 2, 0);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(x + width / 2, y - height / 2, 0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	/*if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	float vertexData[8];
	vertexData[0] = x + width/2; //0 0.6
	vertexData[1] = y + height/2; //1 0.1
	vertexData[2] = x - width / 2; //2 -0.6
	vertexData[3] = y + height / 2; //3 
	vertexData[4] = x - width / 2;//4
	vertexData[5] = y - height / 2;//5
	vertexData[6] = x + width / 2;//6
	vertexData[7] = y - height / 2;//7

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
}

void Object::draw(float r, float g, float b) {
	glColor3f(r,g,b);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0,0);
	glDrawArrays(GL_QUADS, 0, 8);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*void Object::sprite(char *loc) {
	texture[0] = SOIL_load_OGL_texture
	(
		loc,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	if (texture[0] == 0) {
		cout << "texture tidak ada";
	}

	else {
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}*/
