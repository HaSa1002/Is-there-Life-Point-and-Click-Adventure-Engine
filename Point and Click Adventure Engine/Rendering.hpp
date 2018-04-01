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

#ifndef PC_RENDERING
#define PC_RENDERING

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <Bus.hpp>

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <vector>
#include <memory>
#include <list>

namespace pc {
	////////////////////////////////////////////////////////////
	/// Class that gives a highlevel draw-API
	///
	////////////////////////////////////////////////////////////
	class Rendering {
	public:

		////////////////////////////////////////////////////////////
		/// Default Constructor
		///
		/// Sets the Messagebus and subscribes to some Events
		///
		////////////////////////////////////////////////////////////
		Rendering(mb::Bus& message_bus);

		////////////////////////////////////////////////////////////
		/// Default Deconstructor
		///
		/// Closes the Window, so that it can delete all attached
		/// resources.
		///
		////////////////////////////////////////////////////////////
		~Rendering();

		////////////////////////////////////////////////////////////
		/// Adds a item to the draw list
		///
		/// Adds a shared pointer of the sf::Drawable to it's internal
		/// draw list.
		///
		/// param object shared_ptr to the drawable
		///
		////////////////////////////////////////////////////////////
		void add(std::shared_ptr<sf::Drawable> object, int layer);

		////////////////////////////////////////////////////////////
		/// Adds a item to the gui draw list
		///
		/// Adds a shared pointer of the sf::Drawable to it's internal
		/// gui draw list.
		///
		/// param object shared_ptr to the drawable
		///
		////////////////////////////////////////////////////////////
		void addGUI(std::shared_ptr<sf::Drawable> gui_element, int layer);

		////////////////////////////////////////////////////////////
		/// Closes the window
		///
		/// The Rendering object stayes valid, but be carefull,
		/// currently the Rendering class does not checks if the
		/// window is closed and may behave with an undefined behaviour.
		/// 
		////////////////////////////////////////////////////////////
		void closeWindow();

		////////////////////////////////////////////////////////////
		/// Creates the window
		///
		/// Creates the window with the title "ITLengine" and the 
		/// given sf::VideoMode
		///
		/// param video_mode sf::VideoMode to display
		///					 Default: 1600x900
		///
		////////////////////////////////////////////////////////////
		void createWindow(sf::VideoMode video_mode = sf::VideoMode(1600, 900));

		////////////////////////////////////////////////////////////
		/// Creates the window
		///
		/// Creates the window with th given arguments. Please note,
		/// that if fullscreen is enabled, the engine may override your
		/// video_mode, due the fact, that it isn't displayable.
		///
		/// param title		 string of the title
		/// param fullscreen bool wether fullscreen should been displayed or not
		/// param video_mode sf::VideoMode to display (0,0,0), which is
		///						the standard means that the best will be
		///						selected, once implemented (TODO)
		/// 
		////////////////////////////////////////////////////////////
		void createWindow(const std::string& title, const bool& fullscreen, const sf::VideoMode& video_mode = sf::VideoMode(0, 0, 0));

		////////////////////////////////////////////////////////////
		/// TODO: Think about that
		///
		/// I forgot why I defined that.
		/// Neither used nor implemented currently.
		/// 
		////////////////////////////////////////////////////////////
		void display();

		////////////////////////////////////////////////////////////
		/// Returns a std::vector of all supported sf::VideoModes
		///
		/// returns: std::vector of all supported sf::VideoModes
		/// 
		////////////////////////////////////////////////////////////
		auto getVideoModes()-> const std::vector<sf::VideoMode>;

		////////////////////////////////////////////////////////////
		/// Returns the underlying sf::RenderWindow&
		///
		/// This method is undecided. It's currently widely used for
		/// rendering and event operations. This should became part of
		/// this class.
		///
		/// returns: Reference to the underlying sf::RenderWindow object
		///			 Should be valid as the instance of this class is
		///			 valid
		/// 
		////////////////////////////////////////////////////////////

		auto getWindowObject()->sf::RenderWindow&;

		////////////////////////////////////////////////////////////
		/// Sets imGui rendering state
		///
		/// param draw bool if imGui should be drawn
		/// 
		////////////////////////////////////////////////////////////
		void imgui_rendering(bool draw = true);

		////////////////////////////////////////////////////////////
		/// Is the window open?
		///
		/// returns state of window
		///
		////////////////////////////////////////////////////////////
		bool isOpen();

		////////////////////////////////////////////////////////////
		/// Moves the camera (sf::View)
		///
		/// The movement is proceeded relativly to the previous position
		///
		/// param offset where to move relativly
		///
		/// idea/remark/todo: Movement with speed and not a position set
		///			Maybe just add a setPosition()??
		///
		////////////////////////////////////////////////////////////
		void move(const sf::Vector2f& offset);

		////////////////////////////////////////////////////////////
		/// Sends the SFML Events to the Message Bus and do optimisations
		///
		////////////////////////////////////////////////////////////
		void processEvents();

		////////////////////////////////////////////////////////////
		/// Recieves the messages from the Message Bus and calls
		/// the nessessary methods
		/// 
		///
		////////////////////////////////////////////////////////////
		void reciever(mb::Message messages);

		////////////////////////////////////////////////////////////
		/// Renders the content in the draw lists
		///
		/// The Rendering order is defined in the draw lists, but
		/// since it's very uncommen to have the GUI under the actual
		/// scene we have diffrent draw_lists. That results in this
		/// draw order:
		///  1. draw_list
		///  2. gui_list
		///  3. imGui
		///
		////////////////////////////////////////////////////////////
		void render();

		////////////////////////////////////////////////////////////
		/// Removes an object from the draw list
		///
		///
		/// param object shared_ptr to the drawable
		///
		////////////////////////////////////////////////////////////
		void remove(std::shared_ptr<sf::Drawable> object);

		////////////////////////////////////////////////////////////
		/// Removes an object from the gui list
		///
		///
		/// param object shared_ptr to the drawable
		///
		////////////////////////////////////////////////////////////
		void removeGUI(std::shared_ptr<sf::Drawable> gui_element);

		////////////////////////////////////////////////////////////
		/// Resets the camera
		///
		////////////////////////////////////////////////////////////
		void reset();

		////////////////////////////////////////////////////////////
		/// Sets the camera (sf::View)
		///
		/// The position is set relativly to the previous position
		///
		/// param offset where to set relativly
		///
		/// remark: If you wish to have an animation use
		///			Rendering::move() instead
		///
		////////////////////////////////////////////////////////////
		void setPosition(sf::Vector2f offset);

		////////////////////////////////////////////////////////////
		/// Zooms the camera (sf::View)
		///
		/// The position is set relativly to the previous position
		///
		/// param offset where to set relativly
		///
		/// remark: If you wish to have an animation use
		///			Rendering::move() instead
		///
		////////////////////////////////////////////////////////////
		void zoom(const float factor, const bool animated);

	private:
		/// Recieverfunction
		std::function<void(mb::Message)> render_reciever = [this](mb::Message message) {
			this->reciever(message);
		};

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		mb::Bus&												bus;										///< Message Bus
		bool													draw_imgui				= false;			///< States if imGui should be drawn
		std::vector<std::list<std::shared_ptr<sf::Drawable>>>	draw_list;									///< Contains pointers to the objects, that should be drawn
		bool													fullscreen				= false;			///< States if the window should be constructed in Fullscreenmode
		std::vector<std::list<std::shared_ptr<sf::Drawable>>>	gui_list;									///< Contains pointers to the objects, that should be drawn as gui (in foreground)
		sf::Vector2f											offset;										///< The absolut position the view has to (0,0)
		bool													has_focus				= true;				///< Used to save power when there is no focus
		std::string												title;										///< Stores the title of the window, as it is possible required when recreating the window
		sf::VideoMode											video_mode;									///< Stores the video_mode
		sf::View												view;										///< Our Camera that we are controlling
		sf::RenderWindow										window;										///< Window we are rendering to
		float													zoom_level = 1.f;							///< The absolut zoom_level to the initated one
	};
} // namespace pc

#endif // !PC_RENDERING

////////////////////////////////////////////////////////////
/// class pc::Rendering
/// 
/// The Rendering class is one of the foundational classes in
/// this engine. It allows you to render sf::Drawables and the
/// gui (wheter it is imgui or in the future cegui).
/// 
/// As the engine this class is not completed yet, what means
/// that it is constantly improved, changed and/or updated.
/// 
/// ToDos:
///  - Animation controlling
///  - Time handling
///  - Constant refresh time
///  - View handling
///  - Optimisations on the use of textures etc.
///  - General optimisations, due it's proably the most time-
///		critical class
/// 
////////////////////////////////////////////////////////////