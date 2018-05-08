#pragma once
#include "Animation.hpp"


namespace pc {

	

	struct Character : Animation {
		SpriteSheet left;
		SpriteSheet right;
		SpriteSheet front;
		SpriteSheet back;
		sf::Sprite character;

	private:
		


	};
}