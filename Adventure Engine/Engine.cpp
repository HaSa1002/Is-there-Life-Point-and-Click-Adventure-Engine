////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#include "Engine.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////



namespace itl {

	Engine::Engine() {
		start();
	}
	void Engine::start() {
		lua.init();
		// Bind the classes to Lua
		sol::state& l = lua.lua;
		l.script(R"(
		objects = {};
		utils = {};
		utils.hash = {})");
		l.new_usertype<TextureManager>("textures", sol::constructors<
			TextureManager()>(),
			"find", &TextureManager::find,
			"add", &TextureManager::add,
			"clear", &TextureManager::clear,
			"build", &TextureManager::build
			);

		l.new_usertype<Texture>("texture");

		l["tm"] = &texture_manager;

		l["utils"]["hash"]["string"] = [](const std::string& s) {
			std::hash<std::string> hs;
			return hs(s);
		};

		lua.postinit();
		// Create the window

		//Load the Cursor
		cursor_normal_img.loadFromFile("data/textures/cursor/normal.png");
		cursor_normal.loadFromPixels(cursor_normal_img.getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(0,0));


		window.create(sf::VideoMode(1600, 900), "ITL Engine");
		window.setMouseCursor(cursor_normal);
		ImGui::SFML::Init(window);
		//window.setFramerateLimit(60);

		clock.restart();
		main();
	}
	void Engine::main() {
		while (window.isOpen()) {
			this->processEvents();
			this->logicUpdate();
			this->render();
		}
	}

	void Engine::logicUpdate() {
		if (lua.asyncInProgress) {
			//if (lua.asyncLoad.wait_for(std::chrono::duration<long, std::atto>(1)) == std::future_status::ready) {
				lua.asyncReturn["onFinish"].call(lua.asyncReturn);
				lua.asyncInProgress = false;
			//}
		}

		lua.lua["state"]["update"].call(lua.lua["state"], clock.restart().asSeconds());
	}

	void Engine::render() {
		if (has_focus || true) {
			window.clear();
			window.draw(ecs_wrapper);

			if (draw_imgui)
				ImGui::SFML::Render(window);
		}
		window.display();
	}

	void Engine::processEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (draw_imgui)
				ImGui::SFML::ProcessEvent(event);

			events.push_back(event);

			switch (event.type) {
				case sf::Event::Closed:
					ImGui::SFML::Shutdown();
					window.close();
					break;
				case sf::Event::Resized: {
						sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
						view = std::move(sf::View(visibleArea));
						window.setView(view);
						break;
					}
				case sf::Event::LostFocus:
					has_focus = false;
					break;
				case sf::Event::GainedFocus:
					has_focus = true;
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code) {
						case sf::Keyboard::F3:
							if (event.key.shift) {
								std::string scene = scene_name;
								lua.postinit();
							}
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}

		lua.lua["state"]["setInput"].call(lua.lua["state"], events);
		lua.lua["state"]["handleInput"].call(lua.lua["state"]);
		events.clear();
	}
}
