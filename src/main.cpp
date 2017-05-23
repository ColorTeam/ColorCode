//outer head files
#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//inner head files
#include "GlobalData.h"

//stb_image
#define STB_IMAGE_IMPLEMENTATION 1
#define STB_IMAGE_WRITE_IMPLEMENTATION 1
#include <stb_image.h>
#include <stb_image_write.h>

using namespace std;

bool ReadJson(const char* file_name) {
	Json::Reader reader;
	Json::Value root;
	ifstream ifs;
	ifs.open(file_name, std::ios::binary);
	if (!ifs) {
		cerr << "open " << file_name << " failed!" << endl;
		Sleep(5000);
		return false;
	}
	if (!reader.parse(ifs, root)) {
		cerr << "cannot parser " << file_name << "!" << endl;
		Sleep(5000);
		return false;
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
			foreground.push_back(Foreground(root[rootIndex]));
		}
	}
	return true;
}

bool OnKeyboard(int Key) {
	//bool ret = player.OnKeyboard(Key);
	bool Ret = true;
	Vec2f tmp_pos(0.0, 0.0);
	switch (Key) {
		case GLUT_KEY_UP: tmp_pos.y = g_data.getStep().y; break;
		case GLUT_KEY_DOWN: tmp_pos.y = -g_data.getStep().y; break;
		case GLUT_KEY_LEFT: tmp_pos.x = -g_data.getStep().x; break;
		case GLUT_KEY_RIGHT: tmp_pos.x = g_data.getStep().x; break;
		default: Ret = false; break;
	}
	if (!Ret) return false;
	player.updateStep(tmp_pos);
	g_data.updataStartX(player.getPosX());
#if _DEBUG
	player.print_Pos();
#endif
	return Ret;
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
#if USE_PACKAGE == 1
	// use package
#else
	for (int i = 0; i < MAX_TEX; i++) {
		sprintf(tmp_name, "res/bigtex%02d.png", i);
		tex = (u32*)stbi_load(tmp_name, &xx, &yy, &nn, ImageChannels);
		if (!tex) break;
#if _DEBUG
		printf("loadtex: %s\n", tmp_name);
#endif
		bigtex.push_back(BigTex(xx, yy, tex));
	}
	//ReadJson("res/desc.json");
	ReadJson("res/desc_huiwen.json");
#endif

	gl_work_init(500, 500);

	//game loop
	while (!g_data.isGameEnd()) {
		game_main_loop();
	}
}
