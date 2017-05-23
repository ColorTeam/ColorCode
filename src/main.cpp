//outer head files
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

Player player;
vector<Enemy> enemy;
//vector<Foreground> foreground;

Collision colli;
vector<BigTex> bigtex;

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
	colli.PBodyCollide(player.PhysBody, enemy[0].PhysBody);
	///step 4. update GO
	///step 5. render
	glOnRender();
	///step 6. control fps
	Sleep(50);
}

int main() {
	bigtex.clear();
	enemy.clear();
	//foreground.clear();

	int xx, yy, nn;
	char tmp_name[128];
	u32 *tex;
	Json::Reader reader;
	Json::Value root;
#if USE_PACKAGE == 1
	// use package
#else
	for (int i = 0; i < MAX_TEX; i++) {
		sprintf(tmp_name, "res/bigtex%02d.png", i);
		tex = (u32*)stbi_load(tmp_name, &xx, &yy, &nn, image_channels);
		if (!tex) break;
#if _DEBUG
		printf("loadtex: %s\n", tmp_name);
#endif
		bigtex.push_back(BigTex(xx, yy, tex));
	}
	//big1 = (u32*)stbi_load("res/bigtex01.png", &xx, &yy, &nn, image_channels);

	ifstream ifs;
	ifs.open("res/desc.json", std::ios::binary);
	if (!ifs) {
		cerr << "open 'res/desc.json' failed!" << endl;
		Sleep(5000);
		return -1;
	}
	if (!reader.parse(ifs, root)) {
		cerr << "cannot parser 'res/desc.json'!" << endl;
		Sleep(5000);
		return -1;
	}
	int rootSize = root.size();
	for (int rootIndex = 0; rootIndex < rootSize; rootIndex++) {
		string type = root[rootIndex]["Type"].asString();
		if (type == "Player") {
			player = Player(root[rootIndex]);
		}
		else if (type == "Enemy") {
			enemy.push_back(Enemy(root[rootIndex]));
		}
		else if (type == "Foreground") {
			//
		}
	}
#endif

	gl_work_init(500, 500);

	//game loop
	while (!EndGameFlag) {
		game_main_loop();
	}
}
