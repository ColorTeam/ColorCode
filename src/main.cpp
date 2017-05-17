//outer head files
#include <cstdio>
#include <iostream>
#include <vector>

//inner head files
#include "GameObject.h"
#include "Collision.h"
#include "utils.h"

//stb_image
#define STB_IMAGE_IMPLEMENTATION 1
#define STB_IMAGE_WRITE_IMPLEMENTATION 1
#include <stb_image.h>
#include <stb_image_write.h>

//inner define
#define USE_PACKAGE  0

using namespace std;

const int image_channels = 4;

vector<GameObject> GO;
Player player;
Enemy enemy;

Collision colli;
BigTex bigtex;

static bool EndGameFlag = false;

void ReadJson() {
	
}

bool OnKeyboard(int Key) {
	bool ret = player.OnKeyboard(Key);
#if _DEBUG
	player.print_Pos();
#endif
	return ret;
}

//game loop and render loop
void game_main_loop() {
	///step 1. listen user key

	///step 2. update position
	
	///step 3. physical (for a,b in GO: check colli(a,b) -> mark)
	colli.PBodyCollide(player.PhysBody, enemy.PhysBody);
	///step 4. update GO
	///step 5. render
	glOnRender();
	///step 6. control fps
	Sleep(50);
}

int main() {
	GO.clear();

	int xx, yy, nn;
	u32 *big;
#if USE_PACKAGE == 1
	// use package
#else
	big = (u32*)stbi_load("res/bigtex.png", &xx, &yy, &nn, image_channels);
	player = Player(50,50,50,50);
	enemy = Enemy(120, 120, 100, 100);
	//GO.push_back(player);
#endif
	bigtex = BigTex(xx, yy, big);
	gl_work_init(500, 500, bigtex);

	//game loop
	while (!EndGameFlag) {
		game_main_loop();
	}
}
