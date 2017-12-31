////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
// Copyright (c) 2017 Johannes Witt (johawitt@outlook.de)
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

#ifndef PC_LVLEDITOR_LOCALISATION
#define PC_LVLEDITOR_LOCALISATION

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Menue.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <vector>
#include <list>
#include <map>

namespace pc {
	namespace Lvleditor {
		////////////////////////////////////////////////////////////
		/// Class that manages the Mainmenu in the Leveleditor
		///
		////////////////////////////////////////////////////////////
		class Localisation :public Menue {
		public:
			///////////////////////////////////////////////////////////
			/// Struct of the Localise-items
			///
			////////////////////////////////////////////////////////////
			struct Item {
				std::string text;
				std::string audio_path;
			};


			////////////////////////////////////////////////////////////
			/// Default Constructor
			///
			////////////////////////////////////////////////////////////
			Localisation();

			////////////////////////////////////////////////////////////
			/// Default Deconstructor
			///
			////////////////////////////////////////////////////////////
			~Localisation();

			////////////////////////////////////////////////////////////
			/// draws the menue
			///
			////////////////////////////////////////////////////////////
			void draw();

			////////////////////////////////////////////////////////////
			/// reports opening Actions
			///
			////////////////////////////////////////////////////////////
			auto reportOpeningAction()->std::string;

			////////////////////////////////////////////////////////////
			/// reports closing action
			///
			////////////////////////////////////////////////////////////
			auto reportClosingAction()->std::string;
		private:

			///////////////////////////////////////////////////////////
			/// loads the languagekeys from file
			///
			////////////////////////////////////////////////////////////
			void loadLanguages();

			///////////////////////////////////////////////////////////
			/// 
			///
			////////////////////////////////////////////////////////////
			void saveLanguages();

			void showModalLanguages();

			void loadLocaliseKeys();

			void saveLocaliseKeys();

			void selectKey(const std::string& key);

			void removeKey(const std::string& key);

			void showModalError();

			////////////////////////////////////////////////////////////
			// Members
			////////////////////////////////////////////////////////////
			bool		is_open = 1;			///
			std::string	opening_action = "";	/// states the Action
			ImGuiTextFilter				object_filter;						/// filter
			std::vector<std::string>	languages{ "EN", "DE" };
			int							language_index = 0;
			std::string					current_key = "";
			bool						modal_is_open = 1;
			std::string					language_code = "";
			int							modal_language_index = 0;
			std::string					text = "";
			std::map<std::string, Item> localise_keys;
			std::string					audio_path = "";
			std::string					original_key;
			bool						show_error = 0;
			bool						supress_modal_showing = 0;
			bool						supress_modal_delete_showing = 0;
			bool						show_remove = 0;
		};
	} //Lvleditor
} //pc


#endif // !PC_LVLEDITOR_LOCALISATION

  ////////////////////////////////////////////////////////////
  /// class Localisation
  ///
  /// 
  ///
  ////////////////////////////////////////////////////////////