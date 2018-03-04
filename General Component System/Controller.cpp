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
#include "Controller.hpp"
#include "Entity.hpp"
#include <string>
#include <cassert>

namespace pc {
	namespace cs {
		const std::vector<size_t> WasCollected::requirements() {
			std::vector<size_t> required;
			required.resize(1);
			required[0] = PropertyName::Collected;
			return required;
		}



		bool WasCollected::control(std::shared_ptr<Entity> e, mb::Bus& bus) {
			std::hash<std::string> hash;
			
			if (auto prop = e->hasProperty(PropertyName::Collected)) {
				auto property = static_cast<const Property<bool>*>(prop);
				assert(property != nullptr); // If we fail then...
				if (property->value) { // When it was collected ...send the message
					mb::Message message;
					message.type = mb::MessageType::ComponentSystem;
					message.data.resize(2);
					size_t t = hash("Item collected");
					message.data[0] = static_cast<const void *>(&t);
					message.data[1] = static_cast<const void*>(&e->id);
					bus.send(message);
					return true;
				}
				return true;
			}
			else {
				e->component_changed();
				assert(true && "A controller wanted to access a property, which was not found");
				return false;
			}
				
		}
	}
}

