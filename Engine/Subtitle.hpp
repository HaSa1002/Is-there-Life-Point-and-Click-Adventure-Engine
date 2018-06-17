#pragma once
#include "Lua.hpp"
#include <SFML\Graphics.hpp>
#include <memory>



namespace pc {
	struct Subtitle {
	public:
		Subtitle();

		void setSettings(const ScriptEngine::SubtitleValue& vals);

		size_t getMiddlePosition();

		bool update(const sf::Vector2u & w_size, const sf::Time& t);

		////////////////////////////////////////////////////////////
		/// sets the subtitle
		///
		////////////////////////////////////////////////////////////
		void setSubtitle(const std::wstring & to_set);


		std::shared_ptr<sf::Text>		subtitle;		///< The Subtitle we want to display
		sf::Font						font;
		std::wstring					text;
		sf::Vector2u & window_size;
	private:
		
	};
}