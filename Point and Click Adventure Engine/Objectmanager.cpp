#include "Objectmanager.hpp"

namespace pc {
	namespace Lvleditor {


		Objectmanager::Objectmanager() {

		}

		Objectmanager::~Objectmanager() {

		}

		void Objectmanager::draw() {
			ImGui::Begin("Objectmanager", &is_open);
			ImGui::Columns(2, "col", 0);
			object_filter.Draw("Search", 333);
			if (ImGui::IsItemHoveredRect())
				ImGui::displayFilterUsage();
			ImGui::BeginChild("Objectlist", ImVec2(380, 150), 1);
			for each (std::string line in object_list)
			{
				if (object_filter.PassFilter(line.data())) {
					if (ImGui::Selectable(line.data())) {
						input_buffer = line;
					}

				}

			}

			ImGui::EndChild();

			ImGui::BeginChild("btnCntrl", ImVec2(400, 20));
			if (ImGui::Button("Add", ImVec2(93.5, 0))) {

			}
			ImGui::SameLine(0, 2);
			ImGui::Button("Remove", ImVec2(93.5, 0));
			ImGui::SameLine(0, 2);
			ImGui::Button("Refresh", ImVec2(93.5, 0));
			ImGui::SameLine(0, 2);
			ImGui::Button("Save", ImVec2(93.5, 0));
			ImGui::EndChild();
			ImGui::NextColumn();
			ImGui::InputText("Key", input_buffer, input_buffer.capacity());
			ImGui::InputText("Default name", input_buffer, input_buffer.capacity());
			ImGui::InputText("Path", input_buffer, input_buffer.capacity());


			ImGui::Checkbox("interactable", &testing);
			if (testing) {
				ImGui::BeginGroup();
				ImGui::Checkbox("lookable", &t1);
				if (ImGui::RadioButton("collectable", t2)) {
					t2 = 1;
					t3 = 0;
				}
				if (ImGui::RadioButton("usable", t3)) {
					t2 = 0;
					t3 = 1;
				}
				ImGui::EndGroup();
			}


			ImGui::End();
		}

		auto Objectmanager::reportOpeningAction() -> std::string {
			std::string temp = opening_action;
			opening_action = "";
			return temp;
		}
		auto Objectmanager::reportClosingAction() -> std::string {
			if (!is_open) {
				is_open = 1;
				return "objectmanager";
			}
			else
				return "";
		}
		void Objectmanager::loadObjects() {

		}
		void Objectmanager::saveObjects() {

		}
	} //Lvleditor
} //pc
