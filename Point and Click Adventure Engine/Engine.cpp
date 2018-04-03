#include "Engine.hpp"
#include "ImGui.hpp"


namespace pc {
	auto Engine::getRendering()->Rendering & {
		return rendering;
	}


	void Engine::start() {
		//Load the config file, then set
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


	bool Engine::loadScene(const std::string& scene) {
		auto l = lua.lua["rooms"][scene];
		if (!l.valid())
			return false;

		auto objects = l["objects"].get<sol::table>();
		std::string objectname;
		sf::Vector3i pos;
		sf::Vector3<bool> pos_true;
		std::string callback;
		std::vector<char> actions;

		auto get_action = [&actions](std::pair<sol::object, sol::object> p) {
			if (!p.first.is<int>() && !p.second.is<char>())
				return;
			actions.push_back(p.second.as<char>());
		};

		auto do_with_object = [this, &objectname, &pos, &callback, &actions, get_action, &pos_true](std::pair<sol::object, sol::object> p) {
			if (p.first.is<int>()) {
				switch (p.first.as<int>()) {
				case 1:
					if (!p.second.is<std::string>())
						break;
					objectname = p.second.as<std::string>();
					break;
				case 2:
					if (!p.second.is<int>())
						break;

					pos.x = p.second.as<int>();
					pos_true.x = true;
					break;
				case 3:
					if (!p.second.is<int>())
						break;

					pos.y = p.second.as<int>();
					pos_true.y = true;
					break;
				case 4:
					if (!p.second.is<int>())
						break;

					pos.z = p.second.as<int>();
					pos_true.z = true;
					break;

				case 5:
					if (p.second.get_type() != sol::type::nil)
						callback = "nil";
					if (!p.second.is<std::string>())
						break;
					callback = p.second.as<std::string>();
					break;
				case 6:
					if (!p.second.is<sol::table>())
						break;;
					p.second.as<sol::table>().for_each(get_action);
					break;
				default:
					break;
				}
			}
			//Check if everything needed is set
			if (!objectname.empty() && pos_true != sf::Vector3<bool>(false, false, false) && !callback.empty()) {
				if (callback != "nil" && !actions.empty()) {
					// Create Message
					mb::Message message;


					// Reset vars;
					objectname.clear();
					pos = sf::Vector3i();
					pos_true = sf::Vector3<bool>();
					callback.clear();
					actions.clear();
				}
			}
		};

	}

}