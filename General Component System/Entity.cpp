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
#include "Entity.hpp"

namespace pc {
	////////////////////////////////////////////////////////////
	/// Componentsystem
	////////////////////////////////////////////////////////////
	namespace cs {
		
		Entity::Entity(BaseProperty* property, mb::Bus& message_bus, const size_t id) : message_bus{ message_bus }, id{ id } {
			addProperty(property);
		}


		////////////////////////////////////////////////////////////
		/// Constructs the Entity with a bunch of properties
		///
		////////////////////////////////////////////////////////////
		Entity::Entity(const std::vector<BaseProperty*>& property_list, mb::Bus& message_bus, const size_t id) : message_bus{ message_bus }, id{ id } {
			properties = property_list;
			component_changed();
		}


		////////////////////////////////////////////////////////////
		/// Checks if a property with the given id (name)
		/// Use a hash of std::string
		///
		////////////////////////////////////////////////////////////
		const BaseProperty* Entity::hasProperty(size_t name) {
			for (const auto& i : properties) {
				if (i->id == name)
					return i;
			}
			return nullptr;
		}



		void Entity::addProperty(BaseProperty * property) {
			properties.push_back(property);
			component_changed();
		}

		void Entity::component_changed() {
			mb::Message mess;
			mess.type = mb::MessageType::ComponentSystem;
			std::hash<std::string> h_s;
			size_t cs_type = h_s("Component changed");
			mess.data.push_back(static_cast<const void*>(&cs_type));
			mess.data.push_back(static_cast<const void*>(&id));
		}
	}
}
