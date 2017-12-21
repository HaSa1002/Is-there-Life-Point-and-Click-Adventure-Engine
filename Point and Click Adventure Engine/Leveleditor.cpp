#include "Leveleditor.hpp"
#include "imgui-helper.h"

#include <imgui-SFML.h>

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
		renderer.addGUI(1);
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

