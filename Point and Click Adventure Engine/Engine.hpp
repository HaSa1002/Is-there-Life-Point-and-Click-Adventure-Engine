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
#include "Pipeline.hpp"
#include "Rendering.hpp"
#include "Menuemanager.hpp"
#include <System.hpp>
#include <Bus.hpp>



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
		Engine(bool editor) :rendering{ bus }, pipeline{ bus }, ecs{ bus }, editor_mode { editor } { start(); };

		////////////////////////////////////////////////////////////
		/// We don't have an default constructor
		///
		////////////////////////////////////////////////////////////
		Engine() = delete;

		//DELETE
		////////////////////////////////////////////////////////////
		/// Gives the underlaying Renderingclass
		///
		/// returns pc::Rendering&
		///
		////////////////////////////////////////////////////////////
		auto getRendering()->Rendering&;

	private:

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
		/// Sends the SFML Events to the Message Bus
		///
		////////////////////////////////////////////////////////////
		void processEvents();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		mb::Bus						bus;			///< The Message Bus. It's the only class who own's one
		cs::System					ecs;			///< The ECS. It's the only class who own's one
		bool						editor_mode;	///< states the mode
		Lvleditor::Menuemanager		menue;			///< ImGui Menuemanager
		Pipeline					pipeline;		///< The Data Pipeline. It's the only class who own's one
		Rendering					rendering;		///< The Rendering. It's the only class who own's one
	};
}


#endif // !PC_ENGINE