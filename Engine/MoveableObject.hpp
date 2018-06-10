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

#ifndef PC_MOVEABLE_OBJECT
#define PC_MOVEABLE_OBJECT

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Animation.hpp"
#include "Object.hpp"
#include "sol.hpp"
#include <SFML\Graphics.hpp>
#include <memory>

namespace pc {
	struct MoveableObject : public Animation, Object {
		MoveableObject(sol::state& lua, const sf::Texture& texture, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions, const std::string& trigger);
		std::list<std::pair<sf::IntRect, hash>> areas; 
		std::list<std::pair<hash, sf::Vector2f>> points;
		hash point = 0;
		sf::Time toMove;
		sf::Vector2f getPoint(hash point);
		void setPosition(hash point);
		void move(hash point, sf::Time duration);
		const sf::IntRect getStateRect(const sf::Vector2i& position);
		void update(sf::Time elapsed);
		sf::Transformable& get();


	private:
		sol::state& l;

	};
}

#endif //!PC_MOVEABLE_OBJECT
