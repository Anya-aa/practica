#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

#include "GL/freeglut.h"
#include "gl_func.h"
#include "matlab_parser.h"

#include <string.h>
#include <stdio.h>

#define WORD_LEN 50

int scanner(FILE* file, char*& buff, bool& end)
{
	int i = 0, c;

	buff = (char*)calloc(WORD_LEN, sizeof(char)); // занять память для записи слова

	while (1)
	{
		c = fgetc(file);
		if (c == '\n' || c == '\r')
		{
			end = true;
		}
		if (feof(file))
		{
			return i;
		}
		if (isspace(c) || c == '\t')
		{
			return i;
		}
		if (c == ',')
		{
			c = '.';
		}
		buff[i] = c;
		i++;
	}
	return i;
}

int parser(std::vector<Drone_state>*& vec, const char* file_name)
{
	char* buff;
	buff = NULL;

	FILE* file;
	file = fopen(file_name, "r");

	int brek;
	for (brek = strlen(file_name); (file_name[brek] != '/') && (file_name[brek] != '\\'); brek--);
	char print_buf[256];
	memset(print_buf, NULL, 256 * sizeof(char));
	print_buf[0] = '.';
	print_buf[1] = '.';
	print_buf[2] = '.';
	strcpy(&print_buf[3], &file_name[brek]);

	if (!file)
	{
		printf("File %s not opened\n", print_buf);
		return -1;
	}
	printf("File %s opened,", print_buf);

	vec = new std::vector<Drone_state>;
	int vec_i = 0;
	int err;

	float x[6] = { 0,0,0,0,0,0 };
	bool end = false;
	while (1)
	{
		end = false;
		for (int i = 0; i < 6; i++)
		{
			err = scanner(file, buff, end);
			x[i] = atof(buff);

			if (err <= 0)
			{
				fclose(file);
				printf(" lines: %d\n", vec_i);
				return vec_i;
			}

			if (end)
				break;
		}

		Drone_state b(x[0], x[1], x[2], x[3], x[4], x[5]);

		vec->push_back(b);
		vec_i++;
	}

	fclose(file);
	return vec_i;
}

