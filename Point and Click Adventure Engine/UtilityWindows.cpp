#include "UtilityWindows.hpp"

namespace pc {
	namespace Lvleditor {
		void UtilityWindows::errorModal(const std::string & errorMessage, bool& show_error) {
			ImGui::OpenPopup("Error##static_call");
			ImGui::BeginPopupModal("Error##static_call");
			ImGui::TextColored(ImVec4(255, 0, 0, 255), errorMessage.data());
			if (ImGui::Button("OK##modal_empty", ImVec2(100, 20))) {
				show_error = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}