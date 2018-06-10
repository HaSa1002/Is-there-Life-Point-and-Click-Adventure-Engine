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
#include "MoveableObject.hpp"
#include "sol.hpp"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector3.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>


#include <list>

namespace pc {
	struct Scene {

		struct Walkbox {
			sf::IntRect rectangle;
			bool is_active;

			Walkbox(const sf::IntRect& rect, const bool active) :rectangle{ rect }, is_active{ active } {};
		};

		struct Zoomline {
			sf::IntRect position;
			float factor;
			bool is_active;

			Zoomline(const sf::IntRect& rect, const float factor, const bool active) :position{ rect }, factor{ factor }, is_active { active } {};
		};


		////////////////////////////////////////////////////////////
		/// adds an Object to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		/// can throw (DEBUG): Exception::cantLoadImage
		///
		////////////////////////////////////////////////////////////
		void addObject(const std::string& texture_path, const sf::Vector3i& position);

		////////////////////////////////////////////////////////////
		/// adds an Object to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		/// can throw (DEBUG): Exception::cantLoadImage
		///
		////////////////////////////////////////////////////////////
		void addObject(const std::string& texture_path, const sf::Vector3i& position, const std::string& name, const std::list<char>& action);

		////////////////////////////////////////////////////////////
		/// adds an MoveableObject to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		/// can throw (DEBUG): Exception::cantLoadImage
		///
		////////////////////////////////////////////////////////////
		void addMoveableObject(sol::state& lua, const std::string& texture_path, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions);

		////////////////////////////////////////////////////////////
		/// adds a Walkbox to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		////////////////////////////////////////////////////////////
		void addWalkbox(const sf::IntRect& rectangle, const bool is_active);

		////////////////////////////////////////////////////////////
		/// adds a Zoomline to the Scene
		///
		/// param texture_path which texture is used
		/// param position where to position the object
		///
		////////////////////////////////////////////////////////////
		void addZoomline(const sf::IntRect& position, const float factor, const bool is_active);

		static bool sort_objects_by_layer(const std::shared_ptr<Object>& l, const std::shared_ptr<Object>& r);

		void createEditorHelper();

		void reset();

		std::shared_ptr<Object> getObject(const std::string& object_name);

		std::string makeLuaString();

		std::string name;
		std::list<sf::Texture> textures;
		std::list<std::shared_ptr<Object>> objects;
		std::list<Walkbox> walkboxes;
		std::list<Zoomline> zoomlines;
		std::list<sf::RectangleShape> helper;
		sf::Vector3i helper_count;
	};
}

#endif //!PC_SCENE
