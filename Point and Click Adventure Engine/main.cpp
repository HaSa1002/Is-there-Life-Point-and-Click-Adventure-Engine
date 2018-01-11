#pragma once
#pragma comment(linker, "/SUBSYSTEM:Windows /ENTRY:mainCRTStartup")
#include "Game.hpp"
#include "Editor.hpp"

#include <SFML\Main.hpp>


int main(int argc, char* argv[]) {
	bool intoEngine = true; //Change this to false for normal use
	for (int i = 0; i < argc; i++) {
		if (argv[i] == "-engine")
			intoEngine = true;
	}
	if (intoEngine) {
		pc::Editor editor;
		editor.start();
	}
	/*else {
		pc::Game Game;
		Game.start();
		Game.~Game();
	}*/
	return 0;
}