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

#ifndef PC_SCENE
#define PC_SCENE

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Exception.hpp"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector3.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "sol.hpp"

#include <list>

namespace pc {
	struct Scene {

		struct Object {
			sf::Sprite sprite;
			int layer;
			std::string callback;
			std::list<char> actions;

			Object(const sf::Sprite& s, const sf::Vector3i& pos, const std::string& call, const std::list<char>& actions);
			bool has_action(const char& action);
		};


		////////////////////////////////////////////////////////////
		/// adds an Object to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		/// can throw: Exception::cantLoadImage
		///
		////////////////////////////////////////////////////////////
		void addObject(const std::string& texture_path, const sf::Vector3i& position);

		////////////////////////////////////////////////////////////
		/// adds an Object to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		/// can throw: Exception::cantLoadImage
		///
		////////////////////////////////////////////////////////////
		void addObject(const std::string& texture_path, const sf::Vector3i& position, const std::string& callback, const std::list<char>& action);

		std::string name;
		std::list<sf::Texture> textures;
		std::list<Object> objects;
	};
}

#endif //!PC_SCENE
