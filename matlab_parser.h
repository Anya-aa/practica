#ifndef MATLAB_PARSER_H
#define MATLAB_PARSER_H 

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>

struct Drone_state
{
	float x, y, z, yaw, pitch, roll;
	Drone_state(float x_, float y_, float z_,
		float yaw_, float pitch_, float roll_)
		:x(x_), y(y_), z(z_),
		yaw(yaw_), pitch(pitch_), roll(roll_) {}
};

int scanner(FILE* file, char*& buff, bool& end);
int parser(std::vector<Drone_state>*& vec, const char* file_name);


#endif