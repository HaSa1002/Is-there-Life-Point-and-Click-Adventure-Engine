#include "TimedAnimatedSpriteObject.hpp"

namespace pc {

	TimedAnimatedSpriteObject::TimedAnimatedSpriteObject(const sf::Texture& texture, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions) :SpriteObject { texture, position, name, actions } {
		type = types::TIMED_ANIMATED;
	}


	void TimedAnimatedSpriteObject::update(sf::Time elapsed) {
		if (elapsed > toWait) {
			if (currentTime + 1 >= times.size())
				currentTime = 0;
			else
				++currentTime;

			elapsed -= toWait;
			toWait = times[currentTime].second;
		}
		toWait -= elapsed;
		sprite->setTextureRect(getStateRect(times[currentTime].first));
	}
}

