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

		////////////////////////////////////////////////////////////
		/// Standard constructor
		///
		////////////////////////////////////////////////////////////
		TextureManager() { };

		////////////////////////////////////////////////////////////
		/// Instantly loads the textures and builds the texture atlas
		///
		/// param textures - std::vector of pairs of the path and hashed name
		////////////////////////////////////////////////////////////
		TextureManager(std::vector<std::pair<const std::string&, const hashedName>>& textures);

		////////////////////////////////////////////////////////////
		/// Gets the texture with the given name
		///
		/// param name - hashed name of the texture
		/// returns Texture* or nullptr if nothing was found
		////////////////////////////////////////////////////////////
		auto find(size_t name) -> const Texture*;

		////////////////////////////////////////////////////////////
		/// Adds a texture to the buffer
		///
		/// param path - Path to the texture
		/// param name - hashed name of the texture
		///
		////////////////////////////////////////////////////////////
		void add(const std::string& path, const size_t name);

		////////////////////////////////////////////////////////////
		/// Clears the buffer and given on the param also the texture atlas
		///
		/// param onlyBuffer - if true only the buffer is cleared
		////////////////////////////////////////////////////////////
		void clear(bool onlyBuffer = false);
		
		////////////////////////////////////////////////////////////
		/// Builds the texture atlas using a MaxRect Algorithm
		///
		/// call clear() before adding textures, to not include
		/// existing textures
		/// If a texture can't be loaded, the engine will replace it with 
		/// a 50x50px sized purple texture
		////////////////////////////////////////////////////////////
		void build();



	private:

		////////////////////////////////////////////////////////////
		// Member Data
		////////////////////////////////////////////////////////////
		std::vector<std::pair<const std::string&, const hashedName>>	buffer;				/// Saves the path and name of the textues to be loaded
		std::map<hashedName, Texture>									loaded_textures;	/// Holds the loaded Textures
		std::vector<sf::Texture>										textures;			/// Holds the texture atlas'

		
	};

	static TextureManager	texture_manager;
}


