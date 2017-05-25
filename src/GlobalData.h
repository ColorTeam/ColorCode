#ifndef GLOBAL_DATA_H_INCLUDE
#define GLOBAL_DATA_H_INCLUDE

#include "utils.h"
#include "GameObject.h"
#include "Collision.h"

//inner define
#define USE_PACKAGE  0
#define ImageChannels 4
#define MAX_TEX 10

class GlobalData {
public:
	GlobalData() {
		PlayerStep = Vec2f(10.0, 10.0);
		ViewSize = Vec2f(1024.0, 1024.0);
		EndGameFlag = false;
		MaxPlayerPosX = 500.0;
		ViewStartX = 0.0;
	}

	inline Vec2f getStep() { return PlayerStep; }
	inline Vec2f getViewSize() { return ViewSize; }
	inline bool isGameEnd() { return EndGameFlag; }
	inline float getStartX() { return ViewStartX; }
	inline bool updataStartX(float playerX) {
		if (playerX - ViewStartX <= MaxPlayerPosX) return false;
		ViewStartX += playerX - ViewStartX - MaxPlayerPosX;
		return true;
	}
private:
	Vec2f PlayerStep;
	Vec2f ViewSize;
	bool EndGameFlag;
	float ViewStartX;
	float MaxPlayerPosX;
};

extern GlobalData g_data;
extern Player player;
extern std::vector<Enemy> enemy;
extern std::vector<Foreground> foreground;
extern Collision colli;

extern std::vector<BigTex> bigtex;
#endif //GLOBAL_DATA_H_INCLUDE
