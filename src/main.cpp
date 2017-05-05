#include <cstdio>
#include <iostream>

using namespace std;

#define GAME_DEBUG 0
#define EDITOR	   0

void ReadJson() {
	
}

int main() {

#if EDITOR == 1
	//todo run editor
#else
	//todo run game
	ReadJson();
#endif
	scanf("%*c");
	return 0;
}