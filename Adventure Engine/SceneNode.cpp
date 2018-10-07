////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de) based on "SFML GAME DEVELOPMENT"
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

#include "SceneNode.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <cassert>

namespace itl {
	SceneNode::SceneNode() : mChildren(), mParent(nullptr) { }

	void SceneNode::attachChild(Ptr child) {
		child->mParent = this;
		mChildren.push_back(std::move(child));
	}

	SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
		auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
		assert(found != mChildren.end());

		Ptr result = std::move(*found);
		result->mParent = nullptr;
		mChildren.erase(found);
		return result;
	}

	void SceneNode::update(sf::Time dt) {
		updateCurrent(dt);
		updateChildren(dt);
	}

	void SceneNode::updateCurrent(sf::Time) { }

	void SceneNode::updateChildren(sf::Time dt) {
		for (Ptr& child : mChildren)
			child->update(dt);
	}

	void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// Apply transform of current node
		//states.transform *= getTransform();

		// Draw node and children with changed transform
		drawCurrent(target, states);
		drawChildren(target, states);
	}

	void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const { }

	void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
		for (const Ptr& child : mChildren)
			child->draw(target, states);
	}

	sf::Vector2f SceneNode::getWorldPosition() const {
		return getWorldTransform() * sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTransform() const {
		sf::Transform transform = sf::Transform::Identity;

		for (const SceneNode* node = this; node != nullptr; node = node->mParent)
			transform = node->getTransform() * transform;

		return transform;
	}
}