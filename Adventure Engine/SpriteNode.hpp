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

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Lua.hpp"
#include "Event.hpp"
#include "SceneNode.hpp"
#include "TextureManager.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace itl {
	class SpriteNode : public SceneNode {
	public:
		SpriteNode();
		SpriteNode(sf::Texture & texture);
		SpriteNode(const sf::Texture & texture, const sf::IntRect & textureRect);
		void setTexture(size_t name, TextureManager& tm);
		void updateFunction(sol::function& function);
		void addMember(size_t name, sol::object o);
		sol::object getMember(size_t name);

	private:
		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		

		void updateCurrent(sf::Time dt, Event* e);


	private:
	typedef size_t hashedName;
		std::map<hashedName, sol::object>	lua_members;
		sf::Sprite										mSprite;
		sol::function		update;
	};
}