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
		void redraw();

		void createWindow(sf::VideoMode windowSize);

		///Möglicherweise ist das eine blöde Idee, da ich dann schauen muss welches Modul was managet
		void setDrawList(const std::vector<sf::Drawable> drawList);

	protected:
		std::vector<sf::Drawable> drawList;
		sf::RenderWindow window;
	};
}

#endif // !PC_RENDERING