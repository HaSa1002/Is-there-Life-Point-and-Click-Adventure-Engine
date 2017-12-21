#pragma once
#ifndef PC_LVLEDITOR_MAINMENU
#define PC_LVLEDITOR_MAINMENU

#include "Menue.hpp"

namespace pc {
	namespace Lvleditor {
		class Mainmenue :public Menue {
		public:
			Mainmenue();
			~Mainmenue();
			void draw();
			auto reportOpeningAction()->std::string;
		private:
			std::string opening_action = "";
		};
	} //Lvleditor
} //pc


#endif // !PC_LVLEDITOR_MAINMENU
