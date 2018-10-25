#include "TextRenderComponent.hpp"
#include <cmath>

namespace itl {

	TextRenderComponent::TextRenderComponent(const std::wstring & s, const std::string & fontp, unsigned int charSize) { 
		font.loadFromFile("data/fonts/" + fontp);
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

	void TextRenderComponent::setColor(unsigned char r, unsigned char g, unsigned char b, float a) {
		unsigned char alpha = static_cast<unsigned char>(std::round(a));
		setFillColor(r, g, b, alpha);
		setOutlineColor(r, g, b, alpha);
	}

	void TextRenderComponent::setOutlineThickness(float thickness) { 
		drawable.setOutlineThickness(thickness);
	}

	const std::wstring& TextRenderComponent::getString() {
		string = drawable.getString();
		return string;
	}

	void TextRenderComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		if (target.getViewport(target.getView()).intersects(static_cast<sf::IntRect>(drawable.getGlobalBounds())))
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

