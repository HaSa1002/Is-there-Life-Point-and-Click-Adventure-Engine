////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de) based on "SFML GAME DEVELOPMENT"
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

#include "SpriteNode.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderTarget.hpp>

namespace itl {

	SpriteNode::SpriteNode() : mSprite() { }
	SpriteNode::SpriteNode(const std::string& name, sf::Texture& texture) : mSprite(texture), object_name { name } { }

	SpriteNode::SpriteNode(const std::string& name, const sf::Texture& texture, const sf::IntRect& textureRect) : mSprite(texture, textureRect), object_name { name } { }

	void SpriteNode::setTexture(const sf::Texture & texture) {
		mSprite = sf::Sprite(texture);
	}

	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
		//TODO: Exectue culling
		target.draw(mSprite, states);
	}


	////////////////////////////////////////////////////////////
	void SpriteNode::updateCurrent(sf::Time dt) {
		if (lua.lua["objects"][object_name].get_type() == sol::type::table) {
			if (last_event == nullptr) lua.lua["objects"][object_name]["update"].call(dt.asSeconds());
			else lua.lua["objects"][object_name]["update"].call(dt.asSeconds(), last_event->action, last_event->x, last_event->y);
		} else std::cout << "Object " + object_name + " or update() method wasn't found. Skipping update.\n";
	}
}