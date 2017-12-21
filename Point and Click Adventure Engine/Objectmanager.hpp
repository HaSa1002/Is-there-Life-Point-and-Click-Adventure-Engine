#pragma once
#include "Menue.hpp"
#include "imgui-helper.h"
#include <imgui-SFML.h>
#include <vector>
namespace pc {
	namespace Lvleditor {
		class Objectmanager : public Menue
		{
		public:
			Objectmanager();
			~Objectmanager();

			void draw();
			auto reportOpeningAction()->std::string;
		private:
			void loadObjects();
			void saveObjects();

			std::string opening_action = "";
			std::vector<int> openMenues;
			bool testing;
			bool t1;
			bool t2;
			bool t3;
			ImGuiTextFilter objectFilter;
			std::string inputBuffer;
			std::vector<std::string> objectList{ "bg.te", "bg.lp" };
		};
	}
}
