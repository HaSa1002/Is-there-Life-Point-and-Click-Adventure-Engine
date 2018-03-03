#include "Mainmenue.hpp"

#include "imgui-helper.h"

#include "imgui-SFML.h"



namespace pc {
	namespace Lvleditor {
		Mainmenue::Mainmenue() {

		}

		Mainmenue::~Mainmenue() {

		}

		void Mainmenue::draw() {
			ImGui::Begin("Mainmenue");
			ImGui::Text("SFML Point & Click Adventure Engine");
			ImGui::Text("Version 0.3.0.0-dev");
			ImGui::Separator();
			ImGui::Columns(2, "col", 0);
			if (ImGui::Button("Scenemanager")) {
				opening_action = "scenemanager";
			}
			if (ImGui::Button("Objectmanager")) {
				opening_action = "objectmanager";
			}
			if (ImGui::Button("Cutscene-editor")) {

			}
			if (ImGui::Button("Settings")) {

			}
			ImGui::NextColumn();
			if (ImGui::Button("Create Scene")) {

			}
			if (ImGui::Button("Localisation")) {
				opening_action = "localisation";
			}
			if (ImGui::Button("Scripts")) {

			}
			if (ImGui::Button("Help")) {

			}
			ImGui::Columns(1);
			ImGui::Separator();
			if (ImGui::Button("Close")) {
				//Closeevent senden
			}
			ImGui::End();
			ImGui::ShowTestWindow();
		}

		auto Mainmenue::reportOpeningAction()->std::string {
			std::string temp = opening_action;
			opening_action = "";
			return temp;
		}
		auto Mainmenue::reportClosingAction() -> std::string {
				return "";
		}

	}
}