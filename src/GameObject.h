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
	GameObject(Json::Value root) {
		Position.x = (float)root["Position"][0].asDouble();
		Position.y = (float)root["Position"][1].asDouble();
		PhysBody = PhysicsBody(root["BoundingBox"]);
		MySprite = Sprite(root["Sprite"]);
		
		//PhysBody = PhysicsBody(Position);
		PhysBody.Init(Position);

		Size = PhysBody.outBox.Size;
	}
	void print_Pos() {
		printf("x: %.1f; y: %.1f;\n", Position.x, Position.y);
	}
	inline Vec2f getGLPosition() {
		return Vec2f(Position.x/1024.f * 2.f - 1.f, Position.y/1024.f * 2.f - 1.f);
	}
	inline Vec2f getGLSize() {
		return Vec2f(Size.x/1024.f * 2.f, Size.y/1024.f * 2.f);
	}

	void InitPhysicsBody(float x, float y, float w, float h);

	PhysicsBody PhysBody;

protected:
	Vec2f Position;
	Vec2f Size;
	Sprite MySprite;
};

class Player : public GameObject {
public:
	Player() {}
	Player(Json::Value root) : GameObject(root) {}
	

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

		PhysBody.UpdatePos(Position);
		return Ret;
	}
};

extern Player player;

class Enemy : public GameObject {
public:
	Enemy() {}
	Enemy(Json::Value root) : GameObject(root) {}
};

extern std::vector<Enemy> enemy;
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

