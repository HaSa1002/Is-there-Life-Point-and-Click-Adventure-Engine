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
				objects.emplace_back(std::make_shared<Object>(sf::RectangleShape(size), position, name, action));
				objects.back()->texture_string = texture_path;
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
		objects.emplace_back(std::make_shared<Object>(textures.back(), position, name, action));
		objects.back()->texture_string = texture_path;
	}


	void Scene::addMoveableObject(const std::string& texture_path, const sf::Vector3i& position, const std::string& name, const std::list<char>& actions) {
		textures.emplace_back(sf::Texture());
		if (!textures.back().loadFromFile(texture_path.substr(1))) {
#if defined _DEBUG || !defined NO_EXCEPTIONS
			throw Exception::cantLoadImage;
#else
			printf("Couldn't load image from: \"%s\"\n", texture_path.data());
#endif
		}

		objects.emplace_back(std::make_shared<MoveableObject>(textures.back(), position, name, actions, ""));
		objects.back()->texture_string = texture_path;
	}


	////////////////////////////////////////////////////////////
	void Scene::addWalkbox(const sf::IntRect & rectangle, const bool is_active) {
		walkboxes.emplace_back(rectangle, is_active);
	}


	////////////////////////////////////////////////////////////
	void Scene::addZoomline(const sf::IntRect& position, const float factor, const bool is_active) {
		zoomlines.emplace_back(position, factor, is_active);
	}

	bool Scene::sort_objects_by_layer(const std::shared_ptr<Object> & l, const std::shared_ptr<Object> & r) {
		return (l->layer > r->layer) ? true : false;
	}

	void Scene::createEditorHelper() {
		if (helper_count.x + 1 != objects.size() || helper_count.y + 1 != walkboxes.size() || helper_count.z + 1 != zoomlines.size()) {
			helper.clear();
			helper_count *= 0;
			for (auto& i : objects) {
				if (i->type == 'c') {
					helper.emplace_back(*i->click);
					helper.back().setOutlineColor(sf::Color::Red);
					helper.back().setOutlineThickness(1.f);
					helper.back().setFillColor(sf::Color::Transparent);
					++helper_count.x;
				}
				if (i->type == 's' || i->type == 'm') {
					helper.emplace_back(sf::Vector2f(i->sprite->getGlobalBounds().width, i->sprite->getGlobalBounds().height));
					helper.back().setPosition(i->sprite->getGlobalBounds().left, i->sprite->getGlobalBounds().top);
					helper.back().setOutlineColor(sf::Color::Red);
					helper.back().setOutlineThickness(1.f);
					helper.back().setFillColor(sf::Color::Transparent);
					++helper_count.x;
				}
			}
			for (auto& i : walkboxes) {
				sf::Vector2i rect(sf::Vector2i(i.rectangle.left, i.rectangle.top) - sf::Vector2i(i.rectangle.width, i.rectangle.height));
				helper.emplace_back(sf::Vector2f(static_cast<float>(i.rectangle.width), static_cast<float>(i.rectangle.height)));
				helper.back().setPosition(static_cast<float>(i.rectangle.left), static_cast<float>(i.rectangle.top));
				helper.back().setOutlineColor(sf::Color::Green);
				helper.back().setOutlineThickness(1.f);
				helper.back().setFillColor(sf::Color::Transparent);
				++helper_count.y;
			}
			for (auto& i : zoomlines) {
				float r = std::hypotf(static_cast<float>(i.position.width - i.position.left), static_cast<float>(i.position.height - i.position.top));
				if (r == 0)
					continue;
				int y = i.position.height - i.position.top;
				helper.emplace_back(sf::Vector2f(r, 1));
				helper.back().setPosition(static_cast<float>(i.position.left), static_cast<float>(i.position.top));
				helper.back().setRotation(std::asin(static_cast<float>(y/r)) * 180 / static_cast<float>(PI));
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

	std::shared_ptr<Object> Scene::getObject(const std::string & object_name) {
		for (auto& i : objects) {
			if (i->name == object_name)
			return i;
		}
		return nullptr;
	}

	std::string Scene::makeLuaString() {
		std::string result;
		result += "scenes[\"" + name + "\"] = {}\nlocal scene = scenes[\"" + name + "\"]\n scene[\"objects\"] = {\n";
		for (auto& i : objects) {
			result += "\t" + i->name + " = {";
			if (i->type == 's') {
				result += std::to_string((int)i->sprite->getPosition().x) + ',';
				result += std::to_string((int)i->sprite->getPosition().y) + ',';
			}
			if (i->type == 'c') {
				result += std::to_string((int)i->click->getPosition().x) + ',';
				result += std::to_string((int)i->click->getPosition().y) + ',';
			}
			result += std::to_string(i->layer) + ", \"" + i->texture_string + "\", {";
			for (char& j : i->actions) {
				result += "\'";
				result.push_back(j);
				result += "\', ";
			}
			result += "}},\n";
		}

		result += "}";

		result += "\n scene[\"walkboxes\"] = {\n";
		for (auto& i : walkboxes) {
			result += "\t{" + std::to_string(i.rectangle.top) + ", " + std::to_string(i.rectangle.left) + ", " + std::to_string(i.rectangle.width) + ", " + std::to_string(i.rectangle.height) + ", " + std::to_string(i.is_active) + "}\n";
		}

		result += "}";

		result += "\n scene[\"zoomlines\"] = {\n";
		for (auto& i : zoomlines) {
			result += "\t{" + std::to_string(i.position.top) + ", " + std::to_string(i.position.left) + ", " + std::to_string(i.position.width) + ", " + std::to_string(i.position.height) + ", " + std::to_string(i.factor) + ", " + std::to_string(i.is_active) + "}\n";
		}

		result += "}";

		return result;
	}


	////////////////////////////////////////////////////////////

}

