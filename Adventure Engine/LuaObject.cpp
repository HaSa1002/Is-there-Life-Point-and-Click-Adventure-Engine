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

#include "LuaObject.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////


namespace itl {
	extern std::map<size_t, std::weak_ptr<SceneNode>>	scene_layers;
	extern SceneNode									scene_graph;

	LuaObject::LuaObject(const std::string& n, const std::string& t, const TextureManager& tm, const int x, const int y) : LuaObject(n, t, tm, x, y, 0, 1.f, 1.f) { }


	////////////////////////////////////////////////////////////
	LuaObject::LuaObject(const std::string& n, const std::string& t, const TextureManager& tm, const int x, const int y, const int a) : LuaObject(n, t, tm, x, y, a, 1.f, 1.f) { }


	////////////////////////////////////////////////////////////
	LuaObject::LuaObject(const std::string& n, const std::string& t, const TextureManager& tm, const int x, const int y, const int a, const float sx, const float sy) : object_name { n }, tm { tm } {
		setTexture(t);
		setPosition(x,y);
		setRotation(a);
		setScale(sx,sy);
		//Create the object table to give the user a place to put their functions into
		//FIXME: Get the tablecreation done
		//lua.lua.script("objects."+object_name+" = {}");
	}


	////////////////////////////////////////////////////////////
	void LuaObject::setTexture(const std::string & name) {
		std::hash<std::string> sh;
		texture_name = name;
		texture_hash = sh(texture_name);
		auto t = tm.find(texture_hash);
		if (t != nullptr) {
			texture_ref = &t->texture_ref;
			sprite.setTexture(t->texture_ref);
			sprite.setTextureRect(t->rect);
		}
		updatePositions();
		updateTexCoords();

	}


	////////////////////////////////////////////////////////////
	auto LuaObject::getTexture() -> const std::string & {
		return texture_name;
	}



		////////////////////////////////////////////////////////////
		void LuaObject::updateCurrent(sf::Time dt) {
		/*if (lua.lua["objects"]["test"].get_type() == sol::type::table) {
			printf("Found");
		} else {
			printf("%d", lua.lua["objects"]["test"].get_type());
		}
		if (last_event == nullptr) lua.lua["objects"][object_name]["update"].call(dt.asSeconds());
		else lua.lua["objects"][object_name]["update"].call(dt.asSeconds(), last_event->action, last_event->x, last_event->y);*/
	}


	////////////////////////////////////////////////////////////
	void LuaObject::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
		if (texture_ref) {
			states.texture = texture_ref;
			target.draw(vertices, 4, sf::PrimitiveType::TriangleStrip, states);
		} else {
			printf("No texture set");
		}

	}


	////////////////////////////////////////////////////////////
	sf::IntRect LuaObject::getTextureRect() {
		auto r = tm.find(texture_hash);
		if (r == nullptr) {
			printf("%s hasn't a correct texture. Texturename was \"%s\". Are you sure the spelling is correct?\n", object_name.data(), texture_name.data());
			assert(r); // The Texture can't be nothing. Check the spelling
			return sf::IntRect();
		}
		return r->rect;
	}


	////////////////////////////////////////////////////////////
	const sf::FloatRect LuaObject::getLocalBounds() {
		sf::IntRect t_rect = getTextureRect();
		float width = static_cast<float>(std::abs(t_rect.width));
		float height = static_cast<float>(std::abs(t_rect.height));

		return sf::FloatRect(0.f, 0.f, width, height);
	}


	////////////////////////////////////////////////////////////
	void LuaObject::updatePositions() {
		sf::FloatRect bounds = getLocalBounds();

		vertices[0].position = sf::Vector2f(0, 0);
		vertices[1].position = sf::Vector2f(0, bounds.height);
		vertices[2].position = sf::Vector2f(bounds.width, 0);
		vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
	}


	////////////////////////////////////////////////////////////
	void LuaObject::updateTexCoords() {
		sf::IntRect t_rect = getTextureRect();
		float left = static_cast<float>(t_rect.left);
		float right = left + t_rect.width;
		float top = static_cast<float>(t_rect.top);
		float bottom = top + t_rect.height;

		vertices[0].texCoords = sf::Vector2f(left, top);
		vertices[1].texCoords = sf::Vector2f(left, bottom);
		vertices[2].texCoords = sf::Vector2f(right, top);
		vertices[3].texCoords = sf::Vector2f(right, bottom);
	}

	////////////////////////////////////////////////////////////
	void LuaObject::setColor(const sf::Color& color) {
		// Update the vertices' color
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;
	}
}


