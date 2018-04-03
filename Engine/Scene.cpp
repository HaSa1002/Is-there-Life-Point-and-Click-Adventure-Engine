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

namespace pc {
	void Scene::addObject(const std::string & texture_path, const sf::Vector3i& position) {
		addObject(texture_path, position, "", std::list<char>());
	}

	void Scene::addObject(const std::string & texture_path, const sf::Vector3i & position, const std::string & callback, const std::list<char>& action) {
		textures.emplace_back(sf::Texture());
		if (!textures.back().loadFromFile(texture_path)) {
			throw Exception::cantLoadImage;
		}
		objects.emplace_back(Object(sf::Sprite(textures.back()), position, callback, action));
	}

	Scene::Object::Object(const sf::Sprite & s, const sf::Vector3i & pos, const std::string & call, const std::list<char>& a) : sprite{s}, layer {pos.z}, callback{call}, actions{a} {
		sprite.setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
	}
	bool Scene::Object::has_action(const char& action) {
		for (const auto& a : actions) {
			if (a == action)
				return true;
		}
		return false;
	}
}

