#include <iostream>
#include "GL/freeglut.h"
#include "GL/GLAux.h"
#include "drone.h"
#include "gl_func.h"
#include "camera.h"
#include "matlab_parser.h"
#include "texture.h"
#include "skybox.h"
#include "surface.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#define PI (3.1415926)

int const WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;

extern double rotateX_medium, rotateY_medium, rotateX_small, rotateY_small;
double x1 = 0, x2 = 0, x3 = 0, x4 = 0, y_1 = 0, y2 = 0, y3 = 0, y4 = 0, z1 = 0, z2 = 0, z3 = 0, z4 = 0, n1 = 0, n2 = 0, n3 = 0;

CCamera g_Camera;


int resize = 300;
int resize_len = 80;
int resize_main = 150;
extern float resize_medium_left;
extern float resize_medium_right;
extern float resize_medium_len_left;
extern float resize_medium_len_right;
extern float resize_small_left;
extern float resize_small_right;
extern float resize_small_len_right;
extern float resize_small_len_left;
extern bool diagram;
extern bool isPressed;
extern bool isHeight;
extern bool isRotate;
extern double rotateX;
extern double rotateY;

extern bool reset_b;
extern bool stop_b;
extern bool debug_coords;
extern float t_del;
extern bool zaderska;
extern bool surface_on;
extern bool traect_on;
extern bool isEnd;

int DRONES;

float t = 0;

GLint d, l, s, g, h;

#pragma warning(disable:4996)

double func(double x)
{
	return sin((10 - x) / 9 * PI / 2);
}

double func2(double x) {
	return sqrt(2 * x - (x * x));
}

void func3(float resize_temp)
{
	for (double x = 0.0; x <= 10.0; x += 0.1) {
		if (x > 1) {
			for (double ang = 0; ang <= 360; ang += 5) {
				double angle = 2.0 * 3.1415926 * ang / 360.0;
				double dy = func(x) * cos(angle) * resize_temp;
				double dz = func(x) * sin(angle) * resize_temp;
				x1 = 10 - x;
				y_1 = dy;
				z1 = dz + 280;
				if (x + 0.1 < 10) {
					angle = 2.0 * 3.1415926 * ang / 360.0;
					dy = func(x + 0.1) * cos(angle) * resize_temp;
					dz = func(x + 0.1) * sin(angle) * resize_temp;
					x2 = 9.9 - x;
					y2 = dy;
					z2 = dz + 280;

					if (ang + 5 < 360) {

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func(x + 0.1) * cos(angle) * resize_temp;
						dz = func(x + 0.1) * sin(angle) * resize_temp;
						x3 = 9.9 - x;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func(x) * cos(angle) * resize_temp;
						dz = func(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
					else {
						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func(x + 0.1) * cos(angle) * resize_temp;
						dz = func(x + 0.1) * sin(angle) * resize_temp;
						x3 = 9.9 - x;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func(x) * cos(angle) * resize_temp;
						dz = func(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
				}
				else {
					angle = 2.0 * 3.1415926 * ang / 360.0;
					dy = func(x + 0.1) * cos(angle) * resize_temp;
					dz = func(x + 0.1) * sin(angle) * resize_temp;
					x2 = 0;
					y2 = dy;
					z3 = dz + 280;

					if (ang + 5 < 360) {

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func(x + 0.1) * cos(angle) * resize_temp;
						dz = func(x + 0.1) * sin(angle) * resize_temp;
						x3 = 0;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func(x) * cos(angle) * resize_temp;
						dz = func(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
					else {
						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func(x + 0.1) * cos(angle) * resize_temp;
						dz = func(x + 0.1) * sin(angle) * resize_temp;
						x3 = 0;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func(x) * cos(angle) * resize_temp;
						dz = func(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
				}
				if (x == 0.0) {
					n1 = (y2 - y_1)*(z3 - z1) - (y3 - y_1)*(z2 - z1);
					n2 = (z2 - z1)* (x3 - x1) - (z3 - z1) *(x2 - x1);
					n3 = (x2 - x1)* (y3 - y_1) - (x3 - x1)*(y2 - y_1);
				}
				else {
					n1 = (y4 - y3)*(z1 - z3) - (y_1 - y3)*(z4 - z3);
					n2 = (z4 - z3)*(x1 - x3) - (z1 - z3)*(x4 - x3);
					n3 = (x4 - x3)*(y_1 - y3) - (x1 - x3)*(y4 - y3);
				}
				double n5 = sqrt(n1*n1 + n2*n2 + n3*n3);
				n1 /= (n5 + 0.01);
				n2 /= (n5 + 0.01);
				n3 /= (n5 + 0.01);
				glNormal3d(n1, n2, n3);

				glVertex3f(x1, y_1 + 525, z1);
				glVertex3f(x2, y2 + 525, z2);
				glVertex3f(x3, y3 + 525, z3);
				glVertex3f(x4, y4 + 525, z4);

			}
		}
		else {
			for (double ang = 0; ang <= 360; ang += 5) {
				double angle = 2.0 * 3.1415926 * ang / 360.0;
				double dy = func2(x) * cos(angle) * resize_temp;
				double dz = func2(x) * sin(angle) * resize_temp;
				x1 = 10 - x;
				y_1 = dy;
				z1 = dz + 280;

				if (x + 0.1 < 10) {
					angle = 2.0 * 3.1415926 * ang / 360.0;
					dy = func2(x + 0.1) * cos(angle) * resize_temp;
					dz = func2(x + 0.1) * sin(angle) * resize_temp;
					x2 = 9.9 - x;
					y2 = dy;
					z2 = dz + 280;

					if (ang + 5 < 360) {

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func2(x + 0.1) * cos(angle) * resize_temp;
						dz = func2(x + 0.1) * sin(angle) * resize_temp;
						x3 = 9.9 - x;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func2(x) * cos(angle) * resize_temp;
						dz = func2(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
					else {
						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func2(x + 0.1) * cos(angle) * resize_temp;
						dz = func2(x + 0.1) * sin(angle) * resize_temp;
						x3 = 9.9 - x;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func2(x) * cos(angle) * resize_temp;
						dz = func2(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;

					}
				}
				else {
					angle = 2.0 * 3.1415926 * ang / 360.0;
					dy = func2(x + 0.1) * cos(angle) * resize_temp;
					dz = func2(x + 0.1) * sin(angle) * resize_temp;
					x2 = 0;
					y2 = dy;
					z2 = dz + 280;

					if (ang + 5 < 360) {

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func2(x + 0.1) * cos(angle) * resize_temp;
						dz = func2(x + 0.1) * sin(angle) * resize_temp;
						x3 = 0;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
						dy = func2(x) * cos(angle) * resize_temp;
						dz = func2(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
					else {
						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func2(x + 0.1) * cos(angle) * resize_temp;
						dz = func2(x + 0.1) * sin(angle) * resize_temp;
						x3 = 0;
						y3 = dy;
						z3 = dz + 280;

						angle = 2.0 * 3.1415926 * 0 / 360.0;
						dy = func2(x) * cos(angle) * resize_temp;
						dz = func2(x) * sin(angle) * resize_temp;
						x4 = 10 - x;
						y4 = dy;
						z4 = dz + 280;
					}
				}
				if (x == 0.0) {
					n1 = (y2 - y_1)*(z3 - z1) - (y3 - y_1)*(z2 - z1);
					n2 = (z2 - z1)* (x3 - x1) - (z3 - z1) *(x2 - x1);
					n3 = (x2 - x1)* (y3 - y_1) - (x3 - x1)*(y2 - y_1);
				}
				else {
					n1 = (y4 - y3)*(z1 - z3) - (y_1 - y3)*(z4 - z3);
					n2 = (z4 - z3)*(x1 - x3) - (z1 - z3)*(x4 - x3);
					n3 = (x4 - x3)*(y_1 - y3) - (x1 - x3)*(y4 - y3);
				}
				double n5 = sqrt(n1*n1 + n2*n2 + n3*n3);
				n1 /= (n5 + 0.01);
				n2 /= (n5 + 0.01);
				n3 /= (n5 + 0.01);
				glNormal3d(n1, n2, n3);

				glVertex3f(x1, y_1 + 525, z1);
				glVertex3f(x2, y2 + 525, z2);
				glVertex3f(x3, y3 + 525, z3);
				glVertex3f(x4, y4 + 525, z4);

			}
		}
	}
}

int main(int argc, char** argv)
{

	/////////////////////////////////////////////////////////  СКАНЕР ДИРЕКТОРИИ  //////////////////////////////////////////////////////////////////////////////////////
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	std::vector<char*> traect_files;
	DRONES = 0;

	char start[256];
	printf("Enter the way to the directory: ");
	std::cin >> start;
	int b_e = strlen(start);
	start[b_e] = '\\';
	start[b_e + 1] = '*';
	start[b_e + 2] = '\0';

	hf = FindFirstFile(start, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		printf("Start searching files in a directory...\n");
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//
			}
			else
			{
				char* buf;
				buf = (char*)calloc(strlen(FindFileData.cFileName) + 1 + strlen(start), sizeof(char));
				strcpy(buf, start);
				strcpy(&buf[strlen(start) - 1], (FindFileData.cFileName));
				traect_files.push_back(buf);
				DRONES++;
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}


	printf("Files detected: %d\n", DRONES);

	if (DRONES == 0)
		exit(0);

	for (auto i : traect_files)
	{
		printf("%s\n", i);
	}

	printf("---Complete---\n");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	t_del = 1;

	g_Camera.scenario = 1;
	gl_initialization(argc, argv);

	create_list_global(d, "obj/UAV_and_antenna_1.obj");
	create_list_global(l, "obj/lopost.obj");
	create_list_global(s, "obj/mount.obj");  /// загрузка 3D моделей
	create_list_global(g, "obj/grass.obj");
	create_list_global(h, "obj/truck.obj");
	
	//////////////////////////// Окружение ////////////////////////////

	Surface surface[9];

	surface[0].set_s(g);
	surface[1].set_s(s);

	surface[0].load_texture_surface((char*)"texture_image/grass.jpg");
	surface[1].load_texture_surface((char*)"texture_image/rock_mount.jpg"); /// загрузка текстур
	surface[2].load_texture_surface((char*)"texture_image/military.jpg");


	surface[2].set_s(h);
	surface[2].set_surface_xyz(0, -22, 15); /// положение грузовика

											//////////////////////////////////////////////////////////////////

											///////////////////////////// Дроны /////////////////////////////
	Drone* drones;
	drones = new Drone[DRONES];
	float drone_lates = 200;

	for (int i = 0; i < DRONES; i++)
	{
		drones[i].set_d_l(d, l);
	}


	for (int i = 0; i < DRONES; i++)
	{
		drones[i].load_texture_drone((char*)"texture_image/metal_drone.jpg");
		drones[i].load_texture_lopost((char*)"texture_image/aluminum_lopost.jpg");
	}

	int strs = 0;
	int time_max = 0;
	int sup;
	for (int i = 0; i < DRONES; i++)
	{
		strs = drones[i].trajectory_load(traect_files[i]);
		time_max = (time_max < strs) ? strs : time_max;
	}

	///////////////////////////////////////////////////////////////

	Skybox Skybox((char*)"texture_image/skybox_day.png");
	//Skybox Skybox((char*)"texture_image/skybox_night.png"); // ночное небо
	Skybox.set_whl(10000, 10000, 10000);
	Skybox.set_xyz(g_Camera.Position().x, g_Camera.Position().y, g_Camera.Position().z);

	while (1)
	{
		if (zaderska)
			sup = time_max + (DRONES - 1) * drone_lates;
		else
			sup = time_max;

		if (t < 0)
			t = 0;

		if (t > sup)
			t = sup;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (g_Camera.scenario == 1)
		{
			g_Camera.PositionCamera(260, 39, 28, 255, 37, 25, 0, 1, 0);
			g_Camera.scenario = 0;
		}
		else
			if (g_Camera.scenario == 2)
			{
				g_Camera.PositionCamera(229, 139, -197, 195, 110, -156, 0, 1, 0);
				g_Camera.scenario = 0;
			}
			else
				if (g_Camera.scenario == 3)
				{
					g_Camera.PositionCamera(184, 73, 206, 184, 73, 201, 0, 1, 0);
					g_Camera.PositionCamera(13, 13, -67, 12, 12, -62, 0, 1, 0);
					g_Camera.scenario = 0;
				}
				else
				{
					g_Camera.SetViewByMouse(t);
				}
		g_Camera.Look();

		for (int i = 0; i < DRONES; i++)
		{
			if (zaderska)
				drones[i].time_late = i * drone_lates;
			else
				drones[i].time_late = 0;
			drones[i].trajectory_fly_MATLAB(t);
		}

		for (int i = 0; i < DRONES; i++)
		{
			if (drones[i].good)
			{
				drones[i].draw();
				if (stop_b)
					drones[i].blade_step(t_del);
				if (traect_on)
					drones[i].draw_traect(g_Camera.View().x - g_Camera.Position().x, g_Camera.View().y - g_Camera.Position().y, g_Camera.View().z - g_Camera.Position().z);
			}
		}

		float vicota = 35;
		float vicota_100 = -120; /// переменные для настройки положения гор и травы
		float vdal = 100;

		if (reset_b)
		{
			t = 0;
			for (int i = 0; i < DRONES; i++)
			{
				drones[i].clear_traect();
			}
			diagram = false;
			isEnd = true;
			reset_b = false;
		}

		if (surface_on)
		{

			surface[2].set_surface_ypr(-2, 0, 0);
			surface[2].set_surface_ypr(-5, 0, 0);
			surface[2].draw();

			surface[0].set_surface_xyz(-10, -35, -50);
			surface[0].draw();

			///////////////////////////////////  ГОРЫ  /////////////////////////////////////
			surface[1].set_surface_xyz(-1020, vicota, 40);//лев 
			surface[1].set_surface_ypr(0, 0, 0);
			surface[1].draw();

			surface[1].set_surface_xyz(1020, vicota, 40);//прав 
			surface[1].set_surface_ypr(0, 0, 0);
			surface[1].draw();

			surface[1].set_surface_xyz(0, vicota, -1100);//впереди
			surface[1].set_surface_ypr(255, 0, 0);
			surface[1].draw();

			surface[1].set_surface_xyz(0, vicota, 990);//за нами
			surface[1].set_surface_ypr(75, 0, 0);
			surface[1].draw();
			//////////////////////////////////////////////////////////////////////////////
		}

		Skybox.set_xyz(g_Camera.Position().x, g_Camera.Position().y, g_Camera.Position().z);
		Skybox.Draw(g_Camera.View().x - g_Camera.Position().x, g_Camera.View().y - g_Camera.Position().y, g_Camera.View().z - g_Camera.Position().z);

		//////////////////////////////////////////////////////////////   Расчет векторов и построение диаграммы   ///////////////////////////////////////////////////////////////////////////////////////////////

		if (diagram) {
			glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateY, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateX, 1.0, 0.0, 1.0);
			glTranslatef(0, -525, -280);
			glColor3f(1, 0, 0);
			glPointSize(40.0);
			glBegin(GL_LINES);
			glVertex3f(0.0, 525, 280);
			glVertex3f(1300, 525, 280);
			glEnd();
			glPointSize(5.0);
			glColor4f(0.0, 1.0, 1.0, 0.3);
			glScalef(resize_len, 1, 1);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			for (double x = 0.0; x <= 10.0; x += 0.1) {
				if (x > 1) {
					for (double ang = 0; ang <= 360; ang += 5) {
						double angle = 2.0 * 3.1415926 * ang / 360.0;
						double dy = func(x) * cos(angle) * resize;
						double dz = func(x) * sin(angle) * resize;
						x1 = 10 - x;
						y_1 = dy;
						z1 = dz + 280;
						if (x + 0.1 < 10) {
							angle = 2.0 * 3.1415926 * ang / 360.0;
							dy = func(x + 0.1) * cos(angle) * resize;
							dz = func(x + 0.1) * sin(angle) * resize;
							x2 = 9.9 - x;
							y2 = dy;
							z2 = dz + 280;

							if (ang + 5 < 360) {

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func(x + 0.1) * cos(angle) * resize;
								dz = func(x + 0.1) * sin(angle) * resize;
								x3 = 9.9 - x;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func(x) * cos(angle) * resize;
								dz = func(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
							else {
								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func(x + 0.1) * cos(angle) * resize;
								dz = func(x + 0.1) * sin(angle) * resize;
								x3 = 9.9 - x;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func(x) * cos(angle) * resize;
								dz = func(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
						}
						else {
							angle = 2.0 * 3.1415926 * ang / 360.0;
							dy = func(x + 0.1) * cos(angle) * resize;
							dz = func(x + 0.1) * sin(angle) * resize;
							x2 = 0;
							y2 = dy;
							z3 = dz + 280;

							if (ang + 5 < 360) {

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func(x + 0.1) * cos(angle) * resize;
								dz = func(x + 0.1) * sin(angle) * resize;
								x3 = 0;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func(x) * cos(angle) * resize;
								dz = func(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
							else {
								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func(x + 0.1) * cos(angle) * resize;
								dz = func(x + 0.1) * sin(angle) * resize;
								x3 = 0;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func(x) * cos(angle) * resize;
								dz = func(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
						}
						if (x == 0.0) {
							n1 = (y2 - y_1)*(z3 - z1) - (y3 - y_1)*(z2 - z1);
							n2 = (z2 - z1)* (x3 - x1) - (z3 - z1) *(x2 - x1);
							n3 = (x2 - x1)* (y3 - y_1) - (x3 - x1)*(y2 - y_1);
						}
						else {
							n1 = (y4 - y3)*(z1 - z3) - (y_1 - y3)*(z4 - z3);
							n2 = (z4 - z3)*(x1 - x3) - (z1 - z3)*(x4 - x3);
							n3 = (x4 - x3)*(y_1 - y3) - (x1 - x3)*(y4 - y3);
						}
						double n5 = sqrt(n1*n1 + n2*n2 + n3*n3);
						n1 /= (n5 + 0.01);
						n2 /= (n5 + 0.01);
						n3 /= (n5 + 0.01);
						glNormal3d(n1, n2, n3);

						glVertex3f(x1, y_1 + 525, z1);
						glVertex3f(x2, y2 + 525, z2);
						glVertex3f(x3, y3 + 525, z3);
						glVertex3f(x4, y4 + 525, z4);

					}
				}
				else {
					for (double ang = 0; ang <= 360; ang += 5) {
						double angle = 2.0 * 3.1415926 * ang / 360.0;
						double dy = func2(x) * cos(angle) * resize;
						double dz = func2(x) * sin(angle) * resize;
						x1 = 10 - x;
						y_1 = dy;
						z1 = dz + 280;

						if (x + 0.1 < 10) {
							angle = 2.0 * 3.1415926 * ang / 360.0;
							dy = func2(x + 0.1) * cos(angle) * resize;
							dz = func2(x + 0.1) * sin(angle) * resize;
							x2 = 9.9 - x;
							y2 = dy;
							z2 = dz + 280;

							if (ang + 5 < 360) {

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func2(x + 0.1) * cos(angle) * resize;
								dz = func2(x + 0.1) * sin(angle) * resize;
								x3 = 9.9 - x;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func2(x) * cos(angle) * resize;
								dz = func2(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
							else {
								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func2(x + 0.1) * cos(angle) * resize;
								dz = func2(x + 0.1) * sin(angle) * resize;
								x3 = 9.9 - x;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func2(x) * cos(angle) * resize;
								dz = func2(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;

							}
						}
						else {
							angle = 2.0 * 3.1415926 * ang / 360.0;
							dy = func2(x + 0.1) * cos(angle) * resize;
							dz = func2(x + 0.1) * sin(angle) * resize;
							x2 = 0;
							y2 = dy;
							z2 = dz + 280;

							if (ang + 5 < 360) {

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func2(x + 0.1) * cos(angle) * resize;
								dz = func2(x + 0.1) * sin(angle) * resize;
								x3 = 0;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * (ang + 5) / 360.0;
								dy = func2(x) * cos(angle) * resize;
								dz = func2(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
							else {
								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func2(x + 0.1) * cos(angle) * resize;
								dz = func2(x + 0.1) * sin(angle) * resize;
								x3 = 0;
								y3 = dy;
								z3 = dz + 280;

								angle = 2.0 * 3.1415926 * 0 / 360.0;
								dy = func2(x) * cos(angle) * resize;
								dz = func2(x) * sin(angle) * resize;
								x4 = 10 - x;
								y4 = dy;
								z4 = dz + 280;
							}
						}
						if (x == 0.0) {
							n1 = (y2 - y_1)*(z3 - z1) - (y3 - y_1)*(z2 - z1);
							n2 = (z2 - z1)* (x3 - x1) - (z3 - z1) *(x2 - x1);
							n3 = (x2 - x1)* (y3 - y_1) - (x3 - x1)*(y2 - y_1);
						}
						else {
							n1 = (y4 - y3)*(z1 - z3) - (y_1 - y3)*(z4 - z3);
							n2 = (z4 - z3)*(x1 - x3) - (z1 - z3)*(x4 - x3);
							n3 = (x4 - x3)*(y_1 - y3) - (x1 - x3)*(y4 - y3);
						}
						double n5 = sqrt(n1*n1 + n2*n2 + n3*n3);
						n1 /= (n5 + 0.01);
						n2 /= (n5 + 0.01);
						n3 /= (n5 + 0.01);
						glNormal3d(n1, n2, n3);

						glVertex3f(x1, y_1 + 525, z1);
						glVertex3f(x2, y2 + 525, z2);
						glVertex3f(x3, y3 + 525, z3);
						glVertex3f(x4, y4 + 525, z4);

					}
				}
			}
			glEnd();
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);

			glPopMatrix();

			
			glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(30, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateY_medium, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateX_medium, 1.0, 0.0, 1.0);
			glTranslatef(0, -525, -280);
			glColor3f(1, 0, 0);
			glPointSize(5.0);
			glColor4f(0.0, 1.0, 1.0, 0.3);
			glScalef(resize_medium_len_left, 1, 1);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			
			func3(resize_medium_left);
			
			glEnd();
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(-30, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateY_medium, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateX_medium, 1.0, 0.0, 1.0);
			glTranslatef(0, -525, -280);
			glColor3f(1, 0, 0);
			glPointSize(5.0);
			glColor4f(0.0, 1.0, 1.0, 0.3);
			glScalef(resize_medium_len_right, 1, 1);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			
			func3(resize_medium_right);
			
			glEnd();
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(-60, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateY_small, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateX_small, 1.0, 0.0, 1.0);
			glTranslatef(0, -525, -280);
			glColor3f(1, 0, 0);
			glPointSize(5.0);
			glColor4f(0.0, 1.0, 1.0, 0.3);
			glScalef(resize_small_len_right, 1, 1);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			
			func3(resize_small_right);
			
			glEnd();
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0.0, 1.0, 0.0);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(60, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateY_small, 0.0, 1.0, 0.0);
			glTranslatef(0, -525, -280);
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 525, 280);
			glRotatef(rotateX_small, 1.0, 0.0, 1.0);
			glTranslatef(0, -525, -280);
			glColor3f(1, 0, 0);
			glPointSize(5.0);
			glColor4f(0.0, 1.0, 1.0, 0.3);
			glScalef(resize_small_len_left, 1, 1);
			glDepthMask(GL_FALSE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
			
			func3(resize_small_left);
			
			glEnd();
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			glPopMatrix();

		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		glFlush();
		glutMainLoopEvent();

		if (stop_b)
			t += t_del;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (debug_coords)
		{
			debug_coords = false;

			std::cout << "File row : " << (int)t << std::endl;
			for (int i = 0; i < DRONES; i++)
			{
				printf("Drone %d: ", i + 1);
				drones[i].trajectory_str_get();
			}
		}
	}
	return 0;
}