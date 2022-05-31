#ifndef GL_FUNC_H
#define GL_FUNC_H 
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>

void warn(const std::string& str);

int fSize(std::string str);

double getD(std::string& str);

class Vertex // координаты вертекса
{
public:
	double x, y, z, w;
	Vertex(double x_ = 0, double y_ = 0, double z_ = 0, double w_ = 1.0)
		: x(x_), y(y_), z(z_), w(w_) {}
	Vertex(std::string str)
	{
		if (str.size())
			x = getD(str);
		if (str.size())
			y = getD(str);
		if (str.size())
			z = getD(str);
		if (str.size())
			w = getD(str);
	}
};

class vNormal // нормали
{
public:
	double xn, yn, zn;
	vNormal(double xn_ = 0, double yn_ = 0, double zn_ = 0)
		: xn(xn_), yn(yn_), zn(zn_) {}
	vNormal(std::string str)
	{
		if (str.size())
			xn = getD(str);
		if (str.size())
			yn = getD(str);
		if (str.size())
			zn = getD(str);
	}
};

class vTexture // текстурные координаты
{
public:
	double xt, yt, wt;
	vTexture(double xt_ = 0, double yt_ = 0, double wt_ = 0)
		: xt(xt_), yt(yt_), wt(wt_) {}
	vTexture(std::string str)
	{
		if (str.size())
			xt = getD(str);
		if (str.size())
			yt = getD(str);
		if (str.size())
			wt = getD(str);
	}
};

class Field
{
public:
	std::vector<int> v;  // вектор индексов вершин
	std::vector<int> vn; // вектор индексов нормалей
	std::vector<int> vt; // вектор индексов текстур

	Field(std::string str)
	{
		v.reserve(3);
		vn.reserve(3);
		vt.reserve(3);
		auto getI = [&]()
		{
			std::string s;
			for (int i = 0; i < int(str.size()) && isdigit(str[i]); i++)
			{
				s += str[i];
			}
			str.erase(0, s.size());
			return stoi(s);
		};
		auto isNextDigit = [&]() { return str.size() && isdigit(str[0]); };
		auto eraseCntBackSlash = [&]()
		{
			int i;
			for (i = 0; str.size() && str[0] == '/'; i++)
				str.erase(0, 1);
			return i;
		};
		while (str.size())
		{
			int vi = 0;
			int vni = 0;
			int vti = 0;
			if (isspace(str[0]))
			{
				str.erase(0, 1);
				continue;
			}
			if (!isNextDigit())
			{
				std::cout << "can't proc \'";
				for (int i : str) {
					std::cout << i << " ";
				}
				std::cout << "\\'" << std::endl;
				throw std::string("expected digit in surf format but get \'") + str +
					"\'";
			}
			vi = getI();
			int ti;
			switch (ti = eraseCntBackSlash())
			{
			case 0:
				break;
			case 1:
				vti = getI();
				if (eraseCntBackSlash())
					vni = getI();
				break;
			case 2:
				vni = getI();
				break;
			default:
				throw "expected 0-2 backslashs, but get " + std::to_string(ti);
			}
			v.push_back(vi);
			vt.push_back(vti);
			vn.push_back(vni);
		}
	}
};

void create_list_global(GLint& surface, const char* path);

void gl_initialization(int argc, char** argv);

#endif