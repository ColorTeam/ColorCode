#include <cstdio>
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody() {

}

bool PhysicsBody::CollideWithBody(PhysicsBody bodyB) {
	switch (bodyB.iType)
	{
	case 0://rect
		float sw = (fWidth + bodyB.fWidth) / 2;
		break;
		
	case 1://circle

	default:
		break;
	}
}