#include "Engine.hpp"
#include "ImGui.hpp"
#include "lua.hpp"

namespace pc {
	auto Engine::getRendering()->Rendering & {
		return rendering;
	}


	void Engine::start() {
		//Load the config file, then set
		Lua lua;
		if (!lua.init())
			return;
		if (editor_mode) {
			//See the Editor.conf.lua to get an overview of what is possible
			if (!lua.editorConfig())
				return;
			auto editor = lua.lua["editor"];
			rendering.createWindow(editor["title"], editor["fullscreen"], sf::VideoMode(editor["solution"][1].get_or(1600), editor["solution"][2].get_or(900)));
			rendering.imgui_rendering(true);
			auto menues = editor["open_menues"].get<sol::table>();
			auto addmenue = [this](std::pair<sol::object, sol::object> p) {
				if (p.second.is<std::string>())
					menue.open(p.second.as<std::string>());
			};
			menues.for_each(addmenue);
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