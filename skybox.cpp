#pragma comment(lib,"IL/DevIL.lib")
#pragma comment(lib,"IL/ilut.lib")
#pragma comment(lib,"IL/ilu.lib")

#include "texture.h"
#include "skybox.h"


Skybox::Skybox(char* _texture)
{
	CTexture* Texture = new CTexture();
	Texture->LoadTexture(IL_PNG, _texture, &texture_id);
}

void Skybox::Draw(float nx, float ny, float nz)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id.texID);
	glColor3f(1, 1, 1);

	float hx, hy, hz;
	hx = width / 2 + 10;
	hy = height / 2 + 10;
	hz = length / 2 + 10;

	float tret = 0.334f;
	float dret = 0.666f;
	float coeff = 0.002f;

	glNormal3f(-nx, -ny, -nz);
	glBegin(GL_QUADS);//front
	glTexCoord2f(0.25f, tret); glVertex3f(x - hx, y + hy, z - hz);
	glTexCoord2f(0.25f, dret); glVertex3f(x - hx, y - hy, z - hz);
	glTexCoord2f(0.50f, dret); glVertex3f(x + hx, y - hy, z - hz);
	glTexCoord2f(0.50f, tret); glVertex3f(x + hx, y + hy, z - hz);
	glEnd();

	glNormal3f(nx, ny, nz);
	glBegin(GL_QUADS);//back
	glTexCoord2f(1.00f, tret); glVertex3f(x - hx, y + hy, z + hz - hz * coeff);
	glTexCoord2f(1.00f, dret); glVertex3f(x - hx, y - hy, z + hz - hz * coeff);
	glTexCoord2f(0.75f, dret); glVertex3f(x + hx, y - hy, z + hz - hz * coeff);
	glTexCoord2f(0.75f, tret); glVertex3f(x + hx, y + hy, z + hz - hz * coeff);
	glEnd();

	glNormal3f(-nx, -ny, -nz);
	glBegin(GL_QUADS);//right
	glTexCoord2f(0.50f, tret); glVertex3f(x + hx, y + hy, z - hz);
	glTexCoord2f(0.50f, dret); glVertex3f(x + hx, y - hy, z - hz);
	glTexCoord2f(0.75f, dret); glVertex3f(x + hx, y - hy, z + hz);
	glTexCoord2f(0.75f, tret); glVertex3f(x + hx, y + hy, z + hz);
	glEnd();

	glNormal3f(nx, ny, nz);
	glBegin(GL_QUADS);//left
	glTexCoord2f(0.25f, tret); glVertex3f(x - hx, y + hy, z - hz);
	glTexCoord2f(0.25f, dret); glVertex3f(x - hx, y - hy, z - hz);
	glTexCoord2f(0.00f, dret); glVertex3f(x - hx, y - hy, z + hz);
	glTexCoord2f(0.00f, tret); glVertex3f(x - hx, y + hy, z + hz);
	glEnd();

	glNormal3f(-nx, -ny, -nz);
	glBegin(GL_QUADS);//top
	glTexCoord2f(0.25f, 0.0f); glVertex3f(x - hx, y + hy, z + hz + hz * coeff);
	glTexCoord2f(0.25f, tret); glVertex3f(x - hx, y + hy, z - hz);
	glTexCoord2f(0.50f, tret); glVertex3f(x + hx, y + hy, z - hz);
	glTexCoord2f(0.50f, 0.0f); glVertex3f(x + hx, y + hy, z + hz + hz * coeff);
	glEnd();

	glNormal3f(-nx, -ny, -nz);
	glBegin(GL_QUADS);//bottom
	glTexCoord2f(0.25f, dret); glVertex3f(x - hx, y - hy, z - hz);
	glTexCoord2f(0.25f, 1.00f); glVertex3f(x - hx, y - hy, z + hz + hz * coeff);
	glTexCoord2f(0.50f, 1.00f); glVertex3f(x + hx, y - hy, z + hz + hz * coeff);
	glTexCoord2f(0.50f, dret); glVertex3f(x + hx, y - hy, z - hz);
	glEnd();


	glDisable(GL_TEXTURE_2D);
}


void Skybox::set_xyz(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	return;
}

void Skybox::set_whl(float _width, float _height, float _length)
{
	width = _width;
	height = _height;
	length = _length;
	return;
}