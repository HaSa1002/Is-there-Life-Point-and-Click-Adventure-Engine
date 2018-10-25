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
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace itl {
	class LuaBindings {
	public:
		LuaBindings(sol::state& l);

	private:
		template<typename T>
		void bindSfmlVector(const std::string& s);

		template<typename T>
		void bindSfmlRect(const std::string& s);

		void bindTextRenderComponent();
		void bindRenderComponent();
		void bindSfmlTransformable();
		void bindSfmlEventStructs();
		void bindSizeEvent();
		void bindKeyEnum();
		void bindKeyEvent();
		void bindTextEvent();
		void bindMouseMoveEvent();
		void bindMouseButtonEnum();
		void bindMouseButtonEvent();
		void bindMouseWheelEnum();
		void bindMouseWheelEvent();
		void bindMouseWheelScrollEvent();
		void bindJoystickConnectEvent();
		void bindJoystickAxisEnum();
		void bindJoystickMoveEvent();
		void bindJoystickButtonEvent();
		void bindTouchEvent();
		void bindSensorTypeEnum();
		void bindSensorEvent();
		void bindEventTypeEnum();
		void bindEvent();



	sol::state& lua;
	};
}
#include "LuaBindings.inl"