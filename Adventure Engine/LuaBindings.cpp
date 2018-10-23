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

#include "LuaBindings.hpp"
#include "RenderComponent.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Transformable.hpp>

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

namespace itl {
	LuaBindings::LuaBindings(sol::state & l) :lua { l } {
		//Bind different sf::Vector
		this->bindSfmlVector<float, 'f'>();
		this->bindSfmlVector<int, 'i'>();
		this->bindSfmlVector<unsigned int, 'u'>();
		//Bind different sf::Rect
		this->bindSfmlRect<float>("Float");
		this->bindSfmlRect<int>("Int");


		this->bindSfmlEventStructs();
		this->bindSfmlTransformable();
		this->bindRenderComponent();
	}

	void LuaBindings::bindRenderComponent() {
		lua.new_usertype<RenderComponent>("RenderComponent",
			sol::constructors<RenderComponent(TextureManager&, size_t)>(),
			"getTransformable", &RenderComponent::getTransformable,
			"draw", &RenderComponent::draw,
			"getLocalBounds", &RenderComponent::getLocalBounds,
			"getGlobalBounds", &RenderComponent::getGlobalBounds,
			"getSize", &RenderComponent::getSize
			//sol::base_classes, sol::bases<sf::Drawable>()
			);
	}

	void LuaBindings::bindSfmlTransformable() {
		using Transformable = sf::Transformable;
		lua.new_usertype<Transformable>("Transformable",
			sol::default_constructor,
			"setPosition", sol::resolve<float, float>(&Transformable::setPosition),
			"setRotation", &Transformable::setRotation,
			"setScale", sol::resolve<float, float>(&Transformable::setScale),
			"setOrigin", sol::resolve<float, float>(&Transformable::setOrigin),
			"getPosition", &Transformable::getPosition,
			"getRotation", &Transformable::getRotation,
			"getScale", &Transformable::getScale,
			"getOrigin", &Transformable::getOrigin,
			"move", sol::resolve<float, float>(&Transformable::move),
			"rotate", &Transformable::rotate,
			"scale", sol::resolve<float, float>(&Transformable::scale)
			);

	}


	void LuaBindings::bindSizeEvent() {
		using SizeEvent = sf::Event::SizeEvent;
		lua.new_usertype<SizeEvent>("SizeEvent",
			sol::default_constructor,
			"width", sol::readonly_property(&SizeEvent::width),
			"height", sol::readonly_property(&SizeEvent::height)
			);
	}



	void LuaBindings::bindKeyEnum() {
		using Key = sf::Keyboard::Key;
		lua.new_enum<Key>("KeyboardKey", {
			{"A",			Key::A},
			{"B",			Key::B},
			{"C",			Key::C},
			{"D",			Key::D},
			{"E",			Key::E},
			{"F",			Key::F},
			{"G",			Key::G},
			{"H",			Key::H},
			{"I",			Key::I},
			{"J",			Key::J},
			{"K",			Key::K},
			{"L",			Key::L},
			{"M",			Key::M},
			{"N",			Key::N},
			{"O",			Key::O},
			{"P",			Key::P},
			{"Q",			Key::Q},
			{"R",			Key::R},
			{"S",			Key::S},
			{"T",			Key::T},
			{"U",			Key::U},
			{"V",			Key::V},
			{"W",			Key::W},
			{"X",			Key::X},
			{"Y",			Key::Y},
			{"Z",			Key::Z},
			{"Num0",		Key::Num0},
			{"Num1",		Key::Num1},
			{"Num2",		Key::Num2},
			{"Num3",		Key::Num3},
			{"Num4",		Key::Num4},
			{"Num5",		Key::Num5},
			{"Num6",		Key::Num6},
			{"Num7",		Key::Num7},
			{"Num8",		Key::Num8},
			{"Num9",		Key::Num9},
			{"Escape",		Key::Escape},
			{"LControl",	Key::LControl},
			{"LShift",		Key::LShift},
			{"LAlt",		Key::LAlt},
			{"LSystem",		Key::LSystem},
			{"RControl",	Key::RControl},
			{"RShift",		Key::RShift},
			{"RAlt",		Key::RAlt},
			{"RSystem",		Key::RSystem},
			{"Menu",		Key::Menu},
			{"LBracket",	Key::LBracket},
			{"RBracket",	Key::RBracket},
			{"RBracket",	Key::RBracket},
			{"Semicolon",	Key::Semicolon},
			{"Comma",		Key::Comma},
			{"Period",		Key::Period},
			{"Quote",		Key::Quote},
			{"Slash",		Key::Slash},
			{"Backslash",	Key::Backslash},
			{"Tilde",		Key::Tilde},
			{"Equal",		Key::Equal},
			{"Hyphen",		Key::Hyphen},
			{"Space",		Key::Space},
			{"Enter",		Key::Enter},
			{"Backspace",	Key::Backspace},
			{"Tab",			Key::Tab},
			{"PageUp",		Key::PageUp},
			{"PageDown",	Key::PageDown},
			{"End",			Key::End},
			{"Home",		Key::Home},
			{"Insert",		Key::Insert},
			{"Delete",		Key::Delete},
			{"Add",			Key::Add},
			{"Substract",	Key::Subtract},
			{"Multiply",	Key::Multiply},
			{"Divide",		Key::Divide},
			{"Left",		Key::Left},
			{"Right",		Key::Right},
			{"Up",			Key::Up},
			{"Down",		Key::Down},
			{"Numpad0",		Key::Numpad0},
			{"Numpad1",		Key::Numpad1},
			{"Numpad2",		Key::Numpad2},
			{"Numpad3",		Key::Numpad3},
			{"Numpad4",		Key::Numpad4},
			{"Numpad5",		Key::Numpad5},
			{"Numpad6",		Key::Numpad6},
			{"Numpad7",		Key::Numpad7},
			{"Numpad8",		Key::Numpad8},
			{"Numpad9",		Key::Numpad9},
			{"F1",			Key::F1},
			{"F2",			Key::F2},
			{"F3",			Key::F3},
			{"F4",			Key::F4},
			{"F5",			Key::F5},
			{"F6",			Key::F6},
			{"F7",			Key::F7},
			{"F8",			Key::F8},
			{"F9",			Key::F9},
			{"F11",			Key::F10},
			{"F11",			Key::F11},
			{"F12",			Key::F12},
			{"F13",			Key::F13},
			{"F14",			Key::F14},
			{"F15",			Key::F15},
			{"Pause",		Key::Pause}
			});
	}


	void LuaBindings::bindKeyEvent() {
		using KeyEvent = sf::Event::KeyEvent;
		lua.new_usertype<KeyEvent>("KeyEvent",
			sol::default_constructor,
			"code", sol::readonly_property(&KeyEvent::code),
			"alt", sol::readonly_property(&KeyEvent::alt),
			"control", sol::readonly_property(&KeyEvent::control),
			"shift", sol::readonly_property(&KeyEvent::shift),
			"system", sol::readonly_property(&KeyEvent::system)
			);
	}



	void LuaBindings::bindTextEvent() {
		using TextEvent = sf::Event::TextEvent;
		lua.new_usertype<TextEvent>("TextEvent",
			sol::default_constructor,
			"unicode", sol::readonly_property(&TextEvent::unicode)
			);
	}



	void LuaBindings::bindMouseMoveEvent() {
		using MouseMoveEvent = sf::Event::MouseMoveEvent;
		lua.new_usertype<MouseMoveEvent>("MouseMoveEvent",
			sol::default_constructor,
			"x", sol::readonly_property(&MouseMoveEvent::x),
			"y", sol::readonly_property(&MouseMoveEvent::y)
			);
	}



	void LuaBindings::bindMouseButtonEnum() {
		using MouseButton = sf::Mouse::Button;
		lua.new_enum<MouseButton>("MouseButton", {
		{"Left",		MouseButton::Left},
		{"Right",	MouseButton::Right},
		{"Middle",	MouseButton::Middle},
		{"XButton1", MouseButton::XButton1},
		{"XButton2",	MouseButton::XButton2}
			});
	}



	void LuaBindings::bindMouseButtonEvent() {
		using MouseButtonEvent = sf::Event::MouseButtonEvent;
		lua.new_usertype<MouseButtonEvent>("MouseButtonEvent",
			sol::default_constructor,
			"button", sol::readonly_property(&MouseButtonEvent::button),
			"x", sol::readonly_property(&MouseButtonEvent::x),
			"y", sol::readonly_property(&MouseButtonEvent::y)
			);
	}



	void LuaBindings::bindMouseWheelEnum() {
		using MouseWheel = sf::Mouse::Wheel;
		lua.new_enum<MouseWheel>("MouseWheel", {
			{"VerticalWheel", MouseWheel::VerticalWheel },
			{"HorizontalWheel", MouseWheel::HorizontalWheel }
			});
	}



	void LuaBindings::bindMouseWheelEvent() {
		using MouseWheelEvent = sf::Event::MouseWheelEvent;
		lua.new_usertype<MouseWheelEvent>("MouseWheelEvent",
			sol::default_constructor,
			"delta", sol::readonly_property(&MouseWheelEvent::delta),
			"x", sol::readonly_property(&MouseWheelEvent::x),
			"y", sol::readonly_property(&MouseWheelEvent::y)
			);
	}



	void LuaBindings::bindMouseWheelScrollEvent() {
		using MouseWheelScrollEvent = sf::Event::MouseWheelScrollEvent;
		lua.new_usertype<MouseWheelScrollEvent>("MouseWheelScrollEvent",
			sol::default_constructor,
			"wheel", sol::readonly_property(&MouseWheelScrollEvent::wheel),
			"delta", sol::readonly_property(&MouseWheelScrollEvent::delta),
			"x", sol::readonly_property(&MouseWheelScrollEvent::x),
			"y", sol::readonly_property(&MouseWheelScrollEvent::y)
			);
	}



	void LuaBindings::bindJoystickConnectEvent() {
		using JoystickConnectEvent = sf::Event::JoystickConnectEvent;
		lua.new_usertype<JoystickConnectEvent>("JoystickConnectEvent",
			sol::default_constructor,
			"joystickId", sol::readonly_property(&JoystickConnectEvent::joystickId)
			);
	}



	void LuaBindings::bindJoystickAxisEnum() {
		using Axis = sf::Joystick::Axis;
		lua.new_enum<Axis>("JoyStickAxis", {
			{"X", Axis::X },
			{"Y", Axis::Y },
			{"Z", Axis::Z },
			{"R", Axis::R },
			{"U", Axis::U },
			{"V", Axis::V },
			{"PovX", Axis::PovX },
			{"PovY", Axis::PovY }
			});
	}



	void LuaBindings::bindJoystickMoveEvent() {
		using JoyStickMoveEvent = sf::Event::JoystickMoveEvent;
		lua.new_usertype< JoyStickMoveEvent>("JoyStickMoveEvent",
			"joystickId", sol::readonly_property(&JoyStickMoveEvent::joystickId),
			"axis", sol::readonly_property(&JoyStickMoveEvent::axis),
			"position", sol::readonly_property(&JoyStickMoveEvent::position)

			);
	}



	void LuaBindings::bindJoystickButtonEvent() {
		using JoyStickButtonEvent = sf::Event::JoystickButtonEvent;
		lua.new_usertype<JoyStickButtonEvent>("JoyStickButtonEvent",
			sol::default_constructor,
			"joystickId", sol::readonly_property(&JoyStickButtonEvent::joystickId),
			"button", sol::readonly_property(&JoyStickButtonEvent::button)
			);
	}



	void LuaBindings::bindTouchEvent() {
		using TouchEvent = sf::Event::TouchEvent;
		lua.new_usertype<TouchEvent>("TouchEvent",
			sol::default_constructor,
			"finger", sol::readonly_property(&TouchEvent::finger),
			"x", sol::readonly_property(&TouchEvent::x),
			"y", sol::readonly_property(&TouchEvent::y)
			);
	}



	void LuaBindings::bindSensorTypeEnum() {
		using Type = sf::Sensor::Type;
		lua.new_enum<Type>("SensorType", {
			{"Accelerometer",		Type::Magnetometer},
			{"Gyroscope",			Type::Gyroscope},
			{"Magnetometer",		Type::Magnetometer},
			{"Gravity",				Type::Gravity},
			{"UserAcceleration",	Type::UserAcceleration},
			{"Orientation",			Type::Orientation}
			});

	}



	void LuaBindings::bindSensorEvent() {
		using SensorEvent = sf::Event::SensorEvent;
		lua.new_usertype<SensorEvent>("SensorEvent",
			sol::default_constructor,
			"type", sol::readonly_property(&SensorEvent::type),
			"x", sol::readonly_property(&SensorEvent::x),
			"y", sol::readonly_property(&SensorEvent::y)
			);
	}

	void LuaBindings::bindEventTypeEnum() {
		using EventType = sf::Event::EventType;
		lua.new_enum<EventType>("EventType", {
			{"Closed",					EventType::Closed},
			{"Resized",					EventType::Resized},
			{"LostFocus",				EventType::LostFocus},
			{"GainedFocus",				EventType::GainedFocus},
			{"TextEntered",				EventType::TextEntered},
			{"KeyPressed",				EventType::KeyPressed},
			{"KeyReleased",				EventType::KeyReleased},
			{"MouseWheelMoved",			EventType::MouseWheelMoved},
			{"MouseWheelScrolled",		EventType::MouseWheelScrolled},
			{"MouseButtonPressed",		EventType::MouseButtonPressed},
			{"MouseButtonReleased",		EventType::MouseButtonReleased},
			{"MouseMoved",				EventType::MouseMoved},
			{"MouseEntered",			EventType::MouseEntered},
			{"MouseLeft",				EventType::MouseLeft},
			{"JoystickButtonPressed",	EventType::JoystickButtonPressed},
			{"JoystickButtonReleased",	EventType::JoystickButtonReleased},
			{"JoystickMoved",			EventType::JoystickMoved},
			{"JoystickConnected",		EventType::JoystickConnected},
			{"JoystickDisconnected",	EventType::JoystickDisconnected},
			{"TouchBegan",				EventType::TouchBegan},
			{"TouchMoved",				EventType::TouchMoved},
			{"TouchEnded",				EventType::TouchEnded},
			{"SensorChanged",			EventType::SensorChanged},
			});
	}

	void LuaBindings::bindEvent() {
		using EventType = sf::Event::EventType;
		lua.new_usertype<sf::Event>("Event",
			sol::default_constructor,
			"type", sol::readonly_property(&sf::Event::type),
			"size", &sf::Event::size,
			"key", &sf::Event::key,
			"text", &sf::Event::text,
			"mouseMove", &sf::Event::mouseMove,
			"mouseButton", &sf::Event::mouseButton,
			"mouseWheel", &sf::Event::mouseWheel,
			"mouseWheelScroll", &sf::Event::mouseWheelScroll,
			"joystickMove", &sf::Event::joystickMove,
			"joystickButton", &sf::Event::joystickButton,
			"joystickConnect", &sf::Event::joystickConnect,
			"touch", &sf::Event::touch,
			"sensor", &sf::Event::sensor
			);
	}



	////////////////////////////////////////////////////////////
	void LuaBindings::bindSfmlEventStructs() {
		this->bindSizeEvent();
		this->bindKeyEnum();
		this->bindKeyEvent();
		this->bindTextEvent();
		this->bindMouseMoveEvent();
		this->bindMouseButtonEnum();
		this->bindMouseButtonEvent();
		this->bindMouseWheelEnum();
		this->bindMouseWheelEvent();
		this->bindMouseWheelScrollEvent();
		this->bindJoystickConnectEvent();
		this->bindJoystickAxisEnum();
		this->bindJoystickMoveEvent();
		this->bindJoystickButtonEvent();
		this->bindTouchEvent();
		this->bindSensorTypeEnum();
		this->bindSensorEvent();
		this->bindEventTypeEnum();
		this->bindEvent();
	}


}
