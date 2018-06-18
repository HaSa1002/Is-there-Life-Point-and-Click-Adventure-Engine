#include "Subtitle.hpp"


namespace pc { 

	Subtitle::Subtitle() { 
		subtitle = std::make_shared<sf::Text>();
	};


	void Subtitle::setSettings(const ScriptEngine::SubtitleValue& vals) {
		if (!font.loadFromFile(vals.font)) {

		}
		subtitle->setFont(font);
		subtitle->setCharacterSize(vals.size);
		subtitle->setFillColor(vals.color);
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

	bool Subtitle::update(const sf::Vector2u & w_size, const sf::Time & t) {
		window_size = w_size;
		return true;
	}



	void Subtitle::setText(const std::wstring& to_set) {
		text = to_set;
		subtitle->setString(text);
		subtitle->setPosition(static_cast<float>(window_size.x / 2), static_cast<float>(subtitle->getCharacterSize() + 20));
		subtitle->move(-subtitle->findCharacterPos(getMiddlePosition()).x + (window_size.x / 2), 0);
	}
}
