#include "GL/freeglut.h"
#include "surface.h"
#include "texture.h"

Surface::Surface(GLint _surface)
{
	surface = _surface;
	return;
}

Surface::Surface()
{
	//
}

void Surface::set_surface_xyz(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	return;
}

void Surface::set_surface_ypr(float _yaw, float _pitch, float _roll)
{
	yaw = _yaw;
	pitch = _pitch;
	roll = _roll;
	return;
}

void Surface::set_s(GLint _surface)
{
	surface = _surface;
	return;
}

void Surface::draw()
{

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture_id_surface.texID);

	glColor3f(1, 1, 1);
	glPushMatrix();

	glTranslatef(x, y, z);

	glRotatef(pitch, 1, 0, 0);
	glRotatef(yaw, 0, 1, 0);
	glRotatef(roll, 0, 0, 1);

	glScalef(2, 2, 2);

	glCallList(surface);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	return;
}

void Surface::load_texture_surface(char* _texture)
{
	printf("Surface: texture (%s) loading...\n", _texture);
	CTexture* Texture = new CTexture();
	Texture->LoadTexture(IL_JPG, _texture, &texture_id_surface);
	printf("---Complete---\n");
	return;
}
