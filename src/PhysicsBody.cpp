#include <iostream>
#include <cstdio>
#include <cmath>

#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {
	bboxList.clear();
	//Init();
}

PhysicsBody::PhysicsBody(Json::Value &root) {
	bboxList.clear();
	int iBBoxNum = root.size();
	for (int i = 0; i < iBBoxNum; i++) {
		BoundingBox bbox(root[i]);
		bboxList.push_back(bbox);
	}
	outBox = CreateOutBox(bboxList);
}

PhysicsBody::PhysicsBody(Vec2f Pos) {
	Position = Pos;
	PrePosition = Pos;
#if _DEBUG
	printf("In Physics init:\n");
	printf("%f %f\n", Pos.x, Pos.y);
#endif
	bboxList.clear();
	//Init();
}

void PhysicsBody::add(Vec2f Position, Vec2f Size) {
	BoundingBox bbx(Position.x, Position.y, Size.x, Size.y);
	bboxList.push_back(bbx);
}

void PhysicsBody::Init(Vec2f pos) {
	Position = pos;
	PrePosition = pos;
}

BoundingBox PhysicsBody::CreateOutBox(std::vector<BoundingBox> bboxs) {
	//float maxX = 0, minX = MAXNUM, maxY = 0, minY = MAXNUM;
	BoundingBox bigBox(MAXNUM, MAXNUM, 0, 0, 0);
	for (unsigned int i = 0; i < bboxs.size(); i++)
	{
		Vec2f leftDown (bboxs[i].localPosition.x, bboxs[i].localPosition.y);
		Vec2f rightDown(bboxs[i].localPosition.x + bboxs[i].Size.x * std::cos(bboxs[i].fRotate), bboxs[i].localPosition.y + bboxs[i].Size.x * std::sin(bboxs[i].fRotate));
		Vec2f leftUp   (bboxs[i].localPosition.x - bboxs[i].Size.y * std::sin(bboxs[i].fRotate), bboxs[i].localPosition.y + bboxs[i].Size.y * std::cos(bboxs[i].fRotate));
		Vec2f rightUp  (leftUp.x + rightDown.x - leftDown.x, leftUp.y + rightDown.y - leftDown.y);

		//minX
		if (leftDown.x < bigBox.localPosition.x)
			bigBox.localPosition.x = leftDown.x;
		if (rightDown.x < bigBox.localPosition.x)
			bigBox.localPosition.x = rightDown.x;
		if (leftUp.x < bigBox.localPosition.x)
			bigBox.localPosition.x = leftUp.x;
		if (rightUp.x < bigBox.localPosition.x)
			bigBox.localPosition.x = rightUp.x;

		//maxX
		if (leftDown.x > bigBox.localPosition.x + bigBox.Size.x)
			bigBox.Size.x = leftDown.x - bigBox.localPosition.x;
		if (rightDown.x > bigBox.localPosition.x + bigBox.Size.x)
			bigBox.Size.x = rightDown.x - bigBox.localPosition.x;
		if (leftUp.x > bigBox.localPosition.x + bigBox.Size.x)
			bigBox.Size.x = leftUp.x - bigBox.localPosition.x;
		if (rightUp.x > bigBox.localPosition.x + bigBox.Size.x)
			bigBox.Size.x = rightUp.x - bigBox.localPosition.x;

		//minY
		if (leftDown.y < bigBox.localPosition.y)
			bigBox.localPosition.y = leftDown.y;
		if (rightDown.y < bigBox.localPosition.y)
			bigBox.localPosition.y = rightDown.y;
		if (leftUp.y < bigBox.localPosition.y)
			bigBox.localPosition.y = leftUp.y;
		if (rightUp.y < bigBox.localPosition.y)
			bigBox.localPosition.y = rightUp.y;

		//maxY
		if (leftDown.y > bigBox.localPosition.y + bigBox.Size.y)
			bigBox.Size.y = leftDown.y - bigBox.localPosition.y;
		if (rightDown.y > bigBox.localPosition.y + bigBox.Size.y)
			bigBox.Size.y = rightDown.y - bigBox.localPosition.y;
		if (leftUp.y > bigBox.localPosition.y + bigBox.Size.y)
			bigBox.Size.y = leftUp.y - bigBox.localPosition.y;
		if (rightUp.y > bigBox.localPosition.y + bigBox.Size.y)
			bigBox.Size.y = rightUp.y - bigBox.localPosition.y;
	}
	return bigBox;
}

void PhysicsBody::UpdatePos(Vec2f Pos) {
	PrePosition = Position;
	Position = Pos;
#if _DEBUG
	printf("in Phy update:\n");
	printf("Pre:%f %f; Pos:%f %f\n", PrePosition.x, PrePosition.y, 
									 Position.x, Position.y);
#endif
}