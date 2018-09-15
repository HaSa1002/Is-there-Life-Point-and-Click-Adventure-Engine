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
#include "Texture.hpp"
#include "SFMLHelper.hpp"
#include "MaxRectsBinPack.h"
#include <SFML\Graphics\Texture.hpp>
#include <vector>
#include <set>
#include <map>



namespace itl {
	class TextureManager {
	private:
		typedef size_t hashedName;

	public:
		TextureManager() { };
		TextureManager(std::vector<std::pair<const std::string&, const size_t>>& textures);
		auto get(size_t name) -> const Texture*;
		void add(const std::string& path, const size_t name);
		void clear(bool onlyBuffer = false);
		
		////////////////////////////////////////////////////////////
		/// Builds the texture atlas using a MaxRect Algorithm
		///
		/// call clear() before adding textures, to not include
		/// existing textures
		////////////////////////////////////////////////////////////
		void build();



	private:
		void addTexture(const sf::Vector2u& vec = sf::Vector2u(0, 0));

		////////////////////////////////////////////////////////////
		// Member Data
		////////////////////////////////////////////////////////////
		std::vector<std::pair<const std::string&, const hashedName>> buffer;
		std::map<hashedName, Texture> loaded_textures;
		std::vector<sf::Texture> textures;

		
	};
}


