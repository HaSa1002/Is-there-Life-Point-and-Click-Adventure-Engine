#include "Animation.hpp"

namespace pc {
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


