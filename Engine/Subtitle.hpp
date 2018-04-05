#pragma once
#include "Lua.hpp"
#include <SFML\Graphics.hpp>
#include <memory>



namespace pc {
	struct Subtitle {
	public:
		Subtitle(Lua& l);

		void setSettings();

		size_t getMiddlePosition();

		////////////////////////////////////////////////////////////
		/// set the subtitle
		///
		////////////////////////////////////////////////////////////
		void updateSubtitle(const sf::Vector2u& window_size);


		std::shared_ptr<sf::Text>		subtitle;		///< The Subtitle we want to display
		sf::Font						font;
		std::string						text;
	private:
		Lua& lua;
		
		
	};
}