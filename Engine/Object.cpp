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

#include "Object.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

namespace pc {
	Object::Object(const sf::Texture& s, const sf::Vector3i & pos, const std::string & call, const std::list<char>& a) : sprite{ std::make_shared<sf::Sprite>(s) }, layer{ pos.z }, name{ call }, actions{ a } {
		sprite->setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
		type = 's';
	}


	////////////////////////////////////////////////////////////
	Object::Object(const sf::RectangleShape & c, const sf::Vector3i & pos, const std::string & call, const std::list<char>& actions) : click{ std::make_shared<sf::RectangleShape>(c) }, layer{ pos.z }, name{ call }, actions{ actions } {
		click->setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
		type = 'c';
	}


	////////////////////////////////////////////////////////////
	Object::Object(const Object & object) {
		switch (object.type) {
		case 's':
			sprite = object.sprite;
			break;
		case 'c':
			click = object.click;
			break;
		}
		type = object.type;
		layer = object.layer;
		name = object.name;
		actions = object.actions;
	}


	////////////////////////////////////////////////////////////
	Object::~Object() {
	}


	////////////////////////////////////////////////////////////
	bool Object::hasAction(const char& action) {
		for (const auto& a : actions) {
			if (a == action)
				return true;
		}
		return false;
	}
	void Object::setPosition(const sf::Vector2i & pos) {
		switch (type) {
		case 's':
			sprite->setPosition(sf::Vector2f(pos));
			break;
		case 'c':
			click->setPosition(sf::Vector2f(pos));
			break;
		case 't':
			text->setPosition(sf::Vector2f(pos));
			break;
		}
	}


	////////////////////////////////////////////////////////////
	sf::Transformable& Object::get() {
		if (type == 's' ||type == 'm')
			return static_cast<sf::Transformable&>(*sprite);
		if (type == 'c')
			return static_cast<sf::Transformable&>(*click);
		if (type == 't')
			return static_cast<sf::Transformable&>(*text);
		std::string message = "The type of the Object is wrong. : " + type;
		throw(std::invalid_argument(message));
	}
}