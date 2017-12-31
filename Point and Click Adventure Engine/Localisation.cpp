#include "Localisation.hpp"
#include "imgui-helper.h"

#include <SFML\Window\Keyboard.hpp>
#include <iostream>

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
			if (ImGui::IsItemHoveredRect())
				ImGui::displayFilterUsage();

			ImGui::BeginChild("Objectlist", ImVec2(380, 150), 1);
			for each (std::pair<std::string, Item> line in localise_keys)
			{
				if (object_filter.PassFilter(line.first.data())) {
					if (ImGui::Selectable(line.first.data()))
						selectKey(line.first.data());
					original_key = line.first.data();
					if (ImGui::IsItemHovered()) {
						ImGui::BeginTooltip();
						ImGui::Text(line.second.text.data());
						ImGui::Text(line.second.audio_path.data());
						ImGui::EndTooltip();
					}
				}
			}
			ImGui::EndChild();
			if (ImGui::Button("New")) {
				supress_modal_showing = true;
				selectKey("");
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove")) {
				show_remove = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Save")) {
				selectKey(current_key);
			}
			ImGui::NextColumn();

			ImGui::Combo("##Language", &language_index, languages);
			ImGui::SameLine(0.f, 3.f);
			if (ImGui::Button("Language"))
				ImGui::OpenPopup("Languagesettings");

			showModalLanguages();
			if (ImGui::InputText("Key", current_key, 255)) {
				std::cout << current_key;
			}
			if (ImGui::InputTextMultiline("Text", text, 1000)) {
				std::cout << text;
			}
			if (ImGui::InputText("Audio Path", audio_path, 255)) {
				std::cout << audio_path;
			}
			if (show_error)
				showModalError();
			if (show_remove)
				removeKey(current_key);
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

		void Localisation::loadLanguages() {

		}
		void Localisation::saveLanguages() {

		}

		void Localisation::showModalLanguages() {
			if (ImGui::BeginPopupModal("Languagesettings", &modal_is_open, ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::InputText("##Language_add", language_code, language_code.capacity());
				if (ImGui::Button("Add")) {
					languages.push_back(language_code);
					language_code = "";
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

		void Localisation::loadLocaliseKeys() {

		}

		void Localisation::saveLocaliseKeys() {

		}

		void Localisation::selectKey(const std::string & key) {
			if (current_key != "") {
				auto current = localise_keys.find(current_key);
				Item item;
				item.text = text;
				item.audio_path = audio_path;
				if (current != localise_keys.end()) {
					localise_keys.at(current_key).audio_path = audio_path;
					localise_keys.at(current_key).text = text;
				}
				else {
					//Key was changed or is non-existent
					current = localise_keys.find(original_key);
					if (current != localise_keys.end()) {
						//Key was changed, so delete the old
						localise_keys.erase(original_key);
					}
					localise_keys.emplace(std::pair<std::string, Item>(current_key, item));
				}
			}
			else {
				if (!supress_modal_showing)
					show_error = true;
				else
					supress_modal_showing = false;
			}

			if (key != "") {
				auto current = localise_keys.find(key);
				if (current != localise_keys.end()) {
					current_key = key;
					text = current->second.text;
					audio_path = current->second.audio_path;
					return;
				}
			}
				current_key = "";
				text = "";
				audio_path = "";
			
		}

		void Localisation::removeKey(const std::string & key) {
			ImGui::OpenPopup("Remove");
			ImGui::BeginPopupModal("Remove");
			const std::string delete_message = "Delete \"" + key + "\"?";
			ImGui::TextColored(ImVec4(255, 0, 0, 255), delete_message.data());
			if (ImGui::Button("Confirm delete")) {
				show_remove = false;
				if (localise_keys.find(key) != localise_keys.end()) {
					localise_keys.erase(key);
					current_key = "";
					text = "";
					audio_path = "";
				}
				else
					show_error = true;
				show_remove = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		void Localisation::showModalError() {
			ImGui::OpenPopup("Error##Empty");
			ImGui::BeginPopupModal("Error##Empty");
			ImGui::TextColored(ImVec4(255, 0, 0, 255), "Error: Key is not valid!");
			if (ImGui::Button("OK##modal_empty", ImVec2(100, 20))) {
				show_error = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}
