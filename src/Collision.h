#ifndef COLLISION_H_INCLUDE
#define COLLISION_H_INCLUDE

#include "PhysicsBody.h"
#include "GameObject.h"

class Collision {
public:
	Collision();
	int BBoxCollide(BoundingBox bboxA, BoundingBox bboxB);
	int PBodyCollide(PhysicsBody bodyA, PhysicsBody bodyB);
	BoundingBox CreateAABB(std::vector<BoundingBox> bBoxs);

};

#endif //COLLISION_H_INCLUDE
