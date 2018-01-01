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

#ifndef PC_LVLEDITOR_OBJECTMANAGER
#define PC_LVLEDITOR_OBJECTMANAGER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Menue.hpp"
#include "imgui-helper.h"

#include <imgui.h>
#include <imgui-SFML.h>

#include <vector>

namespace pc {
	namespace Lvleditor {
		////////////////////////////////////////////////////////////
		/// Class that manages the objectmanager
		///
		////////////////////////////////////////////////////////////
		class Objectmanager : public Menue {
		public:
			////////////////////////////////////////////////////////////
			/// Default Constructor
			///
			////////////////////////////////////////////////////////////
			Objectmanager();

			////////////////////////////////////////////////////////////
			/// Default Deconstructor
			///
			////////////////////////////////////////////////////////////
			~Objectmanager();

			////////////////////////////////////////////////////////////
			/// draws the objectmanager
			///
			////////////////////////////////////////////////////////////
			void draw();

			////////////////////////////////////////////////////////////
			/// reports opening action
			///
			////////////////////////////////////////////////////////////
			auto reportOpeningAction()->std::string;

			////////////////////////////////////////////////////////////
			/// reports opening action
			///
			////////////////////////////////////////////////////////////
			auto reportClosingAction()->std::string;
		private:

			////////////////////////////////////////////////////////////
			/// loads objects
			///
			////////////////////////////////////////////////////////////
			void loadObjects();

			////////////////////////////////////////////////////////////
			/// saves objects
			///
			////////////////////////////////////////////////////////////
			void saveObjects();

			////////////////////////////////////////////////////////////
			// Members
			////////////////////////////////////////////////////////////
			std::string					input_buffer;						/// buffer
			bool						is_open = 1;						/// states the window_open_state
			std::string					opening_action = "";				/// opening action
			ImGuiTextFilter				object_filter;						/// filter
			std::vector<std::string>	object_list{ "bg.te", "bg.lp" };	/// filterliste
			std::vector<int>			open_menues;						/// open_menues
			bool						t1;									/// t1_buffer
			bool						t2;									/// t2_buffer
			bool						t3;									/// t3_buffer
			bool						testing;							/// testing buffer
		};
	}
}

#endif // !PC_LVLEDITOR_OBJECTMANAGER
////////////////////////////////////////////////////////////
/// Class that manages the objectmanager
///
////////////////////////////////////////////////////////////