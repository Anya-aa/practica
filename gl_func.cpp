#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "GL\freeglut.h"
#include "gl_func.h"
#include "camera.h"
#include "GL\glaux.h"
#include "texture.h"

#define all(x) begin(x), end(x)

float resize_small_len_left = 10;
float resize_small_right = 25;
float resize_small_left = 25;
float resize_small_len_right = 10;
float resize_medium_left = 100;
float resize_medium_right = 100;
float resize_medium_len_left = 40;
float resize_medium_len_right = 40;
bool isPressed = false;
bool isHeight = false;
bool isRotate = true;
double rotateX = 0, rotateY = 0, rotateX_medium = 0, rotateY_medium = 0, rotateX_small = 0, rotateY_small = 0;

void warn(const std::string& str)
{
	std::cerr << str << std::endl;
}

int fSize(std::string str)
{
	std::ifstream in(str, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

double getD(std::string& str)
{
	std::string s;
	while (str.size() && isspace(str[0]))
	{
		str.erase(0, 1);
	}
	while (str.size() && (str[0] == '.' || str[0] == '-' || str[0] == '+' ||
		str[0] == 'e' || isdigit(str[0])))
	{
		s += str[0];
		str.erase(0, 1);
	}
	while (str.size() && isspace(str[0]))
	{
		str.erase(0, 1);
	}
	double d;
	d = stod(s);
	return d;
};

void glNormalv(vNormal n) { glNormal3f(n.xn, n.yn, n.zn); }
void glVertexv(Vertex v) { glVertex3f(v.x, v.y, v.z); }
void glTexCoord2f(vTexture vt) { glTexCoord2f(vt.xt, vt.yt); }

void drawTriangles(const std::vector<Vertex>& v, const std::vector<vNormal>& vn,
	const std::vector<vTexture>& vt, const Field& surf)
{
	if (surf.v.size() == 3)
		glBegin(GL_TRIANGLES);
	else if (surf.v.size() > 3)
		glBegin(GL_TRIANGLE_FAN);
	else
		throw "wrong surf indexing";
	for (int i = 0; i < 3; i++)
	{
		glNormalv(vn[surf.vn[i] - 1]);
		glTexCoord2f(vt[surf.vt[i] - 1]);
		glVertexv(v[surf.v[i] - 1]);
	}
	glEnd();
}

void draw(const std::vector<Vertex>& v, const std::vector<vNormal>& vn,
	const std::vector<vTexture>& vt, const std::vector<Field>& f)
{

	for (auto surf : f)
	{

		auto check = [&](std::vector<int> what, int For)
		{
			auto res = find_if(all(what), [&](int it) { return it > For; });
			if (res != what.end())
			{
				warn("must be less than " + std::to_string(For) + ", but get " +
					std::to_string(*res));
				return true;
			}
			return false;
		};
		if (check(surf.v, v.size()) || check(surf.vn, vn.size()) ||
			check(surf.vt, vt.size()))
		{

			continue;
		}

		drawTriangles(v, vn, vt, surf);
	}
}

void create_list_global(GLint& surface, const char* path) /// создаем дисплейный список дрона
{

	surface = glGenLists(1); /// id дисплейного списка
	glNewList(surface, GL_COMPILE); /// начало заполнения дисп. списка (что\когда)

	std::ifstream in(path);
	printf("Callist (%s) start parsing...\n", path);
	std::vector<Field> f;
	std::vector<Vertex> v;
	std::vector<vNormal> vn;
	std::vector<vTexture> vt;

	std::string str;
	while (in.good()) {
		getline(in, str);

		auto eat = [&](std::string s) {
			if (str.size() < s.size())
				return false;
			if (std::string(str.begin(), str.begin() + s.size()) == s) {
				str.erase(0, s.size());
				return true;
			}
			else
				return false;
		};

		if (eat("f ")) {
			f.push_back(Field(str));
		}
		else if (eat("v ")) {
			v.push_back(Vertex(str));
		}
		else if (eat("vn ")) {
			vn.push_back(vNormal(str));
		}
		else if (eat("vt ")) {
			vt.push_back(vTexture(str));
		}
	}
	draw(v, vn, vt, f);

	glEndList(); /// дисп лсит заполенен
	printf("---Complete---\n", path);
}

void timer(int value)
{
	if (rotateY > 30) {
		isPressed = !isPressed;
	}

	if (rotateY <= -30) {
		isPressed = !isPressed;
	}

	if (!isPressed) {
		if (isRotate) {
			rotateY -= 10;
			rotateY_medium -= 10;
			rotateY_small -= 10;
			resize_small_left += 4;
			resize_small_right -= 4;
			resize_medium_left += 16.5;
			resize_medium_right -= 16.5;
			resize_medium_len_left += 6.6;
			resize_medium_len_right -= 6.6;
			resize_small_len_right -= 1.6;
			resize_small_len_left += 1.6;
			isRotate = !isRotate;
		}
	}
	else {
		if (isRotate) {
			rotateY += 60;
			rotateY_medium += 60;
			rotateY_small += 60;
			resize_small_left = 0;
			resize_medium_left = 0;
			resize_small_right = 25;
			resize_medium_right = 100;
			resize_small_len_right = 10;
			resize_medium_len_right = 40;
			resize_small_len_left = 0;
			resize_medium_len_left = 0;
			isPressed = !isPressed;
			isRotate = !isRotate;
		}
	}

	if (rotateX > 22.5) {
		isHeight = !isHeight;
	}

	if (rotateX < -22.5) {
		isHeight = !isHeight;
	}

	if (!isHeight && !isRotate) {
		rotateX -= 0.5;
		rotateX_medium -= 0.5;
		rotateX_small -= 0.5;
	}
	else {
		rotateX += 45;
		rotateX_medium += 45;
		rotateX_small += 45;
		isHeight = !isHeight;
		isRotate = !isRotate;
	}

	glutPostRedisplay();
	glutTimerFunc(5, timer, 0);
}

void gl_initialization(int argc, char** argv)
{
	glutInit(&argc, argv); /// переносим из консоли все значения в OpenGL для выполнения всех параметров
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_MULTISAMPLE); /// инициализация цветов
	glutInitWindowSize(1300, 600); ///рамер окна
	glutCreateWindow("3D visualization"); /// название окна
	glEnable(GL_DEPTH_TEST); /// разрешаем глубину
	glutTimerFunc(50, timer, 0);
	glutDisplayFunc([]() {}); /// функция отрисовка
	glEnable(GL_LIGHTING); /// используем свое освещения
	glEnable(GL_COLOR_MATERIAL); /// используем цветные материалы
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); /// подсветка внутри и снаружи
	glEnable(GL_NORMALIZE);
	glutKeyboardFunc(glutNormalKeys); /// функция макросов клавы
	glutMouseFunc(mouseButton); /// тут кнопки мышки
	glEnable(GL_LIGHT0); /// вкл конктретный источник света 1/8
	glutReshapeFunc([](int w, int h) /// функция изменения размеров
	{
		if (h == 0)
			h = 1;
		float ratio = 1.0 * w / h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		gluPerspective(60, ratio, 0.1, 50000);
		glMatrixMode(GL_MODELVIEW);
	});
}

