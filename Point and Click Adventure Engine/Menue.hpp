#pragma once

#ifndef PC_MENUE
#define PC_MENUE

//Header
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML\Window\Event.hpp>


namespace pc {
	class Menue {
	public:
		Menue();
		~Menue();

		void handleEvent(sf::Event event);




	private:

	};
}

#endif // !PC_MENUE