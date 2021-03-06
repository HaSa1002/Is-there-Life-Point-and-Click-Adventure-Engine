////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "RenderComponent.hpp"
#include "SFML/Graphics/Text.hpp"

namespace itl {
	class TextRenderComponent : public sf::Drawable {
	public:
		TextRenderComponent(const std::wstring& s, const std::string& fontp, unsigned int charSize);

		void setString(const std::wstring& s);

		void setCharSize(unsigned int size);

		void setLineSpacing(float factor);

		void setLetterSpacing(float factor);

		void setFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		void setOutlineColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		void setColor(unsigned char r, unsigned char g, unsigned char b, float a);

		void setOutlineThickness(float thickness);

		const std::wstring& getString();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Transformable* getTransformable();

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	private:
		std::wstring string;
		sf::Text drawable;
		sf::Font font;
	};
}