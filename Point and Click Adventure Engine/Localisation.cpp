#include "Localisation.hpp"
#include "imgui-helper.h"



namespace pc {
	namespace Lvleditor {
		Localisation::Localisation() {

		}

		Localisation::~Localisation() {

		}

		void Localisation::draw() {
			ImGui::Begin("Localisation", &is_open);
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
					}

				}

			}

			ImGui::EndChild();
			if (ImGui::Button("New")) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {

			}
			ImGui::SameLine();
			if (ImGui::Button("Save")) {

			}
			ImGui::NextColumn();

			ImGui::Combo("##Language", &language_index, languages);
			ImGui::SameLine(0.f, 3.f);
			if (ImGui::Button("Language"))
				ImGui::OpenPopup("Languagesettings");

			showModalLanguages();
			
			ImGui::InputText("Key", current_key, current_key.capacity());
			ImGui::InputTextMultiline("Text", text, text.capacity());

			ImGui::End();
		}

		auto Localisation::reportOpeningAction() -> std::string {
			std::string temp = opening_action;
			opening_action = "";
			return temp;
		}

		auto Localisation::reportClosingAction() -> std::string {
			if (!is_open) {
				is_open = 1;
				return "localisation";
			}
			else
				return "";
			
			
			
		}
		void Localisation::showModalLanguages() {
			if (ImGui::BeginPopupModal("Languagesettings", &modal_is_open, ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::InputText("##Language_add", add_key, add_key.capacity());
				if (ImGui::Button("Add")) {
					languages.push_back(add_key);
					add_key = "";
				}
				ImGui::Separator();
				ImGui::Combo("##Language_modal", &modal_language_index, languages);
				if (ImGui::Button("Delete")) {
					languages.at(static_cast<size_t>(modal_language_index)) = languages.back();
					languages.pop_back();
				}
				ImGui::EndPopup();
			}
			else
				modal_is_open = 1;
		}

	}
}
