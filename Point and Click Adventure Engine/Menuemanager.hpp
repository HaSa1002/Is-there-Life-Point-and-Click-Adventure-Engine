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

#ifndef PC_LVLEDITOR_MENUEMANAGER
#define PC_LVLEDITOR_MENUEMANAGER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Menue.hpp"
#include "Rendering.hpp"
#include "Mainmenue.hpp"
#include "Objectmanager.hpp"
#include "Scenemanager.hpp"
#include "Localisation.hpp"

#include <SFML\System\Clock.hpp>

#include <list>
#include <memory>
#include <string>


namespace pc {
	namespace Lvleditor {
		////////////////////////////////////////////////////////////
		/// Class that manages all ImGui Windows in the Editor
		///
		////////////////////////////////////////////////////////////
		class Menuemanager {
		public:

			////////////////////////////////////////////////////////////
			/// Default constructor
			///
			////////////////////////////////////////////////////////////
			Menuemanager();

			////////////////////////////////////////////////////////////
			/// Default deconstructor
			///
			////////////////////////////////////////////////////////////
			~Menuemanager();

			////////////////////////////////////////////////////////////
			/// opens the given window
			///
			/// param menue_id window id
			///
			////////////////////////////////////////////////////////////
			void open(std::string menue_id);

			////////////////////////////////////////////////////////////
			/// closes the given window
			///
			/// param menue_id window id
			///
			////////////////////////////////////////////////////////////
			bool close(std::string menue_id);

			////////////////////////////////////////////////////////////
			/// draws all windows
			///
			/// param renderer target
			///
			////////////////////////////////////////////////////////////
			void draw(pc::Rendering& renderer);

		private:

			////////////////////////////////////////////////////////////
			// Members
			////////////////////////////////////////////////////////////
			std::list<std::shared_ptr<Menue>>	active_menues;		/// 
			std::list<std::string>				active_menues_id;	///
			sf::Clock							clock;				///
			Mainmenue							mainmenue;			///
			Objectmanager						objectmanager;		///
			Scenemanager						scenemanager;		///
			Localisation						localisation;		///

		}; //class
	} //Lvleditor
} //pc

#endif