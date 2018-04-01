#pragma once
//#pragma comment(linker, "/SUBSYSTEM:Windows /ENTRY:mainCRTStartup")
#include "Engine.hpp"
#include <SFML\Main.hpp>


int main(int argc, char* argv[]) {
	bool intoEngine = true; //Change this to false for normal use
	for (int i = 0; i < argc; i++) {
		if (argv[i] == "-engine")
			intoEngine = true;
	}
	pc::Engine engine(intoEngine);
	return 0;
}