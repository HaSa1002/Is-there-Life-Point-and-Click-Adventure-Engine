#pragma once
#ifndef PC_RENDERING
#define PC_RENDERING

//itlEngine
#include "Menue.hpp"
//dependencis
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
//std library
#include <vector>

namespace pc {
	class Rendering {
	public:
		Rendering();
		~Rendering();

		void add(sf::Drawable& object);

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
		std::vector<sf::Drawable*> draw_list;
		std::vector<sf::Drawable*> gui_list;
		bool drawImGui = false;
		std::string title = "PnCAE";
		sf::RenderWindow window;
		sf::View view;
		sf::Vector2f offset;
	};
} //pc

#endif // !PC_RENDERING