#include "Sprite.h"

Sprite::Sprite() {
	iFrameN = 0;
	iFrameNow = 0;
	vFrames.clear();
}

Sprite::Sprite(Json::Value root) {
	vFrames.clear();
	iFrameN = root.size();
	for (int i = 0; i < iFrameN; i++) {
		SpriteFrame frame;
		frame.bigtexIndex = root[i]["src"].asInt();
		Json::Value v = root[i]["v"];
		Json::Value vt = root[i]["vt"];
		for (int j = 0; j < 4; j++) {
			frame.v[j].x = (float)v[j<<1].asDouble();
			frame.v[j].y = (float)v[(j<<1)+1].asDouble();
			frame.vt[j].x = (float)vt[j<<1].asDouble();
			frame.vt[j].y = (float)vt[(j<<1)+1].asDouble();
		}
		vFrames.push_back(frame);
	}
	iFrameNow = 0;
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

void Sprite::SetNextFrame() {
	iFrameNow++;
	if (iFrameNow >= iFrameN)
		iFrameNow = 0;
}

SpriteFrame Sprite::getFrame() {
	return vFrames[iFrameNow];
}

void Sprite::Draw(Vec2f wPos) {
	
} 
