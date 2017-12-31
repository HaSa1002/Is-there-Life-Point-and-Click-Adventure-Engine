#include "Menuemanager.hpp"

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
				active_menues.push_back(&mainmenue);
			}
			if (menue_id == "objectmanager") {
				active_menues.push_back(&objectmanager);
			}
			if (menue_id == "scenemanager") {
				active_menues.push_back(&scenemanager);
			}
			if (menue_id == "localisation") {
				active_menues.push_back(&localisation);
			}
				
			active_menues_id.push_back(menue_id);
		}

		bool Menuemanager::close(std::string menue_id) {
			if (menue_id == "")
				return 0;
			if (menue_id == "objectmanager") {
				active_menues.remove(&objectmanager);
			}
			if (menue_id == "scenemanager") {
				active_menues.remove(&scenemanager);
			}
			if (menue_id == "localisation") {
				active_menues.remove(&localisation);
			}

			active_menues_id.remove(menue_id);
			return 1;
		}

		void Menuemanager::draw(pc::Rendering& renderer) {
			ImGui::SFML::Update(renderer.getWindowObject(), clock.restart());
			for each (pc::Lvleditor::Menue* menue in active_menues)
			{
				menue->draw();
				open(menue->reportOpeningAction());
				if (close(menue->reportClosingAction()))
					break;
			}
		}

	} //Lvleditor
} //pc
