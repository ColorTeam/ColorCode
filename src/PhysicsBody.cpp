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
	printf("In Phy init:\n");
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

//for Rotate
BoundingBox PhysicsBody::CreateAABB(BoundingBox bbox) {
	//float maxX = 0, minX = MAXNUM, maxY = 0, minY = MAXNUM;
	BoundingBox bigBox(MAXNUM, MAXNUM, 0, 0, 0);

	return bigBox;
}

BoundingBox PhysicsBody::CreateOutBox(std::vector<BoundingBox> bboxs) {
	//float maxX = 0, minX = MAXNUM, maxY = 0, minY = MAXNUM;
	BoundingBox bigBox(MAXNUM, MAXNUM, 0, 0, 0);
	for (unsigned int i = 0; i < bboxs.size(); i++)
	{
		if (bboxs[i].localPosition.x < bigBox.localPosition.x)
			bigBox.localPosition.x = bboxs[i].localPosition.x;
		if (bboxs[i].localPosition.x + bboxs[i].Size.x > bigBox.localPosition.x + bigBox.Size.x)
			bigBox.Size.x = bboxs[i].localPosition.x + bboxs[i].Size.x - bigBox.localPosition.x;

		if (bboxs[i].localPosition.y < bigBox.localPosition.y)
			bigBox.localPosition.y = bboxs[i].localPosition.y;
		if (bboxs[i].localPosition.y + bboxs[i].Size.y > bigBox.localPosition.y + bigBox.Size.y)
			bigBox.Size.y = bboxs[i].localPosition.y + bboxs[i].Size.y - bigBox.localPosition.y;
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