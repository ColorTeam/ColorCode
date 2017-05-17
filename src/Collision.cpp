#include<cstdio>
#include<iostream>

#include "Collision.h"

Collision::Collision() {

}

int Collision::BBoxCollide(BoundingBox& bboxA, BoundingBox& bboxB, Vec2f PosA, Vec2f PosB, Vec2f PrePosA, Vec2f PrePosB) {
	int isCollision = 0;//0:not collide; 1: up; 2: down; 3: left; 4: right

	//printf("boxA: pre(%f,%f), cur(%f,%f), size(%f,%f)\n", PrePosA.x, PrePosA.y, PosA.x, PosA.y, bboxA.Size.x, bboxA.Size.y);
	//printf("boxB: pre(%f,%f), cur(%f,%f), size(%f,%f)\n", PrePosB.x, PrePosB.y, PosB.x, PosB.y, bboxB.Size.x, bboxB.Size.y);

	switch (bboxA.iType)
	{
	case 0://rect
		switch (bboxB.iType)
		{
		case 0://rect
		{
			float disWidth = std::abs((PosA.x + bboxA.Size.x / 2) - (PosB.x + bboxB.Size.x / 2));
			float disHeight = std::abs((PosA.y + bboxA.Size.y / 2) - (PosB.y + bboxB.Size.y / 2));
			float sumHalfWidth = (bboxA.Size.x + bboxB.Size.x) / 2;
			float sumHalfHeight = (bboxA.Size.y + bboxB.Size.y) / 2;

			if (disWidth<sumHalfWidth && disHeight<sumHalfHeight) {
				if (PrePosA.y >= PrePosB.y + bboxB.Size.y && PosA.y < PosB.y + bboxB.Size.y) {
					isCollision = 1; //up
#if _DEBUG
					printf("UP!\n");
#endif
				}
				else if (PrePosA.y + bboxA.Size.y <= PrePosB.y && PosA.y + bboxA.Size.y > PosB.y) {
					isCollision = 2; //down
#if _DEBUG
					printf("DOWN!\n");
#endif 
				}
				else if (PrePosA.x + bboxA.Size.x <= PrePosB.x && PosA.x + bboxA.Size.x > PosB.x) {
					isCollision = 3; //left
#if _DEBUG
					printf("LEFT!\n");
#endif
				}
				else if (PrePosA.x >= PrePosB.x + bboxB.Size.x && PosA.x < PosB.x + bboxB.Size.x) {
					isCollision = 4; //right
#if _DEBUG
					printf("RIGHT!\n");
#endif
				}
				else {
					if (true) { // (cls == "enemy"||cls == "thorn"), losing life + transparent
						isCollision = 5;
#if _DEBUG
						printf("COLLIDE FROM INSIDE!\n");
#endif
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
		bodyA.Position+bodyA.outBox.localPosition, bodyB.Position+bodyB.outBox.localPosition,
		bodyA.PrePosition+bodyA.outBox.localPosition, bodyB.PrePosition+bodyB.outBox.localPosition))
		return 0;

	int isCollision = 0;//0:not collide; 1: up; 2: down; 3: left; 4: right

	for (unsigned int i = 0; i < bodyA.bboxList.size(); i++) {
		for (unsigned int j = 0; j < bodyB.bboxList.size(); j++) {
			isCollision = BBoxCollide(bodyA.bboxList[i], bodyB.bboxList[j],
				bodyA.Position + bodyA.bboxList[i].localPosition, bodyB.Position + bodyB.bboxList[j].localPosition,
				bodyA.PrePosition + bodyA.bboxList[i].localPosition, bodyB.PrePosition + bodyB.bboxList[j].localPosition);
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