#pragma once
#include "Game.h"
#include "Leveleditor.h"

#include <SFML\Main.hpp>

int main(int argc, char* argv[]) {
	bool intoEngine = true; //Change this to false for normal use
	for (int i = 0; i < argc, i++) {
		if (argv[i] == "-engine")
			intoEngine = true;
	}
	if (intoEngine) {
		pc::Leveleditor Leveleditor;
		Leveleditor.start();
		Leveleditor.~Leveleditor();
	}
	else {
		pc::Game Game;
		Game.start();
		Game.~Game();
	}
	return 0;
}