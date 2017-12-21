#pragma once

#include "Rendering.hpp"
#include "Menuemanager.hpp"
#include <SFML\Window.hpp>
#include <AF\xml.h>
#include <imgui.h>



namespace pc {
	class Leveleditor
	{
	public:
		Leveleditor();
		~Leveleditor();
		void start();
		void main();

		void processEvents();

	private:
		Lvleditor::Menuemanager menue;
		Rendering renderer;
		
	};
} //pc