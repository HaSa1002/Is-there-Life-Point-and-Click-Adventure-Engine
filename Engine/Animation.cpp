#include "Animation.hpp"

namespace pc {
	const sf::Vector2i Animation::convertToVector2i(const sf::Vector2f& vec) {
		return sf::Vector2i(static_cast<int>(vec.x), static_cast<int>(vec.y));
	}


	const sf::IntRect Animation::getStateRect(std::string state) {
		std::hash<std::string> stringHash;
		return getStateRect(stringHash(state));
	}
	const sf::IntRect Animation::getStateRect(hash state) {
		for (const auto& i : states) {
			if (i.first == state)
				return i.second;
		}
		return sf::IntRect();
	}
}


