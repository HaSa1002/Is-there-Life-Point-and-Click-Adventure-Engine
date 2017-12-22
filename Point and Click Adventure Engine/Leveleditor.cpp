////////////////////////////////////////////////////////////
// 
// SFML Point and Click Adventure Engine (ITLengine)
// Copyright (c) 2017 Johannes Witt
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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Leveleditor.hpp"
#include "imgui-helper.h"
// Dependencies
#include <imgui-SFML.h>
// STD Library
#include <iostream>

namespace pc {
	Leveleditor::Leveleditor() {

	}

	Leveleditor::~Leveleditor() {

	}

	void Leveleditor::start() {
		//Startup
		renderer.createWindow();
		ImGui::SFML::Init(renderer.getWindowObject());
		renderer.imgui_rendering();
		menue.open("mainmenue");
		this->main();
		//End
		ImGui::SFML::Shutdown();
	}

	void Leveleditor::main() {
		renderer.getWindowObject().resetGLStates();
		sf::Clock clock;
		while (renderer.isOpen()) {
			this->processEvents();
			menue.draw(renderer);
			renderer.redraw();
		}
	}

	void Leveleditor::processEvents() {
		sf::Event event;
		while (renderer.getWindowObject().pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) {
				renderer.closeWindow();
			}
		}
		
	}

}

