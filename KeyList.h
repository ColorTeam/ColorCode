#ifndef KEYLIST_H_INCLUDE
#define KEYLIST_H_INCLUDE

#include <freeglut.h>

class KeyList {
public:
	bool UP;
	bool DOWN;
	bool LEFT;
	bool RIGHT;

	KeyList() {
		UP = false; DOWN = false; LEFT = false; RIGHT = false;
	}

	bool OnKeyboard(int Key) {
		bool Ret = true;

		switch (Key) {

		case GLUT_KEY_UP:
		{
			UP = true;
		}
		break;

		case GLUT_KEY_DOWN:
		{
			DOWN = true;
		}
		break;

		case GLUT_KEY_LEFT:
		{
			LEFT = true;
		}
		break;

		case GLUT_KEY_RIGHT:
		{
			RIGHT = true;
		}
		break;

		default:
		{
			Ret = false;
		}
		break;

		}
		return Ret;
	}
};

#endif //KEYLIST_H_INCLUDE


