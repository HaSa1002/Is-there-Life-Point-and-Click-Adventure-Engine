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

#include "MoveableObject.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

namespace pc {
	MoveableObject::MoveableObject(const sf::Texture& texture, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions, const std::string& trigger) :Object{ texture, position, name, actions } {
		trigger_function = trigger;
		type = 'm';
		if (!areas.empty())
			areas.clear();
		if (!points.empty())
			points.clear();
		if (!states.empty())
			states.clear();

	}
	sf::Vector2f MoveableObject::getPoint(hash point) {
		for (const auto& i : points) {
			if (i.first == point)
				return i.second;
		}
		return sf::Vector2f();
	}
	void MoveableObject::setPosition(hash point) {
		sprite->setPosition(static_cast<sf::Vector2f>(getPoint(point)));
		this->point = point;
	}
	void MoveableObject::move(hash point, sf::Time duration) {
		this->point = point;
		toMove = duration;
	}
	const sf::IntRect MoveableObject::getStateRect(const sf::Vector2i& position) {
		for (const auto& i : areas) {
			if (i.first.contains(position))
				return Animation::getStateRect(i.second);
		}
		return sf::IntRect();
	}
	void MoveableObject::update(sf::Time elapsed) {
		//Skip if no movement has to be done
		if (toMove.asSeconds() == 0)
			goto set_texture;

		//Calculate the current position to set
		{
		sf::Vector2f dest = getPoint(point);
		if (toMove < elapsed) {
			sprite->setPosition(dest);
			toMove = sf::Time::Zero;
			goto set_texture;
		}
		dest -= sprite->getPosition();
		sprite->move((dest / toMove.asSeconds())* elapsed.asSeconds());
		toMove -= elapsed;
		}
	set_texture: //We are setting the correct texture now
		sprite->setTextureRect(getStateRect(convertToVector2i(sprite->getPosition())));
	}

	sf::Transformable & MoveableObject::get() {
		return static_cast<sf::Transformable&>(*sprite);
	}
}