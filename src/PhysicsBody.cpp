#include <cstdio>
#include <cmath>
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {

}

bool PhysicsBody::CollideWithBody(PhysicsBody bodyB) {
	switch (bodyB.iType)
	{
	case 0://rect
		float disWidth  = std::abs((Position.x + fWidth/2) -(bodyB.Position.x + bodyB.fWidth/2));
		float disHeight = std::abs((Position.y + fHeight/2)-(bodyB.Position.y + bodyB.fHeight/2));
		float sumHalfWidth = (fWidth + bodyB.fWidth) / 2;
		float sumHalfHeight = (fHeight + bodyB.fHeight) / 2;

		if ((disWidth<sumHalfWidth) && (disHeight<sumHalfHeight)) {

		}
		break;
		
	case 1://circle

	default:
		break;
	}
}