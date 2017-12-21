#include "Menuemanager.hpp"
#include "Rendering.hpp"
#include "Mainmenue.hpp"
#include "Objectmanager.hpp"

#include "imgui-SFML.h"


namespace pc {
	namespace Lvleditor {
		Menuemanager::Menuemanager() {
			clock.restart();
		}

		Menuemanager::~Menuemanager() {
			
		}

		void Menuemanager::open(std::string menue_id) {
			if (menue_id == "")
				return;
			for each (std::string menue in active_menues_id)
			{
				if (menue_id == menue)
					return;
			}
			if (menue_id == "mainmenue") {
				static pc::Lvleditor::Mainmenue mainmenue;
				active_menues.push_back(&mainmenue);
			}
			if (menue_id == "objectmanager") {
				static pc::Lvleditor::Objectmanager objectmanager;
				active_menues.push_back(&objectmanager);
			}
				
			active_menues_id.push_back(menue_id);
		}

		void Menuemanager::close(std::string menue_id) {

		}

		void Menuemanager::draw(pc::Rendering& renderer) {
			ImGui::SFML::Update(renderer.getWindowObject(), clock.restart());
			for each (pc::Lvleditor::Menue* menue in active_menues)
			{
				menue->draw();
				this->open(menue->reportOpeningAction());
			}
		}

	} //Lvleditor
} //pc
