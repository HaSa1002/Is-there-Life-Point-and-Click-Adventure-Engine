#include "AnimatedObject.hpp"

namespace pc {

	AnimatedObject::AnimatedObject(const sf::Texture& texture, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions, const std::string& trigger) :Object { texture, position, name, actions } {
		trigger_function = trigger;
		type = 'a';
		//if (!states.empty())
		//	states.clear();

	}


	void AnimatedObject::update(sf::Time elapsed) { 
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

