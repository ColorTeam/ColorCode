//outer head files
#include <cstdio>
#include <iostream>
#include <vector>

//inner head files
#include "GameObject.h"
#include "utils.h"

//stb_image
#define STB_IMAGE_IMPLEMENTATION 1
#define STB_IMAGE_WRITE_IMPLEMENTATION 1
#include <stb_image.h>
#include <stb_image_write.h>

//inner define
#define SHOW_LOG     1
#define USE_PACKAGE  0

using namespace std;

const int image_channels = 4;

vector<GameObject> GO;
Player player;
BigTex bigtex;

void ReadJson() {
	
}

bool OnKeyboard(int Key) {
	bool ret = player.OnKeyboard(Key);
	player.print_Pos();
	return ret;
}

//game loop and render loop
void game_main_loop() {

}

int main() {
	GO.clear();

	int xx, yy, nn;
	u32 *big;
#if USE_PACKAGE == 1
	// use package
#else
	big = (u32*)stbi_load("res/bigtex.png", &xx, &yy, &nn, image_channels);
	player = Player(50,50);
	//GO.push_back(player);
#endif
	bigtex = BigTex(xx, yy, big);
	gl_work_init(500, 500, bigtex);
}
