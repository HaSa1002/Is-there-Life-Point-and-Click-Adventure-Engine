////////////////////////////////////////////////////////////
// 
// SFML Point and Click Adventure Engine (ITLengine)
// Copyright (c) 2017 Johannes Witt
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
#include "Menue.hpp"
//Dependencies
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
//STD Library
#include <vector>
#include <memory>

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
		/// Does nothing.
		///
		////////////////////////////////////////////////////////////
		Rendering();

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
		/// param object
		///
		////////////////////////////////////////////////////////////
		void add(std::shared_ptr<sf::Drawable> object);

		void addGUI(sf::Drawable& gui_element);
		
		void addGUI(bool imGui_drawing = true);

		void closeWindow();

		void createWindow();

		void createWindow(sf::VideoMode video_mode);

		void createWindow(const std::string& title, const bool fullscreen, const sf::VideoMode video_mode = sf::VideoMode(0, 0, 0));

		void display();

		auto getVideoModes()-> const std::vector<sf::VideoMode>;

		auto getWindowObject()->sf::RenderWindow&;

		bool isOpen();

		void move(const sf::Vector2f& offset);

		void redraw();

		void remove(const sf::Drawable* object);

		void removeGUI(const sf::Drawable& gui_element);

		void reset();

		///Möglicherweise ist das eine blöde Idee, da ich dann schauen muss welches Modul was managet
		void setDrawList(const std::vector<sf::Drawable> drawList);

		void setVideoMode(const sf::VideoMode = sf::VideoMode(1600, 900));

		void zoom(const float factor);


	protected:
		std::vector<std::shared_ptr<sf::Drawable>> draw_list;
		std::vector<sf::Drawable*> gui_list;
		bool drawImGui = false;
		std::string title = "PnCAE";
		sf::RenderWindow window;
		sf::View view;
		sf::Vector2f offset;
	};
} //pc

#endif // !PC_RENDERING