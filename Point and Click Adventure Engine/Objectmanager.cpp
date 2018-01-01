////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Objectmanager.hpp"
#include "Datatypes.hpp"
#include "UtilityWindows.hpp"

namespace pc {
	namespace Lvleditor {


		Objectmanager::Objectmanager() {
			ptr = std::make_shared<Objectmanager>(*this);
		}
		////////////////////////////////////////////////////////////
		Objectmanager::~Objectmanager() {

		}
		////////////////////////////////////////////////////////////
		void Objectmanager::draw() {
			ImGui::Begin("Objectmanager", &is_open);
			ImGui::Columns(2, "col", 0);
			object_filter.Draw("Search", 333);
			if (ImGui::IsItemHoveredRect() && ImGui::IsWindowFocused())
				ImGui::displayFilterUsage();
			ImGui::BeginChild("Objectlist", ImVec2(380, 150), 1);
			for each (std::pair<std::string, Object> line in object_list) {
				if (object_filter.PassFilter(line.first.data())) {
					if (ImGui::Selectable(line.first.data())) {
						update(line.first.data());
						original_key = line.first.data();
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
			if (ImGui::Button("Save", ImVec2(93.5, 0))) {
				update(current_object_key);
			}
			ImGui::EndChild();
			ImGui::NextColumn();
			ImGui::InputText("Key", current_object_key, 255);
			ImGui::InputText("Name", current_object.name, 255);
			ImGui::InputText("Path", current_object.path, 255);


			ImGui::Checkbox("interactable", &current_object.interactable);
			if (current_object.interactable) {
				ImGui::BeginGroup();
				ImGui::Checkbox("lookable", &current_object.lookable);
				if (ImGui::RadioButton("collectable", current_object.collectable)) {
					current_object.collectable = 1;
					current_object.usable = 0;
				}
				if (ImGui::RadioButton("usable", current_object.usable)) {
					current_object.collectable = 0;
					current_object.usable = 1;
				}
				ImGui::EndGroup();
			}
			ImGui::Checkbox("is complex", &current_object.complex);
			if (current_object.complex)
				ImGui::InputText("Main Script Path", current_object.script, 255);

			if (show_error)
				UtilityWindows::errorModal("Error: Key is not valid!", show_error);

			ImGui::End();
		}
		////////////////////////////////////////////////////////////
		auto Objectmanager::reportOpeningAction() -> std::string {
			std::string temp = opening_action;
			opening_action = "";
			return temp;
		}
		////////////////////////////////////////////////////////////
		auto Objectmanager::reportClosingAction() -> std::string {
			if (!is_open) {
				is_open = 1;
				return "objectmanager";
			}
			else
				return "";
		}
		////////////////////////////////////////////////////////////
		auto Objectmanager::getPtr() -> const std::shared_ptr<Objectmanager>
		{
			const std::shared_ptr<Objectmanager> const_ptr = ptr;
			return const_ptr;
		}
		////////////////////////////////////////////////////////////
		void Objectmanager::loadObjects() {

		}
		////////////////////////////////////////////////////////////
		void Objectmanager::saveObjects() {

		}
		////////////////////////////////////////////////////////////
		void Objectmanager::update(const std::string& key) {
			if (current_object_key != "") {
				auto current = object_list.find(current_object_key);
				if (current != object_list.end()) {
					object_list.at(current_object_key).collectable = current_object.collectable;
					object_list.at(current_object_key).complex = current_object.complex;
					object_list.at(current_object_key).interactable = current_object.interactable;
					object_list.at(current_object_key).lookable = current_object.lookable;
					object_list.at(current_object_key).name = current_object.name;
					object_list.at(current_object_key).path = current_object.path;
					object_list.at(current_object_key).script = current_object.script;
					object_list.at(current_object_key).usable = current_object.usable;
				}
				else {
					//Key was changed or is non-existent
					current = object_list.find(original_key);
					if (current != object_list.end()) {
						//Key was changed, so delete the old
						object_list.erase(original_key);
					}
					object_list.insert(std::pair<std::string, Object>(current_object_key, current_object));
				}
			}
			else {
				if (!supress_error_showing)
					show_error = true;
				else
					supress_error_showing = false;
			}

			if (key != "") {
				auto current = object_list.find(key);
				if (current != object_list.end()) {
					current_object_key = key;
					original_key = key;
					current_object.collectable = current->second.collectable;
					current_object.complex = current->second.complex;
					current_object.interactable = current->second.interactable;
					current_object.lookable = current->second.lookable;
					current_object.name = current->second.name;
					current_object.path = current->second.path;
					current_object.script = current->second.script;
					current_object.usable = current->second.usable;
					return;
				}
			}
			current_object_key = "";
			current_object.collectable = false;
			current_object.complex = false;
			current_object.interactable = false;
			current_object.lookable = false;
			current_object.name = "";
			current_object.path = "";
			current_object.script = "";
			current_object.usable = false;
			original_key = "";
		}

	} //Lvleditor
} //pc
