#ifndef SKYBOX_H
#define SKYBOX_H

class Skybox
{
public:
	float x;
	float y;
	float z;
	int width;
	int height;
	int length;
	TextureImage texture_id;
	char* texture;

	Skybox(char* _texture);
	~Skybox() {};

	void Draw(float nx, float ny, float nz);
	void set_xyz(float _x, float _y, float _z);
	void set_whl(float _width, float _height, float _length);

};


#endif