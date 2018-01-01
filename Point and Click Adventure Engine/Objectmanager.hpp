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
#include <map>
#include <string>
#include <memory>

namespace pc {
	namespace Lvleditor {
		////////////////////////////////////////////////////////////
		/// Class that manages the objectmanager
		///
		////////////////////////////////////////////////////////////
		class Objectmanager : public Menue {
		public:

			struct Object {
				bool		collectable;	/// 
				bool		complex;		/// 
				bool		interactable;	/// 
				bool		lookable;		/// 
				std::string name;			/// 
				std::string path;			/// 
				std::string	script;			/// 
				bool		usable;			/// 
			};

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

			auto getPtr()->const std::shared_ptr<Objectmanager>;
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

			void update(const std::string & key);

			////////////////////////////////////////////////////////////
			// Members
			////////////////////////////////////////////////////////////
			bool							is_open = true;						/// states the window_open_state
			std::string						opening_action = "";				/// opening action
			ImGuiTextFilter					object_filter;						/// filter
			std::map<std::string, Object>	object_list;				/// filterliste
			Object							current_object;
			std::string						current_object_key;
			std::shared_ptr<Objectmanager>	ptr;								/// this shared pointer
			std::string						original_key = "";
			bool							show_error = false;
			bool							supress_error_showing = false;
		};
	}
}

#endif // !PC_LVLEDITOR_OBJECTMANAGER
////////////////////////////////////////////////////////////
/// Class that manages the objectmanager
///
////////////////////////////////////////////////////////////