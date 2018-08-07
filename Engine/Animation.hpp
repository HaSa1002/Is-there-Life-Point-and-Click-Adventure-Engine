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

#ifndef PC_ANIMATION
#define PC_ANIMATION

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "typedefs.hpp"
#include <SFML\Graphics.hpp>
#include <list>
#include <utility>

namespace pc {
	
	struct Animation {
		std::list<std::pair<hash, sf::IntRect>> states;
		std::string trigger_function; //TODO: Delete
		hash state = 0;
		const sf::Vector2i convertToVector2i(const sf::Vector2f & vec);
		const sf::IntRect getStateRect(std::string state);
		const sf::IntRect getStateRect(hash state);
		virtual void update(sf::Time elapsed) = 0;
	};
}

#endif //!PC_ANIMATION
