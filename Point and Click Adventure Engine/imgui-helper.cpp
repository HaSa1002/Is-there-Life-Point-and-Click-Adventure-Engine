#pragma once
#include "imgui-helper.h"

#include <imgui.h>

#include <string>

namespace ImGui
{

	// well, at least it is possible..
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *reinterpret_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter, reinterpret_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter, reinterpret_cast<void*>(&values), values.size());
	}

	bool InputText(const char* label, std::string& str, size_t maxInputSize,
		ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
	{
		if (str.size() > maxInputSize) { // too large for editing
			ImGui::Text(str.c_str());
			return false;
		}

		std::string buffer(str);
		buffer.resize(maxInputSize);
		bool changed = ImGui::InputText(label, &buffer[0], maxInputSize, flags, callback, user_data);
		// using string as char array
		if (changed) {
			auto i = buffer.find_first_of('\0');
			str = buffer.substr(0u, i);
		}
		return changed;
	}

	bool InputTextMultiline(const char* label, std::string& str, size_t maxInputSize, const ImVec2& size,
		ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
	{
		if (str.size() > maxInputSize) { // too large for editing
			ImGui::Text(str.c_str());
			return false;
		}

		std::string buffer(str);
		buffer.resize(maxInputSize);
		bool changed = ImGui::InputTextMultiline(label, &buffer[0], maxInputSize, size, flags, callback, user_data);
		// using string as char array
		if (changed) {
			auto i = buffer.find_first_of('\0');
			str = buffer.substr(0u, i);
		}
		return changed;
	}

} // end of namespace ImGui