#ifndef PHYSICS_BODY_H_INCLUDE
#define PHYSICS_BODY_H_INCLUDE

#include <vector>
#include "utils.h"

class BoundingBox {
public:
	int iType;//0:rect 1:circle
	Vec2f Position;
	Vec2f prePosition;
	float fWidth;
	float fHeight;
	float fRotate;

	BoundingBox() {
		iType = 0;
		Position.x = 0;
		Position.y = 0;
		fWidth = 5;
		fHeight = 5;
		fRotate = 0;
	}

	BoundingBox(float posX, float posY, float width, float height, int type = 0, float rotate = 0.0) {
		Position.x = posX;
		Position.y = posY;
		fWidth = width;
		fHeight = height;
		iType = type;
		fRotate = rotate;
	}
};

class PhysicsBody {
public:
	PhysicsBody();
	PhysicsBody(float posX, float posY, float width, float height, int type, float rotate);
	BoundingBox CreateAABB(BoundingBox bbox);
	BoundingBox CreateOutBox(std::vector<BoundingBox> bboxs);

	std::vector<BoundingBox> bboxList; //small bounding box list
	BoundingBox outBox; //the outside big bounding box of all small bounding box

private:

};

#endif //PHYSICS_BODY_H_INCLUDE
