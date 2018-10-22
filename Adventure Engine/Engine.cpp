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
#include "LuaObject.hpp"
#include "SpriteNode.hpp"
#include <string>
#include <utility>


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

		/*l.new_usertype<SceneNode>("SceneNode");

		l.new_usertype<SpriteNode>("SpriteNode", sol::constructors<
			SpriteNode(sf::Texture&),
			SpriteNode(sf::Texture&, const sf::IntRect&)>(),
			sol::base_classes, sol::bases<SceneNode, sf::Transformable, sf::Drawable>(),

			"setPosition", sol::resolve<void(float, float)>(&SpriteNode::Transformable::setPosition),
			"setScale", sol::overload(&SpriteNode::getScale, sol::resolve<void(float, float)>(&SpriteNode::setScale)),
			"setOrigin", sol::resolve<void(float, float)>(&SpriteNode::setOrigin),
			"texture", &SpriteNode::setTexture,
			"move", sol::resolve<void(float, float)>(&SpriteNode::move),
			"rotate", &SpriteNode::rotate,
			"scale", sol::resolve<void(float, float)>(&SpriteNode::scale),
			"update", &SpriteNode::updateFunction,
			"set", &SpriteNode::addMember,
			"get", &SpriteNode::getMember
			);

		

		l["objects"]["setLayer"] = [this](std::unique_ptr<SpriteNode>& obj, size_t layer) {
			auto r = scene_layers.find(layer);
			if (r == scene_layers.end()) {
				auto o = std::make_unique<SceneNode>();
				scene_layers.emplace(layer, o.get());
				scene_graph.attachChild(std::move(o));
			} else if (r->second == nullptr) {
				auto o = std::make_unique<SceneNode>();
				r->second = o.get();
				scene_graph.attachChild(std::move(o));
			}
			r = scene_layers.find(layer);
			r->second->attachChild(std::move(obj));

		};

		l["objects"]["attach"] = [](SpriteNode* parent, std::unique_ptr<SpriteNode>& obj) {
			parent->attachChild(std::move(obj));
		};

		l["Object"] = [this](size_t texture) -> std::unique_ptr<SpriteNode> {
			const itl::Texture* t = texture_manager.find(texture);
			return std::make_unique<SpriteNode>(t->texture_ref, t->rect);
		};*/

		l["changeScene"] = [this](const std::string& name) {
			lua.eventHandler["clearSubscriptions"].call(lua.eventHandler);
			lua.lua.script_file(".\\data\\scenes\\" + name + ".lua");
			scene_name = name;
		};

		l["utils"]["hash"]["string"] = [](const std::string& s) {
			std::hash<std::string> hs;
			return hs(s);
		};

		lua.postinit();
		// Create the window
		window.create(sf::VideoMode(1600, 900), "ITL Engine");
		ImGui::SFML::Init(window);
		window.setFramerateLimit(60);


		//Load the textures here

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
		lua.eventHandler["update"].call(clock.restart());
		//scene_graph.update(clock.restart(), last_event.get());
	}

	void Engine::render() {
		if (has_focus) {
			window.clear();
			window.draw(ecs_wrapper);
			//window.draw(scene_graph);

			if (draw_imgui)
				ImGui::SFML::Render(window);
		}
		window.display();
	}

	void Engine::processEvents() {
		last_event.release();
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
						sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
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
				case sf::Event::MouseMoved:
					last_event = std::make_unique<Event>(Event('h', event.mouseMove.x, event.mouseMove.y, true));
					break;
				case sf::Event::MouseButtonPressed:	{
						char btn = 'h';
						switch (event.mouseButton.button) {
							case sf::Mouse::Button::Left:
								btn = 'l';
								break;
							case sf::Mouse::Button::Middle:
								btn = 'm';
								break;
							case sf::Mouse::Button::Right:
								btn = 'r';
								break;
							case sf::Mouse::Button::XButton1:
								btn = '1';
								break;
							case sf::Mouse::Button::XButton2:
								btn = '2';
								break;
						}
						last_event = std::make_unique<Event>(Event(btn, event.mouseButton.x, event.mouseButton.y, false));
						break;
					}
				case sf::Event::MouseButtonReleased: {
						char btn = 'h';
						switch (event.mouseButton.button) {
							case sf::Mouse::Button::Left:
								btn = 'l';
								break;
							case sf::Mouse::Button::Middle:
								btn = 'm';
								break;
							case sf::Mouse::Button::Right:
								btn = 'r';
								break;
							case sf::Mouse::Button::XButton1:
								btn = '1';
								break;
							case sf::Mouse::Button::XButton2:
								btn = '2';
								break;
						}
						last_event = std::make_unique<Event>(Event(btn, event.mouseButton.x, event.mouseButton.y, true));
						break;
					}
				case sf::Event::KeyReleased:
					switch (event.key.code) {
						case sf::Keyboard::F3:
							if (event.key.shift) {
								std::string scene = scene_name;
								lua.lua.script_file("engine/engine.lua");
								lua.lua["changeScene"].call(scene);
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

		lua.eventHandler["setEvents"].call(lua.eventHandler, events);
		lua.eventHandler["handleEvents"].call(lua.eventHandler);
	}
}
