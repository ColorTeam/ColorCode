#ifndef COLLISION_H_INCLUDE
#define COLLISION_H_INCLUDE

#include "PhysicsBody.h"
#include "GameObject.h"

class Collision {
public:
	Collision();
	int BBoxCollide(BoundingBox& bboxA, BoundingBox& bboxB, Vec2f globalPosA, Vec2f globalPosB, Vec2f globalPrePosA, Vec2f globalPrePosB);
	int PBodyCollide(PhysicsBody bodyA, PhysicsBody bodyB);
	BoundingBox CreateAABB(std::vector<BoundingBox> bBoxs);

};

#endif //COLLISION_H_INCLUDE
