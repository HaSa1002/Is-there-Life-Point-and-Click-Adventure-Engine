#include "Object.hpp"

namespace pc {

	Object::Object(const Texture object_texture) :texture{ object_texture } {
		object.setTexture(*texture);
	}
	Object::Object(const Texture object_texture, sf::IntRect texture_area) : texture{ object_texture } {
		object.setTexture(*texture);
		object.setTextureRect(texture_area);
	}
	auto Object::getSprite() -> std::shared_ptr<sf::Sprite> {
		return std::make_shared<sf::Sprite>(object);
	}
}