#include "LuaBindings.hpp"
#pragma once

namespace itl {
	template<typename T>
	void LuaBindings::bindSfmlVector(const std::string& s) {
		lua.new_usertype<sf::Vector2<T>>("Vector2" + s,
			sol::constructors<sf::Vector2<T>(), sf::Vector2<T>(T,T)>(),
			"x", &sf::Vector2<T>::x,
			"y", &sf::Vector2<T>::y);

		lua.new_usertype<sf::Vector3<T>>("Vector3" + s,
			sol::default_constructor,
			"x", &sf::Vector3<T>::x,
			"y", &sf::Vector3<T>::y,
			"z", &sf::Vector3<T>::z);
	}

	template<typename T>
	inline void LuaBindings::bindSfmlRect(const std::string& s) {
		lua.new_usertype<sf::Rect<T>>(s + "Rect",
			sol::default_constructor,
			"left", &sf::Rect<T>::left,
			"top", &sf::Rect<T>::top,
			"width", &sf::Rect<T>::width,
			"height", &sf::Rect<T>::height,
			"contains", sol::overload(sol::resolve<bool(T,T) const>(&sf::Rect<T>::contains),
						sol::resolve<bool(const sf::Vector2<T>&) const>(&sf::Rect<T>::contains)),
			"intersects", sol::resolve<bool(const sf::Rect<T>&) const>(&sf::Rect<T>::intersects)
			
		);
	}

}