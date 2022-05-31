#ifndef SURFACE_H
#define SURFACE_H 

#include <vector>
#include "texture.h"

struct Point_surface
{
	float x, y, z;
	Point_surface(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
};

class Surface
{
private:
	float x = 0, y = 0, z = 0;
	float yaw = 0, pitch = 0, roll = 0;
	bool visible = true;
	GLint surface;

public:
	void set_surface_xyz(float _x, float _y, float _z);
	void set_surface_ypr(float _yaw, float _pitch, float _roll);
	void draw();

	void set_s(GLint _surface);

	void load_texture_surface(char* _texture);
	TextureImage texture_id_surface;

	Surface(GLint _surface);
	Surface();
	~Surface() {};
};

#endif