#include "TextRenderComponent.hpp"

namespace itl {

	TextRenderComponent::TextRenderComponent(const std::wstring & s, const std::string & fontp, unsigned int charSize) { 
		font.loadFromFile(fontp);
		drawable.setFont(font);
		drawable.setCharacterSize(charSize);
		drawable.setString(s);
	}

	void TextRenderComponent::setString(const std::wstring & s) { 
		drawable.setString(s);
	}

	void TextRenderComponent::setCharSize(unsigned int size) { 
		drawable.setCharacterSize(size);
	}

	void TextRenderComponent::setLineSpacing(float factor) { 
		drawable.setLineSpacing(factor);
	}

	void TextRenderComponent::setLetterSpacing(float factor) { 
		drawable.setLetterSpacing(factor);
	}

	void TextRenderComponent::setFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { 
		drawable.setFillColor(sf::Color(r,g,b,a));
	}

	void TextRenderComponent::setOutlineColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { 
		drawable.setOutlineColor(sf::Color(r,g,b,a));
	}

	void TextRenderComponent::setOutlineThickness(float thickness) { 
		drawable.setOutlineThickness(thickness);
	}

	const std::wstring TextRenderComponent::getString() {
		return drawable.getString();
	}

	void TextRenderComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		target.draw(drawable, states);
	}
	sf::Transformable* TextRenderComponent::getTransformable() {
		return &drawable;
	}
	sf::FloatRect TextRenderComponent::getLocalBounds() {
		return drawable.getLocalBounds();
	}
	sf::FloatRect TextRenderComponent::getGlobalBounds() {
		return drawable.getGlobalBounds();
	}

}

