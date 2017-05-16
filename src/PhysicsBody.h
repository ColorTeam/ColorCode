#ifndef PHYSICS_BODY_H_INCLUDE
#define PHYSICS_BODY_H_INCLUDE

#include <vector>
#include "utils.h"

//temp structure
//to be replaced by duktape
struct BBoxData {
	int iType;//0:rect 1:circle
	float fPosX;
	float fPosY;
	float fWidth;
	float fHeight;
	float fRotate;

	BBoxData(float pos_x, float pos_y, float width, float height, float rotate = 0.0, int type = 0) {
		fPosX = pos_x;
		fPosY = pos_y;
		fWidth = width;
		fHeight = height;
		fRotate = rotate;
		iType = type;
	}
};

class BoundingBox {
public:
	int iType;//0:rect 1:circle
	Vec2f Position;
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

	BoundingBox(float posX, float posY, float width, float height, float rotate = 0.0, int type = 0) {
		Position.x = posX;
		Position.y = posY;
		fWidth = width;
		fHeight = height;
		fRotate = rotate;
		iType = type;
	}
};

class PhysicsBody {
public:
	PhysicsBody();
	PhysicsBody(float posX, float posY, float width, float height, int type, float rotate);
	void Init(std::vector<BBoxData> bboxData);
	BoundingBox CreateAABB(BoundingBox bbox);
	BoundingBox CreateOutBox(std::vector<BoundingBox> bboxs);
	void UpdatePos(Vec2f Pos);

	std::vector<BoundingBox> bboxList; //small bounding box list
	BoundingBox outBox; //the outside big bounding box of all small bounding box
	void add(Vec2f Position, Vec2f Size);


	Vec2f PrePosition;
	Vec2f Position;
};

#endif //PHYSICS_BODY_H_INCLUDE
