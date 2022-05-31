#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

#include "GL/freeglut.h"
#include "gl_func.h"
#include "camera.h"
#include "drone.h"

float kSpeed = 2.5;		// —корость движени¤ камеры

bool cam_mouse_en = false;
bool time_mouse_en = false;

int mouse_x, mouse_y;

bool reset_b;
bool stop_b;
bool debug_coords;
float t_del;

bool diagram = false;
bool zaderska = false;
bool surface_on = true;
bool traect_on = true;

extern bool isEnd;

float speedup = 0.1;

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cam_mouse_en = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		cam_mouse_en = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		time_mouse_en = true;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		time_mouse_en = false;
	}

	mouse_x = x;
	mouse_y = y;
}

CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vNormal;

	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vNormal;
}

float Magnitude(CVector3 vNormal)
{
	return (float)sqrt((vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
}

CVector3 Normalize(CVector3 vVector)
{
	float magnitude = Magnitude(vVector);

	vVector = vVector / magnitude;

	return vVector;
}

void CCamera::SetViewByMouse(float& t)
{
	POINT mousePos;			// Ёто структура, хран¤щ¤¤ X и Y позиции мыши

	int middleX = mouse_x;	//  оординаты начальные
	int middleY = mouse_y;
	float angleY = 0;	// Ќаправление взгл¤да вверх/вниз
	float angleZ = 0;	// «начение, необходимое дл¤ вращени¤ влево-вправо (по оси Y)
	static float currentRotX = 0;

	if (time_mouse_en)
	{
		GetCursorPos(&mousePos); // ѕолучаем текущие коорд. мыши
		if ((mousePos.x == middleX) && (mousePos.y == middleY)) return; // ≈сли курсор осталс¤ в том же положении, мы не вращаем камеру
		SetCursorPos(middleX, middleY); // “еперь, получив координаты курсора, возвращаем его обратно в середину.
		t += ((float)((middleX - mousePos.x)) / 200) * (-1);
	}

	if (cam_mouse_en)
	{
		GetCursorPos(&mousePos); // ѕолучаем текущие коорд. мыши
		if ((mousePos.x == middleX) && (mousePos.y == middleY)) return; // ≈сли курсор осталс¤ в том же положении, мы не вращаем камеру
		SetCursorPos(middleX, middleY); // “еперь, получив координаты курсора, возвращаем его обратно в середину.
		angleY = (float)((middleX - mousePos.x)) / 2000; // 2000 - это скорсть вращени¤ (чтобы не было минус глаза)
		angleZ = (float)((middleY - mousePos.y)) / 2000;
	}

	static float lastRotX = 0;
	lastRotX = currentRotX;		// —охран¤ем последний угол вращени¤ и используем заново currentRotX

	if (currentRotX > 1)	// ≈сли текущее вращение больше 1 градуса, обрежем его, чтобы не вращать слишком быстро
	{
		currentRotX = 1;
		if (lastRotX != 1)	// врощаем на оставшийс¤ угол
		{
			CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = Normalize(vAxis);
			RotateView(1 - lastRotX, vAxis.x, vAxis.y, vAxis.z);	// ¬ращаем камеру вокруг нашей оси на заданный угол
		}
	}

	else if (currentRotX < -1)	// ≈сли угол меньше -1, убедимс¤, что вращение не продолжитс¤
	{
		currentRotX = -1;
		if (lastRotX != -1)
		{
			CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);			// ќп¤ть же вычисл¤ем ось
			vAxis = Normalize(vAxis);
			RotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);	// ¬ращаем
		}
	}

	else	// ≈сли укладываемс¤ в пределы 1.0f -1.0f - просто вращаем
	{
		CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
		vAxis = Normalize(vAxis);
		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}
	RotateView(angleY, 0, 1, 0);	// ¬сегда вращаем камеру вокруг Y-оси
}

CCamera::CCamera()
{
	CVector3 vZero = CVector3(0.0, 0.0, 0.0);		//»нициализируем вектор нашей позиции в нулевые координаты
	CVector3 vView = CVector3(0.0, 1.0, 0.5);		//»ниц. вектор взгл¤да
	CVector3 vUp = CVector3(0.0, 0.0, 1.0);			//¬ектор верт.

	m_vPosition = vZero;
	m_vView = vView;
	m_vUpVector = vUp;
}

GLvoid CCamera::PositionCamera(float positionX, float positionY, float positionZ, float viewX, float viewY, float viewZ, float upVectorX, float upVectorY, float upVectorZ)
{
	CVector3 vPosition = CVector3(positionX, positionY, positionZ);
	CVector3 vView = CVector3(viewX, viewY, viewZ);
	CVector3 vUpVector = CVector3(upVectorX, upVectorY, upVectorZ);

	m_vPosition = vPosition;
	m_vView = vView;
	m_vUpVector = vUpVector;
}

void CCamera::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;
	CVector3 vView;

	vView.x = m_vView.x - m_vPosition.x;	//ѕолучим наш вектор взгл¤да (направление, куда мы смотрим) направление по X
	vView.y = m_vView.y - m_vPosition.y;	//направление по Y
	vView.z = m_vView.z - m_vPosition.z;	//направление по Z

	float cosTheta = (float)cos(angle);		// –ассчитаем 1 раз синус и косинус переданного угла
	float sinTheta = (float)sin(angle);

	vNewView.x = (cosTheta + (1 - cosTheta) * x * x) * vView.x;		// Ќайдем новую позицию X дл¤ вращаемой точки
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta) * vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta) * vView.z;

	vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta) * vView.x;		// Ќайдем позицию Y
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y) * vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta) * vView.z;

	vNewView.z = ((1 - cosTheta) * x * z - y * sinTheta) * vView.x;		// » позицию Z
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta) * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z) * vView.z;

	m_vView.x = m_vPosition.x + vNewView.x;		// “еперь просто добавим новый вектор вращени¤ к нашей позиции, чтобы установить новый взгл¤д камеры.
	m_vView.y = m_vPosition.y + vNewView.y;
	m_vView.z = m_vPosition.z + vNewView.z;
}

void CCamera::StrafeCamera(float speed)
{
	CVector3 vVector = m_vView - m_vPosition;

	vVector.y = 0;
	vVector = Normalize(vVector);
	vVector.z = vVector.z + vVector.x;
	vVector.x = vVector.z - vVector.x;
	vVector.z = vVector.z - vVector.x;
	vVector.x *= -1;

	m_vPosition = m_vPosition + vVector * speed;

	m_vView = m_vView + vVector * speed;
}

void CCamera::MoveCamera(float speed)
{
	CVector3 vVector = m_vView - m_vPosition;

	vVector = Normalize(vVector);

	m_vPosition.x += vVector.x * speed;
	m_vPosition.y += vVector.y * speed;
	m_vPosition.z += vVector.z * speed;

	m_vView.x += vVector.x * speed;
	m_vView.y += vVector.y * speed;
	m_vView.z += vVector.z * speed;

}

void CCamera::Update(float& t)
{
	CVector3 vCross = Cross(m_vView - m_vPosition, m_vUpVector);

	m_vStrafe = Normalize(vCross);

	SetViewByMouse(t);	// ѕосмотрим, двигалась ли мыша
}

void CCamera::Look()
{
	gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z, m_vView.x, m_vView.y, m_vView.z, m_vUpVector.x, m_vUpVector.y, m_vUpVector.z); // ƒадим OpenGL позицию, взгл¤д и верт. вектор камеры
}

void glutNormalKeys(unsigned char key, int i, int i1)
{
	switch (key)
	{
	case 'a':
		g_Camera.StrafeCamera(-kSpeed);
		break;
	case 'd':
		g_Camera.StrafeCamera(kSpeed);
		break;
	case 's':
		g_Camera.MoveCamera(-kSpeed);
		break;
	case 'w':
		g_Camera.MoveCamera(kSpeed);
		break;
	case '=':
		t_del += speedup;
		printf("Time speed = %f\n", t_del);
		break;
	case '-':
		t_del -= speedup;
		printf("Time speed = %f\n", t_del);
		break;
	case 'r':
		reset_b = true;
		break;
	case 'q':
		printf("Coordinate camera -> %f %f %f\n", g_Camera.Position().x, g_Camera.Position().y, g_Camera.Position().z);
		printf("Napravlenie eye -> %f %f %f\n", g_Camera.View().x, g_Camera.View().y, g_Camera.View().z);
		break;
	case '1':
		if (g_Camera.scenario != 1)
			g_Camera.scenario = 1;
		break;
	case '2':
		if (g_Camera.scenario != 2)
			g_Camera.scenario = 2;
		break;
	case '3':
		if (g_Camera.scenario != 3)
			g_Camera.scenario = 3;
		break;
	case 'c':
		debug_coords = true;
		break;
	case 127: // 'DEL' - кнопка 
		if (g_Camera.scenario != 0)
			g_Camera.scenario = 0;
		break;
	case 'e':
		surface_on = !surface_on;
		break;
	case 'f':
		traect_on = !traect_on;
		break;
	case 't':
		zaderska = !zaderska;
		reset_b = true;
		break;
	case 'o':
		if (!isEnd)
			diagram = !diagram;
		break;
	case 32:
		if (stop_b)
		{
			stop_b = false;
			//printf("Stop animation\n");
		}
		else
		{
			stop_b = true;
			//printf("Play animation\n");
		}
		break;
	case 27:
		exit(0);
		break;
	default:
		printf("Pressed unknown key: %d\n", key); // отладка дл¤ номера клавиши
		break;
	}
}
