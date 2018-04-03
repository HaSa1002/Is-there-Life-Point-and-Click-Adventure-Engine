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


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "System.hpp"

namespace pc {
	namespace cs {

		template<class T>
		void System::connect_controller(std::shared_ptr<Entity> e) {
			//we need to know were to push our controller
			auto entity = entities.find(e);

			//just push when we have the correct properties
			int propertiy_maches = 0;
			std::vector<size_t> requirements = T::requirements();
			for (const auto& i : requirements) {
				if (e->hasProperty(i))
					++propertiy_maches; //else return?
				if (propertiy_maches == requirements.size()) {
					entity->second.push_back(std::make_unique<WasCollected>());
					return;
				}
			}
		}


		void System::factory(std::shared_ptr<Entity> e) {
			//We have to delete all connected controllers, because we don't know (and want to know) which properties have changed
			entities.find(e)->second.clear();
			//Calls the Controller Connector
			//add here your controllers
			connect_controller<WasCollected>(e);
			//connect_controller<WasLooked>(e);
			//connect_controller<WasInteracted>(e);
			//connect_controller<executeScript>(e);
			//connect_controller<Move>(e);
			//connect_controller<Animate>(e);
			//connect_controller<SaveGame>(e);
			//connect_controller<LoadGame>(e);
			//connect_controller<LoadScene>(e);
			
		}


		void System::run_controller() {
			for (auto& i : entities) {
				for (const auto& j : i.second) {
					j->control(i.first, bus);
				}
			}
		}


		void System::run() {
			for (auto& i : changed_entities) {
				factory(i);
			}
			changed_entities.clear();
			run_controller();
		}
	}
}