#include "Objectmanager.hpp"

namespace pc {
	namespace Lvleditor {


		Objectmanager::Objectmanager() {

		}

		Objectmanager::~Objectmanager() {

		}

		void Objectmanager::draw() {
			ImGui::Begin("Objectmanager");
			ImGui::Columns(2, "col", 0);

			ImGui::Text("Filter usage:\n"
				"  \"\"         display all lines\n"
				"  \"xxx\"      display lines containing \"xxx\"\n"
				"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
				"  \"-xxx\"     hide lines containing \"xxx\"");
			objectFilter.Draw("Search", 333);
			ImGui::BeginChild("Objectlist", ImVec2(380, 150), 1);
			for each (std::string line in objectList)
			{
				if (objectFilter.PassFilter(line.data())) {
					if (ImGui::Selectable(line.data())) {
						inputBuffer = line;
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
			ImGui::InputText("Key", inputBuffer, inputBuffer.capacity());
			ImGui::InputText("Default name", inputBuffer, inputBuffer.capacity());
			ImGui::InputText("Path", inputBuffer, inputBuffer.capacity());


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
		void Objectmanager::loadObjects() {

		}
		void Objectmanager::saveObjects() {

		}
	} //Lvleditor
} //pc
