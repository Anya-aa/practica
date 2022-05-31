#ifndef TEXTURE_H
#define TEXTURE_H

#include "IL\il.h"
#include "IL\ilu.h"

#include "GL\freeglut.h"

// �������� ��������� TextureImage ��� �������� ������ ��������.
typedef struct TextureImage
{
	GLubyte* imageData;		// ������ ��������
	GLuint	bpp;			// ���� �� ������
	GLuint width, height;		// ������ � ������
	GLuint texID;			// ID ��������
}TextureImage;


// ����� �������. �������� � �������������.
class CTexture
{
public:

	CTexture();
	~CTexture();

	// ����������, ����� ��� ������ ������� - � �� ������ 2 ������� - 
	// �������� � ������������ ������� =)
	void LoadTexture(ILenum FileType, char* filename, TextureImage* texture);
	void FreeTexture(TextureImage* texture);
};


#endif
