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

#ifndef PC_SCENE
#define PC_SCENE

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Object.hpp"
#include <SFML\Graphics.hpp>
#include <list>
#include <Bus.hpp>

namespace pc {
	class Scene {
	public:
		typedef std::pair<unsigned int, std::shared_ptr<Object>> ListObject;
		Scene(const mb::Bus& bus);

		bool sort(const ListObject& l, const ListObject& r);
	private:
		std::function<void(mb::Message)> reciever = [this](mb::Message) {

		};

		std::list<ListObject> objects;
		std::list<ListObject> clickable_objects;
		sf::Vector2i size;
		const mb::Bus& message_bus;
	};
}

#endif