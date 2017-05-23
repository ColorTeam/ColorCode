#include <cstdio>
#include "GameObject.h"

/*
GameObject::GameObject() {
}

void GameObject::InitPhysicsBody(float x, float y, float w, float h) {
	std::vector<BBoxData> bboxData;
	bboxData.push_back(BBoxData(x, y, w, h, 0.0, 0));
	//bboxData.push_back(BBoxData(0.0, 0.0, 50.0, 50.0, 0.0, 0));
	//bboxData.push_back(BBoxData(20.0, 0.0, 50.0, 50.0, 0.0, 0));
	//bboxData.push_back(BBoxData(20.0, 20.0, 50.0, 50.0, 0.0, 0));
	PhysBody.Init(bboxData);
}
*/

GameObject::GameObject(Json::Value root) {
	Position.x = (float)root["Position"][0].asDouble();
	Position.y = (float)root["Position"][1].asDouble();
	PhysBody = PhysicsBody(root["BoundingBox"]);
	MySprite = Sprite(root["Sprite"]);

	//PhysBody = PhysicsBody(Position);
	PhysBody.Init(Position);

	Size = PhysBody.outBox.Size;
}
/*
bool Player::OnKeyboard(int Key) {
	bool Ret = true;
	Vec2f tmp_pos(0.0, 0.0);
	switch (Key) {
		case GLUT_KEY_UP: tmp_pos.y = step.y; break;
		case GLUT_KEY_DOWN: tmp_pos.y = -step.y; break;
		case GLUT_KEY_LEFT: tmp_pos.x = -step.x; break;
		case GLUT_KEY_RIGHT: tmp_pos.x = step.x; break;
		default: Ret = false; break;
	}
	if (!Ret) return false;

	Position += tmp_pos;
	PhysBody.UpdatePos(Position);
	return Ret;
}*/