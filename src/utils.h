#ifndef UTILS_C_INCLUDE
#define UTILS_C_INCLUDE

#include <windows.h>
#include <conio.h>
#include <vector>
#include "json/json.h"

#define MAXNUM 1e9

typedef unsigned char u8;
typedef unsigned int  u32;

bool OnKeyboard(int Key);
void glOnRender();

class BigTex {
public:
	u32 *data;
	int width, height;
	unsigned int tex_id;
	BigTex(int x, int y, u32* d) {
		width = x;
		height = y;
		data = d;
		tex_id = -1;
	}
	BigTex() {
		width = 0;
		height = 0;
		data = NULL;
		tex_id = -1;
	}
};

int gl_work_init(int width0, int height0);

class Vec2f {
public:
	float x;
	float y;
	Vec2f() {
		x = 0.0;
		y = 0.0;
	}
	Vec2f(float a, float b) {
		x = a;
		y = b;
	}
	Vec2f& operator=(const Vec2f& a) {
		x = a.x;
		y = a.y;
		return *this;
	}
	Vec2f operator+(const Vec2f& a) {
		return Vec2f(x+a.x,y+a.y);
	}
	Vec2f& operator+=(const Vec2f& a) {
		x += a.x;
		y += a.y;
		return *this;
	}
	Vec2f& operator-=(const Vec2f& a) {
		x -= a.x;
		y -= a.y;
		return *this;
	}
};

struct Vec2i {
	int x;
	int y;
	Vec2i() {
		x = 0;
		y = 0;
	}
	Vec2i(int a, int b) {
		x = a;
		y = b;
	}
};

/*
int ListenUserInput() {
	char ch;
	int i = 0;
	//循环监听，直到按Esc键退出
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == 27) {
				break;
			}
		}
		printf("Number: %d\n", ++i);
	}
}
*/


#endif //UTILS_C_INCLUDE
