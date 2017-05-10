#include<cstdio>
#include<iostream>

#include "Collision.h"

Collision::Collision() {

}

int Collision::BBoxCollide(BoundingBox bboxA, BoundingBox bboxB) {
	int isCollision = 0;//0:not collide; 1: up; 2: down; 3: left; 4: right

	switch (bboxA.iType)
	{
	case 0://rect
		switch (bboxB.iType)
		{
		case 0://rect
		{
			float disWidth = std::abs((bboxA.Position.x + bboxA.fWidth / 2) - (bboxB.Position.x + bboxB.fWidth / 2));
			float disHeight = std::abs((bboxA.Position.y + bboxA.fHeight / 2) - (bboxB.Position.y + bboxB.fHeight / 2));
			float sumHalfWidth = (bboxA.fWidth + bboxB.fWidth) / 2;
			float sumHalfHeight = (bboxA.fHeight + bboxB.fHeight) / 2;

			if (disWidth<sumHalfWidth && disHeight<sumHalfHeight) {
				if (bboxA.prePosition.y + bboxA.fHeight <= bboxB.prePosition.y && bboxA.Position.y + bboxA.fHeight > bboxB.Position.y)
					isCollision = 1; //up
				else if (bboxA.prePosition.y + bboxA.fHeight <= bboxB.prePosition.y + bboxB.fHeight && bboxA.Position.y + bboxA.fHeight > bboxB.Position.y + bboxB.fHeight)
					isCollision = 2; //down
				else if (bboxA.prePosition.x + bboxA.fWidth <= bboxB.prePosition.x && bboxA.Position.x + bboxA.fWidth > bboxB.Position.x)
					isCollision = 3; //left
				else if (bboxA.prePosition.x + bboxA.fWidth <= bboxB.prePosition.x + bboxB.fWidth && bboxA.Position.x + bboxA.fWidth > bboxB.Position.x + bboxB.fWidth)
					isCollision = 4; //right
				else {
					if (true) // (cls == "enemy"||cls == "thorn")
						isCollision = 5;
					else
						std::cerr << "Error!";
				}
			}
			else {

			}
			break;
		}

		case 1://circle

		default:
			break;
		}
		break;

	case 1://circle

	default:
		break;
	}

	return isCollision;
}

int Collision::PBodyCollide(PhysicsBody bodyA, PhysicsBody bodyB) {
	if (!BBoxCollide(bodyA.outBox, bodyB.outBox))
		return 0;

	int isCollision = 0;//0:not collide; 1: up; 2: down; 3: left; 4: right

	for (unsigned int i = 0; i < bodyA.bboxList.size(); i++) {
		for (unsigned int j = 0; j < bodyB.bboxList.size(); j++) {
			isCollision = BBoxCollide(bodyA.bboxList[i], bodyB.bboxList[j]);
			if (isCollision)
				return isCollision;
		}
	}

	return 0;
}

BoundingBox Collision::CreateAABB(std::vector<BoundingBox> bboxs) {
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
			bigBox.fHeight = bboxs[i].Position.y + bboxs[i].fHeight- bigBox.Position.y;
	}
	return bigBox;
}