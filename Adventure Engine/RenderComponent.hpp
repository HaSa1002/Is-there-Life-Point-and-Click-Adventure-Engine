////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Engine
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

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "TextureManager.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace itl {
	class RenderComponent : sf::Drawable {
	public:
		////////////////////////////////////////////////////////////
		/// Creates the RenderComponent
		///
		/// param tm - TextureManager to be used
		/// param texture - hashed string of the texture_name
		///
		/// Offensive Class: Panics Lua, if texture doesn't exist
		///
		////////////////////////////////////////////////////////////
		RenderComponent(TextureManager& tm, size_t texture);


		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Transformable* getTransformable();

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

		std::pair<float, float> getSize();

	protected:
		TextureManager& tm;

	private:
		sf::Sprite drawable;
	};
}