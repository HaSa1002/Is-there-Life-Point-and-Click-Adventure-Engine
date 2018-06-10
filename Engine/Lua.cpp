#include "Lua.hpp"
#include "config.hpp"
#include <fstream>

namespace pc {
	bool Lua::init() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::io, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
		try {
			lua.script_file("Engine.lua");
		}
		catch (sol::error err) {
			printf("%s\n", err.what());
			return false;
		}
		if (lua["scenes"].valid() && lua["localisations"].valid() && lua["game"].valid())
			return true;
		return false;
	}


	bool Lua::editorConfig() {
		//See the Editor.conf.lua to get an overview of what is possible
		// Create the variables first, so that we don't run into errors with the file nor with our Engine.cpp
		lua.script(R"(
			editor = {
				solution = {1600, 900},
				title = "Is there Life? | Engine",
				fullscreen = false,
				open_menues = { "mainmenue" },
			}
			print "Config variables set.\n"
			)");


		//Load the Config File
		try {
			lua.script_file("Editor.conf.lua");
		}
		catch (sol::error err) {
			printf("%s\n", err.what());
			
			try {
				//Create a new file...
				std::fstream file("Editor.conf.lua", std::fstream::out);
				file << std::flush;
				file.close();
				//...and try again
				lua.script_file("Editor.conf.lua");
			}
			catch (sol::error err) {
				//if we are here. Something went terribly wrong
				printf("%s\n", err.what());
				return false;
			}
		}
		return true;
	}

	const std::string Lua::getSceneToBeLoaded() {
		if (lua["game"]["loadScene"].get<std::string>().empty())
			return "";

		std::string scene = lua["game"]["loadScene"].get_or<std::string>("");
		lua["game"]["loadScene"] = "";
		return scene;
	}

	const std::wstring Lua::getSubtitleToBeLoaded() {
		if (lua["game"]["setSubtitle"].get_type() == sol::type::nil) {
			lua["game"]["setSubtitle"] = "";
			return L"";
		}

		std::wstring dest = lua["game"]["setSubtitle"].get_or<std::wstring>(L"");
		lua["game"]["setSubtitle"] = "";
		
		return dest;
	}

	void Lua::loadScene(Scene* scene) {
		scene_temp = scene;
		auto l = lua["scenes"][scene->name];
		auto it_objects = [this](std::pair<sol::object, sol::object> o) { 
			readObject(o);
		};
		auto it_walkboxes = [this](std::pair<sol::object, sol::object> o) {
			readWalkbox(o);
		};
		auto it_zoomlines = [this](std::pair<sol::object, sol::object> o) {
			readZoomline(o);
		};

		if (!l.valid())
			goto clean_and_end;

		l["objects"].get<sol::table>().for_each(it_objects);
		l["walkboxes"].get<sol::table>().for_each(it_walkboxes);
		l["zoomlines"].get<sol::table>().for_each(it_zoomlines);

	clean_and_end:
		scene_temp = nullptr;
	}



	void Lua::readObject(std::pair<sol::object, sol::object> o) {
		if (!o.second.is<sol::table>())
#if defined _DEBUG || !defined NO_EXCEPTIONS
			throw Exception::noObjectTable;
#else
			return;
#endif
		std::list<char> actions;
		auto getActions = [&actions](std::pair<sol::object, sol::object> a) {
			if (a.second.is<char>())
				actions.push_back(a.second.as<char>());
		};
		auto t = o.second.as<sol::table>();
		if (t[5].get_type() == sol::type::table)
			t[5].get<sol::table>().for_each(getActions);
		std::string texture = t[4].get_or<std::string>("r0,0");
		if (texture[0] == 'm') {
			
			scene_temp->addMoveableObject(lua, t[4].get_or<std::string>("r0,0"), sf::Vector3i(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0)), o.first.as<std::string>(), actions);
			std::shared_ptr<MoveableObject> i = std::static_pointer_cast<MoveableObject>(scene_temp->objects.back());
			//Scale up to 600%, for the pixel feeling
			i->sprite->setScale(5,5);
			std::hash<std::string> hash;
			auto getStates = [i, hash](std::pair<sol::object, sol::object> o) {
				auto s = o.second.as<sol::table>();
				if (!o.second.is<sol::table>())
					return;
				pc::hash state = hash(s[1].get_or<std::string>(""));
				sf::IntRect rect(s[2].get_or(0), s[3].get_or(0), s[4].get_or(0), s[5].get_or(0));
				i->states.push_back(std::make_pair(state, rect));
			};
			auto getAreas = [i, hash](std::pair<sol::object, sol::object> o) {
				auto s = o.second.as<sol::table>();
				if (!o.second.is<sol::table>())
					return;
				pc::hash state = hash(s[1].get_or<std::string>(""));
				sf::IntRect rect(s[2].get_or(0), s[3].get_or(0), s[4].get_or(0), s[5].get_or(0));
				i->areas.push_back(std::make_pair(rect, state));
			};
			auto getPoints = [&i, hash](std::pair<sol::object, sol::object> o) {
				auto s = o.second.as<sol::table>();
				if (!o.second.is<sol::table>())
					return;
				pc::hash name = hash(s[3].get_or<std::string>(""));
				sf::Vector2f pos(s[1].get_or(0), s[2].get_or(0));
				i->points.push_back(std::make_pair(name, pos));
			};

			t[6].get<sol::table>().for_each(getStates);
			t[7].get<sol::table>().for_each(getAreas);
			t[8].get<sol::table>().for_each(getPoints);
		} else
			scene_temp->addObject(t[4].get_or<std::string>("r0,0"), sf::Vector3i(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0)), o.first.as<std::string>(), actions);
	}




	void Lua::readWalkbox(std::pair<sol::object, sol::object> o) {
		if (!o.second.is<sol::table>())
#if defined _DEBUG || !defined NO_EXCEPTIONS
			throw Exception::noObjectTable;
#else
			return;
#endif
		auto t = o.second.as<sol::table>();
		scene_temp->addWalkbox(sf::IntRect(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0), t[4].get_or(0)), t[5].get_or(true));
	}

	void Lua::readZoomline(std::pair<sol::object, sol::object> o) {
		if (!o.second.is<sol::table>())
#if defined _DEBUG || !defined NO_EXCEPTIONS
			throw Exception::noObjectTable;
#else
			return;
#endif
		auto t = o.second.as<sol::table>();
		scene_temp->addZoomline(sf::IntRect(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0), t[4].get_or(0)), t[5].get_or<float>(0), t[6].get_or(true));
	}
}
