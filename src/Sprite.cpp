#include "Sprite.h"

Sprite::Sprite() {
	iFrameNum = 0;
	iFrameID = 0;
	vFrames.clear();
}

void Sprite::AddFrame(float v[8], float vt[8]) {
	SpriteFrame nowFrame;
	for (int i = 0; i < 8; i++) {
		nowFrame.afVT[i] = vt[i];
		nowFrame.afV[i] = v[i];
	}
	vFrames.push_back(nowFrame);
}

void Sprite::Draw(Vec2f wPos) {
	
}