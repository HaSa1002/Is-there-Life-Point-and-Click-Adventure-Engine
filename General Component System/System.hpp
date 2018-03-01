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

#ifndef PC_CS_SYSTEM
#define PC_CS_SYSTEM

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "BaseController.hpp"
#include "Entity.hpp"
#include "Property.hpp"
#include <Bus.hpp>
#include <memory>


namespace pc {
	namespace cs {
		class System {
		public:
			////////////////////////////////////////////////////////////
			/// Accepts the message Bus
			///
			////////////////////////////////////////////////////////////
			System(mb::Bus& message_bus) : bus{ message_bus } {};


			////////////////////////////////////////////////////////////
			/// Connects Controller and Entities
			/// just touches the entities in changed_entities
			///
			////////////////////////////////////////////////////////////
			void factory(std::shared_ptr<Entity> e, std::vector<std::shared_ptr<BaseController>>& controller);


			////////////////////////////////////////////////////////////
			/// Here you register manually all Controller to the list
			/// 
			////////////////////////////////////////////////////////////
			void controller_register();


			////////////////////////////////////////////////////////////
			/// It calls the control function of the controller
			///
			////////////////////////////////////////////////////////////
			void run_controller();


			////////////////////////////////////////////////////////////
			/// It runs the the system
			///
			////////////////////////////////////////////////////////////
			void run();

		private:
			mb::Bus& bus;
			std::map<std::shared_ptr<Entity>, std::vector<std::shared_ptr<BaseController>>> entities;
			std::vector<std::shared_ptr<Entity>> changed_entities;
			std::vector<std::shared_ptr<BaseController>> controller;
		};
	}
}

#endif // !PC_CS_SYSTEM
