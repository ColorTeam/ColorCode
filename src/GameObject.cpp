#include <cstdio>
#include "GameObject.h"
/*
GameObject::GameObject() {
}
*/

void GameObject::InitPhysicsBody() {
	std::vector<BBoxData> bboxData;
	bboxData.push_back(BBoxData(0.0, 0.0, 50.0, 50.0, 0.0, 0));
	bboxData.push_back(BBoxData(20.0, 0.0, 50.0, 50.0, 0.0, 0));
	bboxData.push_back(BBoxData(20.0, 20.0, 50.0, 50.0, 0.0, 0));
	PhysBody.Init(bboxData);
}