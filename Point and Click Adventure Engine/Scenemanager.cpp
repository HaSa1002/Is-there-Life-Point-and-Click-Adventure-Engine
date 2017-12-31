#include "Scenemanager.hpp"
#include "imgui-helper.h"

namespace pc {
	namespace Lvleditor {
		Scenemanager::Scenemanager() {

		}

		Scenemanager::~Scenemanager() {

		}

		void Scenemanager::draw() {
			ImGui::Begin("Scenemanager", &is_open);
			ImGui::Columns(2, "col", 0);
			object_filter.Draw("Search", 333);
			if (ImGui::IsItemHoveredRect()) {
				ImGui::BeginTooltip();
				ImGui::Text("Filter usage:\n"
					"  \"\"         display all lines\n"
					"  \"xxx\"      display lines containing \"xxx\"\n"
					"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
					"  \"-xxx\"     hide lines containing \"xxx\"");
				ImGui::EndTooltip();
			}
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
			if (ImGui::Button("New")) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {

			}
			ImGui::NextColumn();
			

			ImGui::InputText("Sceneid", scene_id, scene_id.capacity());
			ImGui::InputText("Name", name, name.capacity());
			ImGui::InputTextMultiline("Description", description, description.capacity());

			if (ImGui::Button("Save")) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Rename")) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Start Sceneeditor")) {

			}
			ImGui::End();
		}

		auto Scenemanager::reportOpeningAction()-> std::string {
			return "";
		}
		auto Scenemanager::reportClosingAction() -> std::string {
			if (!is_open) {
				is_open = 1;
				return "scenemanager";
			}
			else return "";
		}
	}
}