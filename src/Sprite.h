#ifndef SPRITE_H_INCLUDE
#define SPRITE_H_INCLUDE

#include "utils.h"
#include <vector>

class SpriteFrame {
public:
	float afVT[8];
	float afV[8];
};

class Sprite {
public:
	Sprite();
	//void Read(const char* filename);
	void AddFrame(float v[8], float vt[8]);
	void Draw(Point2D wPos);
private:
	int iFrameNum;
	int iFrameID;
	std::vector<SpriteFrame> vFrames;
};

#endif //SPRITE_H_INCLUDE

