#pragma once
#include <string>


namespace pc {
	namespace Lvleditor {
		class Menue {
		public:
			virtual void draw()=0;
			virtual auto reportOpeningAction()->std::string=0;
		};

		
	} //Lvleditor
} //pc