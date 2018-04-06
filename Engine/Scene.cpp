////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
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
#include "Scene.hpp"
#include "config.hpp"
#include <cmath>

namespace pc {
	void Scene::addObject(const std::string & texture_path, const sf::Vector3i& position) {
		addObject(texture_path, position, "", std::list<char>());
	}


	////////////////////////////////////////////////////////////
	void Scene::addObject(const std::string & texture_path, const sf::Vector3i & position, const std::string & name, const std::list<char>& action) {
		if (texture_path.size() > 1) {
			if (texture_path[0] == 'r') {
				
				sf::Vector2f size(std::stof(texture_path.substr(1, texture_path.find(','))), std::stof(texture_path.substr(texture_path.find(',') + 1)));
				objects.emplace_back(sf::RectangleShape(size), position, name, action);
				return;
			}
			if (texture_path[0] == 't') {

				//sf::Vector2f size(std::stof(texture_path.substr(1, texture_path.find(','))), std::stof(texture_path.substr(texture_path.find(',') + 1)));
				//objects.emplace_back(sf::RectangleShape(size), position, name, action);
				return;
			}
		}
		textures.emplace_back(sf::Texture());
		if (!textures.back().loadFromFile(texture_path)) {
#if defined _DEBUG || !defined NO_EXCEPTIONS
			throw Exception::cantLoadImage;
#else
			printf("Couldn't load image from: \"%s\"\n", texture_path.data());
#endif
		}
		objects.emplace_back(sf::Sprite(textures.back()), position, name, action);
	}


	////////////////////////////////////////////////////////////
	void Scene::addWalkbox(const sf::IntRect & rectangle, const bool is_active) {
		walkboxes.emplace_back(rectangle, is_active);
	}


	////////////////////////////////////////////////////////////
	void Scene::addZoomline(const sf::IntRect& position, const float factor, const bool is_active) {
		zoomlines.emplace_back(position, factor, is_active);
	}

	bool Scene::sort_objects_by_layer(const Object & l, const Object & r) {
		return (l.layer > r.layer) ? true : false;
	}

	void Scene::createEditorHelper() {
		if (helper_count.x + 1 != objects.size() || helper_count.y + 1 != walkboxes.size() || helper_count.z + 1 != zoomlines.size()) {
			helper.clear();
			helper_count *= 0;
			for (auto& i : objects) {
				if (i.type == 'c') {
					helper.emplace_back(*i.click);
					helper.back().setOutlineColor(sf::Color::Red);
					helper.back().setOutlineThickness(1.f);
					helper.back().setFillColor(sf::Color::Transparent);
					++helper_count.x;
				}
				if (i.type == 's') {
					helper.emplace_back(sf::Vector2f(i.sprite->getGlobalBounds().width, i.sprite->getGlobalBounds().height));
					helper.back().setPosition(i.sprite->getGlobalBounds().left, i.sprite->getGlobalBounds().top);
					helper.back().setOutlineColor(sf::Color::Red);
					helper.back().setOutlineThickness(1.f);
					helper.back().setFillColor(sf::Color::Transparent);
					++helper_count.x;
				}
			}
			for (auto& i : walkboxes) {
				sf::Vector2i rect(sf::Vector2i(i.rectangle.left, i.rectangle.top) - sf::Vector2i(i.rectangle.width, i.rectangle.height));
				helper.emplace_back(sf::Vector2f(i.rectangle.width, i.rectangle.height));
				helper.back().setPosition(i.rectangle.left, i.rectangle.top);
				helper.back().setOutlineColor(sf::Color::Green);
				helper.back().setOutlineThickness(1.f);
				helper.back().setFillColor(sf::Color::Transparent);
				++helper_count.y;
			}
			for (auto& i : zoomlines) {
				float r = std::hypotf(i.position.width - i.position.left, i.position.height - i.position.top);
				if (r == 0)
					continue;
				int y = i.position.height - i.position.top;
				helper.emplace_back(sf::Vector2f(r, 1));
				helper.back().setPosition(i.position.left, i.position.top);
				helper.back().setRotation(std::asin(y/r) * 180 / PI);
				helper.back().setFillColor(sf::Color::Blue);
				++helper_count.z;
			}
		}
	}

	void Scene::reset() {
		textures.clear();
		objects.clear();
		walkboxes.clear();
		zoomlines.clear();
		helper.clear();
		helper_count *= 0;
	}


	////////////////////////////////////////////////////////////
	Scene::Object::Object(const sf::Sprite & s, const sf::Vector3i & pos, const std::string & call, const std::list<char>& a) : sprite{std::make_shared<sf::Sprite>(s)}, layer {pos.z}, name{call}, actions{a} {
		sprite->setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
		type = 's';
	}

	Scene::Object::Object(const sf::RectangleShape & c, const sf::Vector3i & pos, const std::string & call, const std::list<char>& actions) : click{ std::make_shared<sf::RectangleShape>(c) }, layer{ pos.z }, name{ call }, actions{ actions } {
		click->setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
		type = 'c';
	}

	Scene::Object::Object(const Object & object) {
		switch (object.type) {
		case 's':
			sprite = object.sprite;
			break;
		case 'c':
			click = object.click;
			break;
		}
		type = object.type;
		layer = object.layer;
		name = object.name;
		actions = object.actions;
	}

	Scene::Object::~Object() {
	}


	////////////////////////////////////////////////////////////
	bool Scene::Object::has_action(const char& action) {
		for (const auto& a : actions) {
			if (a == action)
				return true;
		}
		return false;
	}
	void Scene::Object::set_position(const sf::Vector2i & pos) {
		switch (type) {
		case 's':
			sprite->setPosition(sf::Vector2f(pos));
			break;
		case 'c':
			click->setPosition(sf::Vector2f(pos));
			break;
		case 't':
			text->setPosition(sf::Vector2f(pos));
			break;
		}
	}
}

