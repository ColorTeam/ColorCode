#ifndef GAME_OBJECT_H_INCLUDE
#define GAME_OBJECT_H_INCLUDE

#include "utils.h"
#include "Sprite.h"
#include <vector>

class GameObject {
public:
	GameObject();
	virtual int ListenInputSignal(int InputKeyID);
private:
	Point2D Position;
	Sprite Sprite;
	//PhysicsBody PhysBody;
};

class GameObject_Player : public GameObject {
public:
	int ListenInputSignal(int InputKeyID);
	void OnCollid(int canshu);
private:
	int iHP;

};

int GameObject_Player::ListenInputSignal(int InputKeyID) {
	switch (InputKeyID) {
	case KEY_UP:

	case KEY_DOWN:

	case KEY_LEFT:

	case KEY_RIGHT:
	}
}

#endif //GAME_OBJECT_H_INCLUDE

