#ifndef UTILS_C_INCLUDE
#define UTILS_C_INCLUDE

#include <windows.h>
#include <conio.h>

struct Point2D {
	int x;
	int y;
};

GLuint VBO;
GLuint EBO;

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

#endif //UTILS_C_INCLUDE
