#include "Sprite.h"

Sprite::Sprite() {
	iFrameNum = 0;
	iFrameID = 0;
	vFrames.clear();
}

Sprite::Sprite(Json::Value root) {
	vFrames.clear();
	iFrameNum = root.size();
	for (int i = 0; i < iFrameNum; i++) {
		SpriteFrame frame;
		frame.bigtexIndex = root[i]["src"].asInt();
		Json::Value v = root[i]["v"];
		Json::Value vt = root[i]["vt"];
		for (int j = 0; j < 8; j++) {
			frame.v[j] = (float)v[j].asDouble();
			frame.vt[j] = (float)vt[j].asDouble();
		}
		vFrames.push_back(frame);
	}
	iFrameID = 0;
}
/*
void Sprite::AddFrame(float v[8], float vt[8]) {
	SpriteFrame nowFrame;
	for (int i = 0; i < 8; i++) {
		nowFrame.vt[i] = vt[i];
		nowFrame.v[i] = v[i];
	}
	vFrames.push_back(nowFrame);
}
*/
void Sprite::Draw(Vec2f wPos) {
	
} 