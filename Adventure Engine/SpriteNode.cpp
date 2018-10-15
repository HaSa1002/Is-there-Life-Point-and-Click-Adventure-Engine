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
	SpriteNode::SpriteNode(sf::Texture& texture) : mSprite(texture) { }

	SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) : mSprite(texture, textureRect) { }

	void SpriteNode::setTexture(size_t name, TextureManager & tm) {
		const Texture* t = tm.find(name);
		if (t == nullptr) {
			std::cout << "Texture wasn't found! \n";
		} else {
			mSprite.setTexture(t->texture_ref, true);
			mSprite.setTextureRect(t->rect);
		}
	}

	void SpriteNode::updateFunction(sol::function & function) {
		update = function;
	}

	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
		//TODO: Exectue culling
		sf::FloatRect view(0,0, target.getSize().x, target.getSize().y);
		sf::FloatRect r = getWorldTransform().transformRect(mSprite.getGlobalBounds());
		if (r.intersects(view))	target.draw(mSprite, states);
	}

	void SpriteNode::addMember(size_t name, sol::object o) {
		lua_members.insert_or_assign(name, o);
	}

	sol::object SpriteNode::getMember(size_t name) {
		auto r = lua_members.find(name);
		if (r == lua_members.end()) {
			std::cout << "Member (" << name << ") wasn't found.";
			return sol::nil;
		} else {
			return r->second;
		}
	}


	////////////////////////////////////////////////////////////
	void SpriteNode::updateCurrent(sf::Time dt, Event* e) {
		if (update.valid() && update.lua_state() != nullptr) {
			if (e != nullptr) {
				sf::Vector2f p = getWorldPosition();
				
				if (getWorldTransform().transformRect(mSprite.getGlobalBounds()).contains(e->x, e->y))
					update.call(dt.asSeconds(), e->action, e->end, e->x, e->y);
				else update.call(dt.asSeconds());
			} else update.call(dt.asSeconds());
		}
	}
}