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

#include "TextureManager.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML\Graphics\Color.hpp>
#include <list>

namespace itl {

	bool sortRectSizes(const rbp::RectSize& l, const rbp::RectSize& r) {
		if (l.height * l.width < r.height * r.width) return true;
		return false;
	}

	TextureManager::TextureManager(std::vector<std::pair<const std::string&, const size_t>>& textures) {
		buffer = std::move(textures);
		this->build();
	}


	////////////////////////////////////////////////////////////
	const Texture* TextureManager::get(size_t name) {
		return &loaded_textures.find(name)->second;
	}


	////////////////////////////////////////////////////////////
	void TextureManager::add(const std::string & path, const size_t name) {
		buffer.push_back(std::move(std::make_pair(path, name)));
	}


	////////////////////////////////////////////////////////////
	void TextureManager::clear(bool onlyBuffer) {
		buffer.clear();
		if (!onlyBuffer) {
			loaded_textures.clear();
			textures.clear();
		}
	}


	////////////////////////////////////////////////////////////
	void TextureManager::build() {
		printf("%d", sf::Texture::getMaximumSize());
		std::list<rbp::RectSize> t_rects;
		std::map<const hashedName, sf::Image> images;

		//Step 1: Load the texture files
		for (const auto& i : buffer) {
			//Load the images
			sf::Image img;
			if (!img.loadFromFile(i.first))
				//We create a purple 50x50px Texture
				img.create(50, 50, sf::Color(255, 0, 255));
			images.emplace(i.second, std::move(img));

			//Save the rect for our packing algo
			rbp::RectSize r;
			r.name = i.second;
			sf::Vector2u size = img.getSize();
			r.height = size.y;
			r.width = size.x;
			t_rects.push_back(std::move(r));

		}

		//Step 1.1: Load textures from the texture if existing
		for (auto& i : loaded_textures) {
			
			//We should copy the images before and not every single time
			sf::Image img;
			img.create(i.second.rect.width, i.second.rect.height);
			img.copy(i.second.texture_ref.copyToImage(), 0, 0, i.second.rect);
			images.emplace(i.first, std::move(img));


			rbp::RectSize r;
			r.name = i.first;
			sf::Vector2u size = img.getSize();
			r.height = size.y;
			r.width = size.x;
			t_rects.push_back(std::move(r));
		}


		//Step 2: Prepare container and sort loaded images
		this->clear();

		t_rects.sort(&sortRectSizes);

		//Step 3: Prepare the MaxRect Algorithm
		std::vector<rbp::RectSize> rects;
		std::vector<rbp::Rect> res;
		rects.resize(t_rects.size());

		for (const auto& i : t_rects) {
			rects.push_back(i);
		}
		unsigned int maxSize = sf::Texture::getMaximumSize();
		rbp::MaxRectsBinPack packing(maxSize, maxSize, false);


		//Step 4: Run the MaxRect Algorithm
		packing.Insert(rects, res, rbp::MaxRectsBinPack::RectBestAreaFit);

		//Step 5: Create the textures by Interpreting the result
		sf::Texture t;
		sf::Vector2u s = packing.Size();
		t.create(s.x, s.y);
		for (auto& i : res) {
			auto img = images.find(i.name);
			t.update(img->second, i.x, i.y);
			loaded_textures.emplace(i.name, std::move(Texture(sf::IntRect(i.x, i.y, i.width, i.height), i.name, t)));
		}

		//Step 6: Push Textures to graphics device
		textures.push_back(std::move(t));

		//TODO: Change the way, the resources (are saved, so that you can build on top of existing texture atlas')




	}
	void TextureManager::addTexture(const sf::Vector2u& vec) {
		sf::Texture t;
		if (vec == sf::Vector2u(0, 0)) {
			unsigned int maxSize = sf::Texture::getMaximumSize();
			t.create(maxSize, maxSize);
		} else
			t.create(vec.x, vec.y);
		textures.push_back(std::move(t));
	}

}
