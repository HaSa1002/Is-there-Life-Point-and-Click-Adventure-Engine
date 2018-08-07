#include "ResourceManager.hpp"

namespace pc {
	bool ResourceManager::addTexture(const std::string & path, const std::string & name) {
		textures.emplace(hasher(name), Texture{});
		auto t = textures.find(hasher(name));
		if (t == textures.end())
			return false;

		t->second.path = path;
		if (!t->second.texture.loadFromFile(path))
			return false;
		return true;
	}

	Texture * ResourceManager::getTexture(const hash name) {
		auto t = textures.find(name);
		if (t == textures.end())
			return nullptr;
		return &t->second;

	}

	Texture * ResourceManager::getTexture(const std::string & name) {
		return getTexture(hasher(name));
	}

}

