#ifndef SPRITE_H_INCLUDE
#define SPRITE_H_INCLUDE

#include "utils.h"
#include "gl_helper.h"
#include <vector>

class SpriteFrame {
public:
	int bigtexIndex;
	Vec2f vt[4];
	Vec2f v[4];
	unsigned int ebo[6];
	SpriteFrame() {
		ebo[0] = 0; ebo[1] = 1; ebo[2] = 2;
		ebo[3] = 1; ebo[4] = 3; ebo[5] = 2;
	}
};

class Sprite {
public:
	Sprite();
	Sprite(Json::Value root);

	//void Read(const char* filename);
	//void AddFrame(float v[8], float vt[8]);
	void Draw(Vec2f wPos);
	void SetNextFrame();
	SpriteFrame getFrame();
private:
	int iFrameN;
	int iFrameNow;
	std::vector<SpriteFrame> vFrames;
	//GLProgram m_program;
};

#endif //SPRITE_H_INCLUDE

