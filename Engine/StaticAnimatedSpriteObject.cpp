#include "StaticAnimatedSpriteObject.hpp"

namespace pc {

	StaticAnimatedSpriteObject::StaticAnimatedSpriteObject(const sf::Texture& texture, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions, std::function<void(const std::chrono::steady_clock::time_point&)> call_func) :callFunction{call_func}, SpriteObject { texture, position, name, actions } {
		type = types::STATIC_ANIMATED;
	}


	void StaticAnimatedSpriteObject::update(sf::Time elapsed) {
		if (elapsed > toWait) {
			toWait = sf::Time::Zero;
			callFunction(callback);
			return;
		}
		toWait -= elapsed;
		sprite->setTextureRect(getStateRect(state));
	}
}

