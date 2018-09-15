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
#include <SFML\Graphics\Texture.hpp>
#include <string>


namespace itl {

	////////////////////////////////////////////////////////////
	/// The Texture struct contains the texture rect of the 
	/// texture, which has the name "name".
	///
	////////////////////////////////////////////////////////////
	struct Texture {

		////////////////////////////////////////////////////////////
		/// param texture_rect: Rect of the texture
		/// param texture_name: hash of the name
		///
		////////////////////////////////////////////////////////////
		Texture(const sf::IntRect& textureRect, const size_t& textureName, const sf::Texture& on_texture) noexcept: rect { textureRect }, name { textureName }, texture_ref { on_texture } { }

		////////////////////////////////////////////////////////////
		// Member Data
		////////////////////////////////////////////////////////////
		const sf::IntRect	rect;			/// Texture rect
		const size_t		name;			/// Texture name
		const sf::Texture&	texture_ref;	/// Refrence to the texture

	};
}