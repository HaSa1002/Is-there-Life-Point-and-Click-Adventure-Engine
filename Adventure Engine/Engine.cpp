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
#include "SFML\Window\Event.hpp"

namespace itl {
	Engine::Engine() {
		start();
	}
	void Engine::start() {
		// Load the scriptmanager here
		// Create the window
		window.create(sf::VideoMode(1600,900), "ITL Engine");
		ImGui::SFML::Init(window);

		//Load the textures here

		main();
	}
	void Engine::main() {
		while (window.isOpen()) {
			// 1. process events
			this->processEvents();

			// 2. Logic

			// 3. Render
			clock.restart();
			if (has_focus) {
				window.clear();

				window.draw(scene_graph);

				if (draw_imgui)
					ImGui::SFML::Render(window);
			}
			window.display();
		}


	}

	void Engine::processEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (draw_imgui)
				ImGui::SFML::ProcessEvent(event);
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

				default:
					break;
			}
		}
	}
}
