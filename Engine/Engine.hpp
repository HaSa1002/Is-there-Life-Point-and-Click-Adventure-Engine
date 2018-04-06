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

#ifndef PC_ENGINE
#define PC_ENGINE

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Rendering.hpp"
#include "lua.hpp"
#include "Subtitle.hpp"

namespace pc {
	class Engine {
	public:

		////////////////////////////////////////////////////////////
		/// It's the default constructor and starts the internals of
		/// the engine
		///
		/// param editor	define wether we start the editor or the game
		///
		////////////////////////////////////////////////////////////
		Engine(bool editor) :editor_mode{ editor }, subtitle{ lua } { start(); };

		////////////////////////////////////////////////////////////
		/// We don't have a default constructor
		///
		////////////////////////////////////////////////////////////
		Engine() = delete;

	private:

		////////////////////////////////////////////////////////////
		/// Loads a scene
		///
		////////////////////////////////////////////////////////////
		void loadScene();

		////////////////////////////////////////////////////////////
		/// Performs the startsequence of the engine
		///
		////////////////////////////////////////////////////////////
		void start();

		////////////////////////////////////////////////////////////
		/// Runs all the time to bring the engine to life
		///
		////////////////////////////////////////////////////////////
		void main();

		////////////////////////////////////////////////////////////
		/// Processess the Events
		///
		////////////////////////////////////////////////////////////
		void processEvents();


		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		bool			editor_mode;	///< states the mode
		Rendering		rendering;		///< The Rendering. It's the only class who own's one
		Lua				lua;			///< Lua State Holder and collection of nice functions
		Scene			scene;			///< The scene we are going to see
		sf::Font		font;			///< The Font we want to use to display the text
		Subtitle		subtitle;
		sf::Vector2i	mouse_pos;
		std::shared_ptr<sf::Sprite> editor_editing;	///< The Object we are editing
		sf::Vector2f	cursor_offset;
	};
}


#endif // !PC_ENGINE