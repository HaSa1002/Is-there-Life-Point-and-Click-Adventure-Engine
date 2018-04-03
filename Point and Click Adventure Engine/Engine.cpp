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

			//Jede vorhandene Szene im ECS erstellen


			
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
		//check if scene exists
		auto l = lua.lua["rooms"][scene];
		if (!l.valid())
			return false;

		//add the scene to the ecs
		std::hash<std::string> h_s;
		std::list<std::shared_ptr<cs::BaseProperty>> props;
		props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<std::string>(h_s("name"), scene)));
		props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<int>(h_s("active"), 0)));
		size_t scene_id = ecs.spawn(props);
		props.clear();

		//get the objects
		auto objects = l["objects"].get<sol::table>();
		std::list<char> actions;
		sf::Vector3i pos;
		
		//reads the action table
		auto get_action = [&actions](std::pair<sol::object, sol::object> p) {
			if (!p.first.is<int>() && !p.second.is<char>())
				return;
			actions.push_back(p.second.as<char>());
		};
		std::string objectname;
		//reads the object
		auto read_object = [this, &props, &pos, &actions, get_action, &h_s, &objectname](std::pair<sol::object, sol::object> p) {
			if (p.first.is<int>()) {
				switch (p.first.as<int>()) {
				case 1:
					if (!p.second.is<std::string>())
						break;
					props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<std::string>(h_s("name"), p.second.as<std::string>())));
					objectname = p.second.as<std::string>();
					break;
				case 2:
					if (!p.second.is<int>())
						break;

					pos.x = p.second.as<int>();
					break;
				case 3:
					if (!p.second.is<int>())
						break;

					pos.y = p.second.as<int>();
					break;
				case 4:
					if (!p.second.is<int>())
						break;

					pos.z = p.second.as<int>();
					break;

				case 5:
					if (!p.second.is<std::string>())
						break;
					props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<std::string>(h_s("callback"), p.second.as<std::string>())));
					break;
				case 6:
					if (!p.second.is<sol::table>())
						break;
					p.second.as<sol::table>().for_each(get_action);
					props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<std::list<char>>(h_s("actions"), actions)));
					break;
				default:
					break;
				}
			}
		};

		//iterates through the object and adds it to the ecs once finished
		auto for_each_object = [this, &pos, &props, read_object, h_s, scene_id](std::pair<sol::object, sol::object> p) {
			if (!p.second.is<sol::table>())
				return;
			p.second.as<sol::table>().for_each(read_object);

			//adding of the object to the ecs
			props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<sf::Vector3i>(h_s("pos"), pos)));
			props.push_back(std::make_shared<cs::BaseProperty>(cs::Property<size_t>(h_s("callback"), scene_id)));
			ecs.spawn(props);
			props.clear();
		};

		//iterates through the objects
		objects.for_each(for_each_object);
		//add walkboxes
		//add zoomlines
		//add the objects to the scene list
	}

}