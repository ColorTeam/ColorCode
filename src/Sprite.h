#ifndef SPRITE_H_INCLUDE
#define SPRITE_H_INCLUDE

#include "utils.h"
#include <vector>

class SpriteFrame {
public:
	int bigtexIndex;
	float vt[8];
	float v[8];
};

class Sprite {
public:
	Sprite();
	Sprite(Json::Value root);

	//void Read(const char* filename);
	void AddFrame(float v[8], float vt[8]);
	void Draw(Vec2f wPos);
private:
	int iFrameNum;
	int iFrameID;
	std::vector<SpriteFrame> vFrames;
};

#endif //SPRITE_H_INCLUDE

