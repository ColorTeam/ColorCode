#ifndef GAME_OBJECT_H_INCLUDE
#define GAME_OBJECT_H_INCLUDE

#include "utils.h"
#include "Sprite.h"
#include "PhysicsBody.h"
#include <vector>
#include <freeglut.h>

class GameObject {
public:
	GameObject() {}
	GameObject(float x, float y) {
		Position.x = x;
		Position.y = y;
		InitPhysicsBody();
	}
	void print_Pos() {
		printf("x: %.1f; y: %.1f;\n", Position.x, Position.y);
	}

	void InitPhysicsBody();

	virtual bool OnKeyboard(int Key)=0;

	PhysicsBody PhysBody;

protected:
	Vec2f Position;
	Sprite MySprite;
};

class Player : public GameObject {
public:
	Player() {}
	Player(float x, float y) {
		Position.x = x;
		Position.y = y;
	}

	Vec2f getGLPosition() {
		Vec2f tmp(Position.x / 1024.f*2.f - 1.f, Position.y / 1024.f*2.f - 1.f);
		return tmp;
	}

	bool OnKeyboard(int Key) {
		bool Ret = true;

		switch (Key) {

		case GLUT_KEY_UP:
		{
			Position.y+=10;
		}
		break;

		case GLUT_KEY_DOWN:
		{
			Position.y-= 10;
		}
		break;

		case GLUT_KEY_LEFT:
		{
			Position.x-= 10;
		}
		break;

		case GLUT_KEY_RIGHT:
		{
			Position.x+= 10;
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

extern Player player;
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

