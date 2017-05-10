#ifndef GAME_OBJECT_H_INCLUDE
#define GAME_OBJECT_H_INCLUDE

#include "utils.h"
#include "Sprite.h"
#include <freeglut.h>
#include <vector>

class GameObject {
public:
	GameObject() {}
	GameObject(float x, float y) {
		Position.x = x;
		Position.y = y;
	}
	void print_Pos() {
		printf("x: %.1f; y: %.1f;\n", Position.x, Position.y);
	}
	virtual bool OnKeyboard(int Key)=0;
protected:
	Vec2f Position;
	Sprite MySprite;
	//PhysicsBody PhysBody;
};

class Player : public GameObject {
public:
	Player() {}
	Player(float x, float y) {
		Position.x = x;
		Position.y = y;
	}

	bool OnKeyboard(int Key) {
		bool Ret = false;

		switch (Key) {

		case GLUT_KEY_UP:
		{
			Position.y++;
			Ret = true;
		}
		break;

		case GLUT_KEY_DOWN:
		{
			Position.y--;
			Ret = true;
		}
		break;

		case GLUT_KEY_LEFT:
		{
			Position.x--;
			Ret = true;
		}
		break;

		case GLUT_KEY_RIGHT:
		{
			Position.x++;
			Ret = true;
		}
		break;
		}

		return Ret;
	}
};
/*
class GameObject_Player : public GameObject {
public:
	GameObject_Player() { iHP = 100; super = 0; };
	int ListenInputSignal(int InputKeyID);
	void OnCollid(int canshu);
private:
	int iHP;
	bool super;
};
*/
/*
int GameObject_Player::ListenInputSignal(int InputKeyID) {
	switch (InputKeyID) {
	case KEY_UP:

	case KEY_DOWN:

	case KEY_LEFT:

	case KEY_RIGHT:
	}
}
*/
#endif //GAME_OBJECT_H_INCLUDE

