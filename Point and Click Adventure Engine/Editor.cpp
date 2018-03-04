////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
// Copyright (c) 2017 Johannes Witt (johawitt@outlook.de)
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
#include "Editor.hpp"
#include "imgui-helper.h"

#include <imgui-SFML.h>

#include <iostream>

namespace pc {

	Editor::Editor() {

	}

	Editor::~Editor() {

	}

	void Editor::start() {
		//Startup
		engine.getRendering().createWindow();
		ImGui::SFML::Init(engine.getRendering().getWindowObject());
		engine.getRendering().imgui_rendering(true);
		menue.open("mainmenue");
		this->main();
		//End
		ImGui::SFML::Shutdown();
	}

	void Editor::main() {
		engine.getRendering().getWindowObject().resetGLStates();
		sf::Clock clock;
		while (engine.getRendering().isOpen()) {
			this->processEvents();
			engine.getEcs().run();
			menue.draw(engine.getRendering());
			engine.getRendering().render();
		}
	}

	void Editor::processEvents() {
		sf::Event event;
		while (engine.getRendering().getWindowObject().pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			mb::Message message;
			message.type = mb::MessageType::sfEvent;
			message.data.push_back(static_cast<void*>(&event));
			engine.getBus().send(message);
		}
		
	}

}

