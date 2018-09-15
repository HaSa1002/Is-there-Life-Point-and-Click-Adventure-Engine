#pragma once
namespace sf {
	template<typename T>
	inline bool operator<(const sf::Vector2<T>& left, const sf::Vector2<T>& right) {
		if (left.x * left.y < right.x * right.y) return true;
		return false;
	}
}