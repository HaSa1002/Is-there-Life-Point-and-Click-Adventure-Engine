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
#include "SceneNode.hpp"
#include "TextureManager.hpp"
#include "Lua.hpp"
#include "Event.hpp"

#include <SFML\Graphics\VertexBuffer.hpp>
#include <SFML\Graphics\Vertex.hpp>
#include <SFML\Graphics\PrimitiveType.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>



namespace itl {
	class LuaObject : public SceneNode {
	public:
		
		LuaObject(const std::string& n, const std::string& t, const TextureManager& tm,  const int x, const int y);
		LuaObject(const std::string& n, const std::string& t, const TextureManager& tm, const int x, const int y, const int a);
		LuaObject(const std::string& n, const std::string& t, const TextureManager& tm, const int x, const int y, const int a, const float sx, const float sy);

		void setTexture(const std::string& name);

		auto getTexture() -> const std::string&;


	private:
		virtual void updateCurrent(sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::IntRect getTextureRect();

		const sf::FloatRect getLocalBounds();

		void updatePositions();

		void updateTexCoords();

		void setColor(const sf::Color & color);

		std::string texture_name;
		size_t texture_hash;

		const std::string object_name;
		sf::Vertex vertices[4];
		const std::shared_ptr<LuaObject> t;
		sf::Sprite sprite;
		sf::Texture* texture_ref;
		TextureManager tm;
	};
}