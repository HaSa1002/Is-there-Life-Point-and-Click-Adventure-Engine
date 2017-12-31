#pragma once

#include <imgui.h>

#include <vector>
namespace ImGui {
	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values);
	bool InputText(const char* label, std::string& str, size_t maxInputSize,
		ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = 0, void* user_data = 0);
	bool InputTextMultiline(const char* label, std::string& str, size_t maxInputSize, const ImVec2& size = ImVec2(0,0),
		ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = 0, void* user_data = 0);

}