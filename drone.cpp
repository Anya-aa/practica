#include "GL/freeglut.h"
#include "drone.h"
#include "matlab_parser.h"
#include "texture.h"

extern bool diagram;
bool isEnd = true;

Drone::Drone(GLint _drone, GLint _lopost)
{
	drone = _drone;
	lopost = _lopost;
	steps = -1;
	return;
}

Drone::Drone()
{
	steps = -1;
}

void Drone::set_xyz(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	return;
}

void Drone::set_ypr(float _yaw, float _pitch, float _roll)
{
	yaw = _yaw;
	pitch = _pitch;
	roll = _roll;
	return;
}

void Drone::set_d_l(GLint _drone, GLint _lopost)
{
	drone = _drone;
	lopost = _lopost;
	return;
}

void Drone::draw()
{

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture_id_drone.texID);

	glColor3f(1, 1, 1);
	glPushMatrix();

	glTranslatef(x, y, z);

	glRotatef(pitch * 90, 1, 0, 0);
	glRotatef(yaw * 90, 0, 1, 0);
	glRotatef(roll * 90, 0, 0, 1);

	glCallList(drone);

	glBindTexture(GL_TEXTURE_2D, texture_id_lopost.texID);

	glColor3f(1, 1, 1);

	////////////////////////////// ДРОНЫ-ВОДОМЕРКИ /////////////////////////////////////
	/*
	glPushMatrix();
	glTranslatef(-3.47, 0.40, 6.21);
	glRotatef(blade_rot, 0, 1, 0);
	glCallList(lopost);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.15, 0.40, -6.33);
	glRotatef(blade_rot, 0, 1, 0);
	glCallList(lopost);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.27, 0.40, -6.23);
	glRotatef(blade_rot, 0, 1, 0);
	glCallList(lopost);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.05, 0.40, 6.40);
	glRotatef(blade_rot, 0, 1, 0);
	glCallList(lopost);
	glPopMatrix();
	*/
	/////////////////////////////////////////////////////////////////////////////////

	/// Чтобы заменить обычных дронов на водомерок надо закоментировать одних, а вторыйх раскмоентировать и поменять название .obj файлов лопости и дрона в main

	/////////////////////////////////// Дроны ///////////////////////////////////////

	glPushMatrix();
	glTranslatef(-4.30, 0.5, 2.60);
	glRotatef(blade_rot, 0, 1, 0);
	glCallList(lopost);
	glRotatef(90, 0, -1, 0); /// раскометить все 4 лопости что бы они были крестовые
	glCallList(lopost);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.30, -0.1, -2.60);
	glRotatef(blade_rot, 0, 1, 0);
	glCallList(lopost);
	glRotatef(90, 0, -1, 0);
	glCallList(lopost);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.35, -0.05, -2.65);
	glRotatef(blade_rot, 0, -1, 0);
	glCallList(lopost);
	glRotatef(90, 0, -1, 0);
	glCallList(lopost);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.40, 0.5, 2.60);
	glRotatef(blade_rot, 0, -1, 0);
	glCallList(lopost);
	glRotatef(90, 0, -1, 0);
	glCallList(lopost);
	glPopMatrix();

	///////////////////////////////////////////////////////////////////////////////////////////
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	return;
}

void Drone::blade_step(float sp) /// шаг вращения лопости
{
	blade_rot += blade_speed * sp;
	if (blade_speed < 75057.250000)
		blade_speed += y;
	return;
}

void Drone::v_move(float dx, float dy, float dz) /// векторное движение
{
	traect.push_back(Point_drone(x, y, z));
	x += dx;
	y += dy;
	z += dz;
	return;
}

void Drone::abs_move(float abs_x, float abs_y, float abs_z) /// абсолютное движение (по точкам)
{
	x = abs_x;
	y = abs_y;
	z = abs_z;
	traect.push_back(Point_drone(x, y, z));
	return;
}

void Drone::draw_traect(float nx, float ny, float nz)
{
	glNormal3f(-nx, -ny, -nz);
	glLineWidth(2.5);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	for (auto i : traect)
	{
		glVertex3f(i.x, i.y, i.z);
		if (i.y >= 625 && i.x >= 380 && isEnd == true) {
			diagram = !diagram;
			isEnd = false;
		}
	}
	glEnd();
}

void Drone::trajectory_fly_MATLAB(float _t)
{
	float t = _t - time_late;

	if (t < 0)
		t = 0;

	if (!good)
		return;

	if (t > steps - 2) // НЕ ТРОГАТЬ (ФИКСЕТ КРАШ ПРОГИ ПОСЛЕ КОНЦА ЧТЕНИЯ ТРАЕТОРИИ ИЗ ФАЙЛА)
		return;

	float x, y, z;
	float xi, yi, zi;
	float yaw, pitch, roll;
	float yawi, pitchi, rolli;
	int pos = t;

	xi = (*traect_MATLAB)[pos + 1].x - (*traect_MATLAB)[pos].x;
	yi = (*traect_MATLAB)[pos + 1].y - (*traect_MATLAB)[pos].y;
	zi = (*traect_MATLAB)[pos + 1].z - (*traect_MATLAB)[pos].z;

	x = (*traect_MATLAB)[pos].x + xi * (t - (float)pos);
	y = (*traect_MATLAB)[pos].y + yi * (t - (float)pos);
	z = (*traect_MATLAB)[pos].z + zi * (t - (float)pos);

	yawi = (*traect_MATLAB)[pos + 1].yaw - (*traect_MATLAB)[pos].yaw;
	pitchi = (*traect_MATLAB)[pos + 1].pitch - (*traect_MATLAB)[pos].pitch;
	rolli = (*traect_MATLAB)[pos + 1].roll - (*traect_MATLAB)[pos].roll;

	yaw = (*traect_MATLAB)[pos].yaw + yawi * (t - (float)pos);
	pitch = (*traect_MATLAB)[pos].pitch + pitchi * (t - (float)pos);
	roll = (*traect_MATLAB)[pos].roll + rolli * (t - (float)pos);

	//printf("%.3f %d %d %.1f %.1f %.1f \n", t, (int) t, pos, x, y, z); /// отладка чтения коррдинат траектории
	set_ypr(yaw, pitch, roll);
	abs_move(x, y, z);

	return;
}

int Drone::trajectory_load(const char* filename)
{
	int res = parser(traect_MATLAB, filename);
	if (res < 0)
		good = false;
	else
		good = true;
	steps = res;
	return res;
}

void Drone::load_texture_drone(char* _texture)
{
	printf("Drone: texture (%s) loading...\n", _texture);
	CTexture* Texture = new CTexture();
	Texture->LoadTexture(IL_JPG, _texture, &texture_id_drone);
	printf("---Complete---\n");
}

void Drone::load_texture_lopost(char* _texture)
{
	printf("Drone prop: texture (%s) loading...\n", _texture);
	CTexture* Texture = new CTexture();
	Texture->LoadTexture(IL_JPG, _texture, &texture_id_lopost);
	printf("---Complete---\n");
}

void Drone::clear_traect()
{
	traect.clear();
}

void Drone::trajectory_str_get()
{
	printf("%+.5f\t%+.5f\t%+.5f\t%+.5f\t%+.5f\t%+.5f\n", x, y, z, yaw, pitch, roll);
	return;
}