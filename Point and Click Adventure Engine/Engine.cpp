#include "Engine.hpp"
#include "ImGui.hpp"

namespace pc {
	auto Engine::getRendering()->Rendering & {
		return rendering;
	}


	void Engine::start() {
		//Load the config file, then set
		if (editor_mode) {
			rendering.createWindow();
			rendering.imgui_rendering(true);
			menue.open("mainmenue");
		}
		else {
			rendering.createWindow("Is there Life?", true);
			//GAME START
		}
		main();
	}

	void Engine::main() {
		
		sf::Clock clock;
		while (rendering.isOpen()) {
			if (editor_mode) {
				menue.draw(rendering);
			}
			else {
				//GAME MAIN PART
			}
			ecs.run();
			rendering.render();
		}
	}
	void Engine::processEvents() {
		//TODO: If some events need to be hard-wired then here
	}
}