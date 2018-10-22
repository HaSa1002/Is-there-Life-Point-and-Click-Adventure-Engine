#pragma once

namespace itl {
	template<typename T, char N>
	void LuaBindings::bindSfmlVector() {
		lua.new_usertype<sf::Vector2<T>>("Vector2" + N,
			sol::default_constructor,
			"x", &sf::Vector2<T>::x,
			"y", &sf::Vector2<T>::y);

		lua.new_usertype<sf::Vector3<T>>("Vector3" + N,
			sol::default_constructor,
			"x", &sf::Vector3<T>::x,
			"y", &sf::Vector3<T>::y,
			"z", &sf::Vector3<T>::z);
	}

}