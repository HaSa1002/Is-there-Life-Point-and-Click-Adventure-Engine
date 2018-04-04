#include "Engine.hpp"
//#include "ImGui.hpp"


namespace pc {

	void Engine::start() {
		//Load the config file, then set
		if (!lua.init())
			return;
		
		//See the Editor.conf.lua to get an overview of what is possible
		if (!lua.editorConfig())
			return;
		
		auto editor = lua.lua["editor"];
		rendering.createWindow(editor["title"], editor["fullscreen"], sf::VideoMode(editor["solution"][1].get_or(1600), editor["solution"][2].get_or(900)));
		rendering.imgui_rendering(true);

		//Testraum laden
		scene.name = "lua_testscene";
		lua.loadScene(scene.name, &scene);
		for (auto& i : scene.objects) {
			rendering.add(std::make_shared<sf::Sprite>(i.sprite), i.layer);
		}
		
		main();
	}

	void Engine::main() {
		
		sf::Clock clock;
		while (rendering.isOpen()) {
			processEvents();
			rendering.render();
		}
	}
	void Engine::processEvents() {
		//We do the callbacks if wanted
		while (!rendering.events.empty()) {
			sf::Event event = rendering.events.front();
			rendering.events.pop();
			switch (event.type) {
			case sf::Event::TextEntered:
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)	{
				case sf::Keyboard::F3:
					if (event.key.shift) {
						rendering.remove();
						scene.reset();
						lua.init();
						lua.loadScene(scene.name, &scene);
						for (auto& i : scene.objects) {
							rendering.add(std::make_shared<sf::Sprite>(i.sprite), i.layer);
						}
						rendering.removeGUI();
						editor_mode = !editor_mode; //We are cheating here, so that we are refreshing just if needed
					}
					editor_mode = !editor_mode;
					if (editor_mode) {
						scene.createEditorHelper();
						for (auto& i : scene.helper) {
							rendering.addGUI(std::make_shared<sf::RectangleShape>(i), 0);
						}
						
					}
					else
						rendering.removeGUI();
					break;
				default:
					break;
				}
				break;
			case sf::Event::MouseWheelMoved:
				break;
			case sf::Event::MouseWheelScrolled:
				break;
			case sf::Event::MouseButtonPressed:
			
				break;
			case sf::Event::MouseButtonReleased:
			{
				sf::Vector2f mouse_pos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
				scene.objects.sort(scene.sort_objects_by_layer);
				for (auto& i : scene.objects) {
					if ((i.type == 's' && i.sprite.getGlobalBounds().contains(mouse_pos)) || (i.type == 'c' && i.click.getGlobalBounds().contains(mouse_pos))) {
						auto callback = lua.lua["scenes"][scene.name][i.callback];
						switch (event.mouseButton.button)
						{
						case sf::Mouse::Button::Left:
							if (i.has_action('u'))
								callback.call('u');
							else if (i.has_action('c'))
								callback.call('c');
							goto end_for;
						case sf::Mouse::Button::Right:
							if (i.has_action('l'))
								callback.call('l');
							goto end_for;
						default:
							break;
						}
					}
				}
			end_for:
				;
			}
				break;
			case sf::Event::MouseMoved:

				break;
			case sf::Event::MouseEntered:
				break;
			case sf::Event::MouseLeft:
				break;
			case sf::Event::JoystickButtonPressed:
				break;
			case sf::Event::JoystickButtonReleased:
				break;
			case sf::Event::JoystickMoved:
				break;
			case sf::Event::JoystickConnected:
				break;
			case sf::Event::JoystickDisconnected:
				break;
			case sf::Event::TouchBegan:
				break;
			case sf::Event::TouchMoved:
				break;
			case sf::Event::TouchEnded:
				break;
			case sf::Event::SensorChanged:
				break;
			default:
				break;
			}
		}
	}

}