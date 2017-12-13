#pragma once
#ifndef PC_RENDERING
#define PC_RENDERING

#include <vector>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>


namespace pc {
	class Rendering {
	public:
		Rendering();
		~Rendering();

		void add(sf::Drawable& object);

		void addGUI(sf::Drawable& gui_element);

		void closeWindow();

		void createWindow();

		void createWindow(sf::VideoMode videoMode);

		void createWindow(const std::string& title, const bool fullscreen, const sf::VideoMode = sf::VideoMode(0, 0, 0));

		void display();

		auto getVideoModes()-> const std::vector<sf::VideoMode>;

		void move(const sf::Vector2f& moveTo);

		void redraw();

		void remove(const sf::Drawable& object);

		void removeGUI(const sf::Drawable& gui_element);

		void reset();

		///Möglicherweise ist das eine blöde Idee, da ich dann schauen muss welches Modul was managet
		void setDrawList(const std::vector<sf::Drawable> drawList);

		void setVideoMode(const sf::VideoMode = sf::VideoMode(100, 100));

		void zoom(const float& level);

	protected:
		std::vector<sf::Drawable&> draw_list;
		std::vector<sf::Drawable&> gui_list;
		std::string title = "PnCAE";
		sf::RenderWindow window;
	};
}

#endif // !PC_RENDERING