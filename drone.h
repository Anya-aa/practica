#ifndef DRONE_H
#define DRONE_H 

#include<vector>
#include "matlab_parser.h"
#include "texture.h"

struct Point_drone
{
	float x, y, z;
	Point_drone(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
};

class Drone
{
private:
	float x = 0, y = 0, z = 0;
	float yaw = 0, pitch = 0, roll = 0;
	float blade_rot = 0;
	float blade_speed = 5;
	bool trajectory;
	bool visible = true;

	int steps;
	GLint drone;
	GLint lopost;
	std::vector<Point_drone> traect;
	std::vector<Drone_state>* traect_MATLAB;

public:
	bool good = false;
	int time_late = 0;

	void set_xyz(float _x, float _y, float _z);
	void set_ypr(float _yaw, float _pitch, float _roll);
	void draw();
	void blade_step(float sp);
	void v_move(float dx, float dy, float dz);
	void abs_move(float abs_x, float abs_y, float abs_z);
	void draw_traect(float nx, float ny, float nz);

	void trajectory_fly_MATLAB(float _t);
	int trajectory_load(const char* filename);

	void set_d_l(GLint _drone, GLint _lopost);

	void load_texture_drone(char* _texture);
	TextureImage texture_id_drone;

	void load_texture_lopost(char* _texture);
	TextureImage texture_id_lopost;

	void clear_traect();
	void trajectory_str_get();


	Drone(GLint _drone, GLint _lopost);
	Drone();
	~Drone() {};
};

#endif
