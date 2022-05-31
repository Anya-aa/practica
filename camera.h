#ifndef CAMERA_H
#define CAMERA_H 
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>


class CVector3
{
public:
	CVector3()
	{
		//
	}
	CVector3(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}
	CVector3 operator+(CVector3 vVector)
	{
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}
	CVector3 operator-(CVector3 vVector)
	{
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	CVector3 operator*(float num)
	{
		return CVector3(x * num, y * num, z * num);
	}
	CVector3 operator/(float num)
	{
		return CVector3(x / num, y / num, z / num);
	}
	float x, y, z;
};

class CCamera
{
public:
	CCamera();
	CVector3 Position() { return m_vPosition; }
	CVector3 View() { return m_vView; }
	CVector3 UpVector() { return m_vUpVector; }
	CVector3 Strafe() { return m_vStrafe; }
	void PositionCamera(float positionX, float positionY, float positionZ, float viewX, float viewY, float viewZ, float upVectorX, float upVectorY, float upVectorZ);
	void RotateView(float angle, float X, float Y, float Z);
	void SetViewByMouse(float& t);
	void StrafeCamera(float speed);
	void MoveCamera(float speed);
	void Update(float& t);
	void Look();
	int scenario = 0; // позиция камеры по умолчанию

private:
	CVector3 m_vPosition;
	CVector3 m_vView;
	CVector3 m_vUpVector;
	CVector3 m_vStrafe;
};

extern CCamera g_Camera;

void glutNormalKeys(unsigned char key, int i, int i1);

void mouseButton(int button, int state, int x, int y);

#endif