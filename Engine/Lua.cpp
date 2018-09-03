#include "Lua.hpp"
#include "config.hpp"
#include <fstream>

namespace pc {
	void Lua::init() {
		try {
			lua.script_file("Engine.lua");
		} catch (sol::error err) {
			printf("%s\n", err.what());
		}
	}

	void Lua::preInit() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::io, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
		lua.script(R"(
			scenes = {}
			localisations = {}
			game = {}
			pc = {}
			)");
	}

	void Lua::setScene(const std::string & scene) {
		scene_temp->name = scene;
	}

	void Lua::setScene(pc::Scene & scene) {
		scene_temp = &scene;
	}


	void Lua::call(pc::Scene & scene, const std::string & object, const char action) {
		std::string callAction;
		switch (action) {
			case 'c':
			callAction = "onCollect";
			break;
			case 'u':
			callAction = "onUse";
			break;
			case 'l':
			callAction = "onLook";
			break;
			case 'h':
			callAction = "onHover";
			break;
			default:
			throw std::invalid_argument(action + " is not a valid Action.");
		}
		lua["scenes"][scene.name]["objects"][object][callAction].call();
	}

	void Lua::call(std::chrono::steady_clock::time_point function) {
		callbacks.find(function)->second.call();
	}

	const ScriptEngine::EditorValues Lua::getEditorConfig() {
		lua.script(R"(
			editor = {
				solution = {1600, 900},
				title = "Is there Life? | Engine",
				fullscreen = false,
			}
			)");

		try {
			lua.script_file("Editor.conf.lua");
		} catch (sol::error err) {
			printf("%s\n", err.what());
		}

		return EditorValues(lua["editor"]["title"].get_or<std::string>(""),
			lua["editor"]["fullscreen"].get_or(false),
			lua["editor"]["solution"][0].get_or(1600),
			lua["editor"]["solution"][0].get_or(900));
	}

	const ScriptEngine::SubtitleValue Lua::getSubtitleSettings() {
		return SubtitleValue(lua["game"]["subtitleFont"].get_or<std::string>(""), lua["game"]["subtitleSize"].get_or(30),
			lua["game"]["subtitleColor"][1].get_or(255), lua["game"]["subtitleColor"][2].get_or(255), lua["game"]["subtitleColor"][3].get_or(255),
			lua["game"]["subtitleColor"][4].get_or(255));
	}




	//TODO: Bind the Functions to Lua in the pc Table
	void Lua::bindFunctions() {
		lua["pc"]["loadScene"] = [this](const std::string& scene) {
			setScene(scene);
			_scene_loadScene();
		};

		lua["pc"]["playAnimatedMove"] = [this](const std::string& obj, const std::string& p, float sec) {
			std::hash<std::string> h;
			auto t = std::static_pointer_cast<MoveableObject>(scene_temp->getObject(obj));
			if (t)
				t->move(h(p), sf::seconds(sec));
			else
				printf("%s couldn't be found.\n", obj.data());
		};

		lua["pc"]["setSubtitle"] = [this](const std::wstring& text) {
			_subtitle_setText(text);
		};

		lua["pc"]["addTextures"] = [this](sol::table t) {
			auto it_textures = [this](std::pair<sol::object, sol::object> o) {
				scene_temp->res.addTexture(o.second.as<std::string>(), o.first.as<std::string>());
				
			};
			t.for_each(it_textures);
		};
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

	void Lua::loadScene(Scene& scene, bool addToRenderer) {
		scene_temp = &scene;
		auto l = lua["scenes"][scene.name];
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
		if (addToRenderer)
			_scene_addToRenderingFunction();
		if (l[scene_temp->name]["onEnter"].valid())
			l[scene_temp->name]["onEnter"].call();

	}

	void Lua::playAnimatedMove(const std::string & obj, const std::string & point, const float sec) {

	}


	void Lua::readObject(std::pair<sol::object, sol::object> o) {
		if (!o.second.is<sol::table>()) {
			_ASSERT_EXPR(false, "A Object was wrong");
			return;
		}
		std::list<char> actions;
		auto getActions = [&actions](std::pair<sol::object, sol::object> a) {
			if (a.second.is<char>())
				actions.push_back(a.second.as<char>());
		};
		auto t = o.second.as<sol::table>();
		if (t[5].get_type() == sol::type::table)
			t[5].get<sol::table>().for_each(getActions);
		std::string texture = t[4].get_or<std::string>("r0,0");

		std::hash<std::string> hash;

		std::shared_ptr<Animation> a;

		auto getStates = [&a, hash](std::pair<sol::object, sol::object> o) {
			auto s = o.second.as<sol::table>();
			if (!o.second.is<sol::table>())
				return;
			pc::hash state = hash(s[1].get_or<std::string>(""));
			sf::IntRect rect(s[2].get_or(0), s[3].get_or(0), s[4].get_or(0), s[5].get_or(0));
			a->states.push_back(std::make_pair(state, rect));
		};




		switch (texture[0]) {
			case 'm': {
				scene_temp->addMoveableObject(t[4].get_or<std::string>("r0,0"), sf::Vector3i(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0)), o.first.as<std::string>(), actions);
				std::shared_ptr<MoveableObject> i = std::static_pointer_cast<MoveableObject>(scene_temp->objects.back());
				a = i;
				//TODO: Set this value in the settings
				//Scale up to 500%, for the pixel feeling
				i->sprite->setScale(5, 5);

				auto getAreas = [&i, hash](std::pair<sol::object, sol::object> o) {
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
					sf::Vector2f pos(s[1].get_or(0.f), s[2].get_or(0.f));
					i->points.push_back(std::make_pair(name, pos));
				};

				t[6].get<sol::table>().for_each(getStates);
				t[7].get<sol::table>().for_each(getAreas);
				t[8].get<sol::table>().for_each(getPoints);

				}
			break;
			case 'a': {
				scene_temp->addAnimatedObject(t[4].get_or<std::string>("r0,0"), sf::Vector3i(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0)), o.first.as<std::string>(), actions);
				std::shared_ptr<TimedAnimatedObject> i = std::static_pointer_cast<TimedAnimatedObject>(scene_temp->objects.back());
				a = i;
				//TODO: Set this value in the settings
				//Scale up to 500%, for the pixel feeling
				i->sprite->setScale(5, 5);

				auto getTimes = [&i, hash](std::pair<sol::object, sol::object> o) {
					auto s = o.second.as<sol::table>();
					if (!o.second.is<sol::table>())
						return;
					pc::hash state = hash(s[1].get_or<std::string>(""));
					sf::Time time = sf::seconds(s[2].get_or<float>(0));
					i->times.push_back(std::make_pair(state, time));
				};


				t[6].get<sol::table>().for_each(getStates);
				t[7].get<sol::table>().for_each(getTimes);
				}
			break;

			case 't':
			case 'r':
			default:
				scene_temp->addObject(t[4].get_or<std::string>("r0,0"), sf::Vector3i(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0)), o.first.as<std::string>(), actions);

			break;
		}
			
	}




	void Lua::readWalkbox(std::pair<sol::object, sol::object> o) {
		if (!o.second.is<sol::table>()) {
			_ASSERT_EXPR(false, "A Walkbox was wrong");
			return;
		}
		auto t = o.second.as<sol::table>();
		scene_temp->addWalkbox(sf::IntRect(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0), t[4].get_or(0)), t[5].get_or(true));
	}

	void Lua::readZoomline(std::pair<sol::object, sol::object> o) {
		if (!o.second.is<sol::table>()) {
			_ASSERT_EXPR(false, "A Zoomline was wrong");
			return;
		}
		auto t = o.second.as<sol::table>();
		scene_temp->addZoomline(sf::IntRect(t[1].get_or(0), t[2].get_or(0), t[3].get_or(0), t[4].get_or(0)), t[5].get_or<float>(0), t[6].get_or(true));
	}
}
