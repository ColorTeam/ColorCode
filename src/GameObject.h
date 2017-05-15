#ifndef GAME_OBJECT_H_INCLUDE
#define GAME_OBJECT_H_INCLUDE

#include "utils.h"
#include "Sprite.h"
#include "PhysicsBody.h"
#include <vector>

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

	bool MoveUp() {
		Position.y--;
		return true;
	}

	bool MoveDown() {
		Position.y++;
		return true;
	}

	bool MoveLeft() {
		Position.x--;
		return true;
	}

	bool MoveRight() {
		Position.x++;
		return true;
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

