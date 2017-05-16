#include <iostream>
#include <cstdio>
#include <cmath>

#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {
	//Init();
}

PhysicsBody::PhysicsBody(float posX, float posY, float width, float height, int type = 0, float rotate = 0.0) {
	//Position = Pos;
	//PrePosition = Pos;
	//Init();
}

void PhysicsBody::add(Vec2f Position, Vec2f Size) {
	BoundingBox bbx(Position.x, Position.y, Size.x, Size.y);
	bboxList.push_back(bbx);
}

void PhysicsBody::Init(std::vector<BBoxData> bboxData) {

	for (unsigned int i = 0; i < bboxData.size(); i++) {
		bboxList.push_back(BoundingBox(bboxData[0].fPosX, bboxData[0].fPosY, bboxData[0].fWidth, bboxData[0].fHeight, bboxData[0].iType, bboxData[0].fRotate));
	}
	outBox = CreateOutBox(bboxList);
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
		if (bboxs[i].Position.x < bigBox.Position.x)
			bigBox.Position.x = bboxs[i].Position.x;
		if (bboxs[i].Position.x + bboxs[i].fWidth > bigBox.Position.x + bigBox.fWidth)
			bigBox.fWidth = bboxs[i].Position.x + bboxs[i].fWidth - bigBox.Position.x;

		if (bboxs[i].Position.y < bigBox.Position.y)
			bigBox.Position.y = bboxs[i].Position.y;
		if (bboxs[i].Position.y + bboxs[i].fHeight > bigBox.Position.y + bigBox.fHeight)
			bigBox.fHeight = bboxs[i].Position.y + bboxs[i].fHeight - bigBox.Position.y;
	}
	return bigBox;
}

void PhysicsBody::UpdatePos(Vec2f Pos) {
	PrePosition = Position;
	Position = Pos;
}