#ifndef PHYSICS_BODY_H_INCLUDE
#define PHYSICS_BODY_H_INCLUDE

class PhysicsBody {
public:
	PhysicsBody();
	bool CollideWithBody(PhysicsBody bodyB);

	int iType;//0:rect 1:circle
	Point2D Position;
	float fWidth;
	float fHeight;

private:

};

#endif //PHYSICS_BODY_H_INCLUDE
