#include "Subtitle.hpp"


namespace pc { 

	Subtitle::Subtitle(Lua& l) :lua{ l } { 
		subtitle = std::make_shared<sf::Text>();
	};


	void Subtitle::setSettings() {
		if (!font.loadFromFile(lua.lua["game"]["subtitleFont"].get_or<std::string>(""))) {

		}
		subtitle->setFont(font);
		subtitle->setCharacterSize(lua.lua["game"]["subtitleSize"].get_or(30));
		auto color = lua.lua["game"]["subtitleColor"];
		subtitle->setFillColor(sf::Color(color[1].get_or(255), color[2].get_or(255), color[3].get_or(255), color[4].get_or(255)));
	}


	size_t Subtitle::getMiddlePosition() {
		std::vector<size_t> sizes;
		sizes.push_back(0);
		do {
			sizes.push_back(text.find('\n', sizes.back() + 1));
		} while (sizes.back() != std::string::npos);

		size_t longest = 0;
		size_t pos = 0;
		for (size_t i = 1; i < sizes.size() - 1; ++i) {
			if (sizes[i] - sizes[i - 1] > longest) {
				longest = sizes[i] - sizes[i - 1];
				pos = i - 1;
			}
		}
		return (sizes.size() > 2) ? sizes[pos] + (longest / 2) : (text.size() / 2);
	}



	void Subtitle::updateSubtitle(const sf::Vector2u& window_size) {
		lua.getSubtitleToBeLoaded(text);
		subtitle->setString(text);
		subtitle->setPosition(static_cast<float>(window_size.x / 2), static_cast<float>(subtitle->getCharacterSize() + 20));
		subtitle->move(-subtitle->findCharacterPos(getMiddlePosition()).x + (window_size.x / 2), 0);
	}
}
