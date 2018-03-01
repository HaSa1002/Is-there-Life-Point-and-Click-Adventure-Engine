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

#ifndef PC_CS_CONTROLLER
#define PC_CS_CONTROLLER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "BaseController.hpp"

namespace pc {
	////////////////////////////////////////////////////////////
	/// Componentsystem - Custom Components
	////////////////////////////////////////////////////////////
	namespace cs {

		////////////////////////////////////////////////////////////
		// Objekte in der Welt
		////////////////////////////////////////////////////////////
		struct WasCollected : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		struct WasLooked : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		struct WasInteracted : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		struct executeScript : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		////////////////////////////////////////////////////////////
		// Moveable Objects: Player, Menschen, ...
		////////////////////////////////////////////////////////////
		struct move : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		////////////////////////////////////////////////////////////
		// Objekte mit mehreren Bilder und einem angegebenen Zeitintervall
		////////////////////////////////////////////////////////////
		struct animate : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		////////////////////////////////////////////////////////////
		// Savegameoperationen
		////////////////////////////////////////////////////////////
		struct save_game : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		struct load_game : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};

		////////////////////////////////////////////////////////////
		// Scenenoperationen
		////////////////////////////////////////////////////////////
		struct load_scene : BaseController {
			static std::vector<size_t> requirements();
			bool control(std::shared_ptr<BaseProperty> entity_properties);

		};
		//...
	}
}


#endif // !PC_CS_CONTROLLER
