#include<cstdio>
#include<iostream>

#include "Collision.h"

Collision::Collision() {

}

int Collision::BBoxCollide(BoundingBox& bboxA, BoundingBox& bboxB, Vec2f globalPosA, Vec2f globalPosB, Vec2f globalPrePosA, Vec2f globalPrePosB) {
	int isCollision = 0;//0:not collide; 1: up; 2: down; 3: left; 4: right

	switch (bboxA.iType)
	{
	case 0://rect
		switch (bboxB.iType)
		{
		case 0://rect
		{
			float disWidth = std::abs((globalPosA.x + bboxA.Size.x / 2) - (globalPosB.x + bboxB.Size.x / 2));
			float disHeight = std::abs((globalPosA.y + bboxA.Size.y / 2) - (globalPosB.y + bboxB.Size.y / 2));
			float sumHalfWidth = (bboxA.Size.x + bboxB.Size.x) / 2;
			float sumHalfHeight = (bboxA.Size.y + bboxB.Size.y) / 2;

			if (disWidth<sumHalfWidth && disHeight<sumHalfHeight) {
				if (globalPrePosA.y > globalPrePosB.y + bboxB.Size.y && globalPosA.y <= globalPosB.y + bboxB.Size.y) {
					isCollision = 1; //up
					printf("UP!\n");
				}
				else if (globalPrePosA.y + bboxA.Size.y < globalPrePosB.y && globalPosA.y + bboxA.Size.y >= globalPosB.y) {
					isCollision = 2; //down
					printf("DOWN!\n");
				}
				else if (globalPrePosA.x + bboxA.Size.x < globalPrePosB.x && globalPosA.x + bboxA.Size.x >= globalPosB.x) {
					isCollision = 3; //left
					printf("LEFT!\n");
				}
				else if (globalPrePosA.x > globalPrePosB.x + bboxB.Size.x && globalPosA.x <= globalPosB.x + bboxB.Size.x) {
					isCollision = 4; //right
					printf("RIGHT!\n");
				}
				else {
					if (true) { // (cls == "enemy"||cls == "thorn"), losing life + transparent
						isCollision = 5;
						printf("COLLIDE FROM INSIDE!\n");
					}
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
	if (!BBoxCollide(bodyA.outBox, bodyB.outBox, 
		bodyA.Position+bodyA.outBox.Position, bodyB.Position+bodyB.outBox.Position, 
		bodyA.PrePosition+bodyA.outBox.Position, bodyB.PrePosition+bodyB.outBox.Position))
		return 0;

	int isCollision = 0;//0:not collide; 1: up; 2: down; 3: left; 4: right

	for (unsigned int i = 0; i < bodyA.bboxList.size(); i++) {
		for (unsigned int j = 0; j < bodyB.bboxList.size(); j++) {
			isCollision = BBoxCollide(bodyA.bboxList[i], bodyB.bboxList[j],
				bodyA.Position + bodyA.bboxList[i].Position, bodyB.Position + bodyB.bboxList[j].Position,
				bodyA.PrePosition + bodyA.bboxList[i].Position, bodyB.PrePosition + bodyB.bboxList[j].Position);
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
		if (bboxs[i].Position.x + bboxs[i].Size.x > bigBox.Position.x + bigBox.Size.x)
			bigBox.Size.x = bboxs[i].Position.x + bboxs[i].Size.x - bigBox.Position.x;

		if (bboxs[i].Position.y < bigBox.Position.y)
			bigBox.Position.y = bboxs[i].Position.y;
		if (bboxs[i].Position.y + bboxs[i].Size.y > bigBox.Position.y + bigBox.Size.y)
			bigBox.Size.y = bboxs[i].Position.y + bboxs[i].Size.y - bigBox.Position.y;
	}
	return bigBox;
}