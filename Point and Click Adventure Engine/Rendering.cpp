#pragma once

#include "Rendering.h"

namespace pc {
	void Rendering::redraw() {
		window.clear();
		for each (sf::Drawable drawable in drawList)
		{
			window.draw(drawable);
		}
		window.display();
	}

	void Rendering::createWindow(sf::VideoMode videoMode) {

	}
}