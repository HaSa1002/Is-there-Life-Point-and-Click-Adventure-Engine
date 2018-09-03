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

#ifndef PC_ANIMATED_OBJECT
#define PC_ANIMATED_OBJECT

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Animation.hpp"
#include "SpriteObject.hpp"
#include <SFML\Graphics.hpp>
#include <memory>
#include <functional>
#include <chrono>

namespace pc {
	struct StaticAnimatedSpriteObject : public SpriteObject, Animation {
		sf::Time toWait;
		std::chrono::steady_clock::time_point callback;
		std::function<void(const std::chrono::steady_clock::time_point&)> callFunction;

		StaticAnimatedSpriteObject(const sf::Texture & texture, const sf::Vector3i & position, const std::string & name, const std::list<char>& actions, std::function<void(const std::chrono::steady_clock::time_point&)> call_func);

		void update(sf::Time elapsed);
		void play(hash state, sf::Time duration, std::chrono::steady_clock::time_point callback);
	};
}

#endif //!PC_ANIMATED_OBJECT
